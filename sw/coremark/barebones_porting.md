# 在裸机系统中使用 CoreMark

本文仅包含将 CoreMark 移植到裸机（bare-bone）系统所需的信息。其他内容（例如运行规则）请参考 [README.md](README.md)。

## 裸机系统定义

这里的 bare-bones 指“最小可用系统”，只提供必要组件。一个 bare-bone 处理器系统可能没有完整操作系统（例如 Linux、Windows），此时也常称为 bare-metal（裸机）。

CoreMark 仓库中的 `barebones` 目录提供了将 CoreMark 移植到处理器系统所需的最小代码。由于该目录中的代码不依赖操作系统，它是将 CoreMark 移植到无 OS 的裸机场景（如微控制器或嵌入式处理器）的最佳起点。

## 概览

CoreMark 可用于微控制器/嵌入式处理器设备。在开始移植前，请先准备一个工程环境，至少包含：

- `printf` 支持
- 定时器支持（例如基于稳定时钟频率的参考计时源）

CoreMark 要求执行时间至少为 10 秒。因此在选择用于计时的定时器外设时，需要确保定时器能覆盖整个 CoreMark 运行时长。  
例如：如果你使用的是带 24 位定时器的微控制器，并把该 24 位定时器作为计时参考。若设备运行在 100MHz，且定时器使用处理器时钟，那么该定时器在溢出（或减到 0）前最长仅能计时 0.16777 秒。为了测量执行时间，你可以将该定时器配置为 1KHz 中断，并在中断服务程序中递增软件计数变量。该方案会有一些软件开销，但结果通常仍较准确。

如果定时器是 32 位，并且满足：

- 迭代次数不太高；
- 定时器频率不太高；

则可以在不发生溢出/下溢的情况下覆盖完整执行周期。  
例如，32 位定时器以 100MHz 递增/递减时，约 42.95 秒才会溢出/下溢。因此如果执行时间在 10 到 42.95 秒之间，可以直接使用定时器值。

开始前还需要估算最小迭代次数。迭代次数由 C 预处理宏 `ITERATIONS` 设置。  
例如处理器性能约为 4 CoreMark/MHz，主频 100MHz，则至少需要：

`4 (CoreMark/MHz) x 100 (MHz) x 10 (秒) = 4000` 次迭代。

计时参考设置错误是常见问题，因此请先测试你的计时代码。比如写一个等待 10 秒的小程序，并与外部计时工具（如秒表）对比。

准备完成后即可开始移植 CoreMark。需要以下文件：

- 无需修改的源码
  - [coremark/core_main.c](https://github.com/eembc/coremark/blob/main/core_main.c)
  - [coremark/core_list_join.c](https://github.com/eembc/coremark/blob/main/core_list_join.c)
  - [coremark/core_matrix.c](https://github.com/eembc/coremark/blob/main/core_matrix.c)
  - [coremark/core_state.c](https://github.com/eembc/coremark/blob/main/core_state.c)
  - [coremark/core_util.c](https://github.com/eembc/coremark/blob/main/core_util.c)
  - [coremark/coremark.h](https://github.com/eembc/coremark/blob/main/coremark.h)
- 需要修改的源码
  - [coremark/barebones/core_portme.c](https://github.com/eembc/coremark/blob/main/barebones/core_portme.c)
  - [coremark/barebones/core_portme.h](https://github.com/eembc/coremark/blob/main/barebones/core_portme.h)

当然，你还需要把定时器和 `printf` 支持文件加入工程。

在工程配置中，你还需要定义以下预处理宏：

| 预处理宏 | 说明 / 取值 |
|---|---|
|ITERATIONS| 设为可保证 CoreMark 工作负载至少运行 10 秒的迭代次数 |
|STANDALONE| 标识独立（Standalone）环境 |
|PERFORMANCE_RUN / VALIDATION_RUN | 设为 1 |

## 修改 core_portme.h

需要更新若干 C 宏：

| 预处理宏 | 取值 |
|---|---|
|HAS_FLOAT| 根据处理器/设备选择 0 或 1 |
|HAS_TIME_H| 0 |
|USE_CLOCK| 0 |
|HAS_STDIO| 1 |
|HAS_PRINTF| 1 |

文件中的下一部分与所用 C 编译器相关。原始代码使用 GCC 预定义宏 **\_\_GNUC\_\_** 和 **\_\_VERSION\_\_** 来打印编译器版本信息。（更多内容见 [GCC 文档](https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html)。）

```C
#ifndef COMPILER_VERSION
#ifdef __GNUC__
#define COMPILER_VERSION "GCC"__VERSION__
#else
#define COMPILER_VERSION "Please put compiler version here (e.g. gcc 4.1)"
#endif
#endif
#ifndef COMPILER_FLAGS
#define COMPILER_FLAGS \
    FLAGS_STR /* "Please put compiler flags here (e.g. -o3)" */
#endif
```

你也可以针对所用工具链，通过预定义宏补充更多编译器信息。比如 LLVM 预定义宏可参考 [这里](https://clang.llvm.org/docs/LanguageExtensions.html#builtin-macros)。

最后，设置 `MAIN_HAS_NOARGC`：

```C
#ifndef MAIN_HAS_NOARGC
#define MAIN_HAS_NOARGC 1
#endif
```

## 修改 core_portme.c

注意：下面代码仅为示例，你可以采用其他实现方式。

在该文件中，通常首先需要声明 `printf`、定时器、缓存相关的外部函数。例如我的工程中声明如下：

```C
extern void timer_config(void); /* 初始化定时器外设 */
extern void stdio_init(void);   /* 初始化 printf 支持（例如 UART） */
extern void cache_init(void);   /* 若有缓存，初始化处理器缓存 */
extern unsigned long get_100Hz_value(void); /* 读取 0.01 秒分辨率的计时值 */
```

然后将 `barebones_clock()` 修改为：

```C
CORETIMETYPE
barebones_clock()
{
/*#error \
    "You must implement a method to measure time in barebones_clock()! This function should return current time.\n"
    */
  return get_100Hz_value();
}
```

在这个例子里，定时器以 100Hz 递增。因此需要用以下配置告知评分计算代码：

```C
/* Define : TIMER_RES_DIVIDER
        Divider to trade off timer resolution and total time that can be
   measured.

        Use lower values to increase resolution, but make sure that overflow
   does not occur. If there are issues with the return value overflowing,
   increase this value.
        */
#define CLOCKS_PER_SEC             100
#define GETMYTIME(_t)              (*_t = barebones_clock())
#define MYTIMEDIFF(fin, ini)       ((fin) - (ini))
#define TIMER_RES_DIVIDER          1
#define SAMPLE_TIME_IMPLEMENTATION 1
#define EE_TICKS_PER_SEC           (CLOCKS_PER_SEC / TIMER_RES_DIVIDER)
```

最后，平台初始化代码可更新为：

```C
/* Function : portable_init
        Target specific initialization code
        Test for some common mistakes.
*/
void
portable_init(core_portable *p, int *argc, char *argv[])
{

/* #error \
    "Call board initialization routines in portable init (if needed), in particular initialize UART!\n"

    (void)argc; // prevent unused warning
    (void)argv; // prevent unused warning
*/
    /* 硬件初始化 */
    stdio_init();
    cache_init();
    timer_config();

    if (sizeof(ee_ptr_int) != sizeof(ee_u8 *))
    {
        ee_printf(
            "ERROR! Please define ee_ptr_int to a type that holds a "
            "pointer!\n");
    }
    if (sizeof(ee_u32) != 4)
    {
        ee_printf("ERROR! Please define ee_u32 to a 32b unsigned type!\n");
    }
    p->portable_id = 1;
}
```

## 额外注意事项

CoreMark 反映的是处理器某些性能侧面，但不一定代表真实应用性能。  
例如，CoreMark 的关键负载不包含浮点运算，且数据密集度有限。另外，由于其内存占用较小（这是为了让 CoreMark 能运行在小型、低成本且内存受限的微控制器上），在高端处理器系统上，基准程序很容易完全驻留于 L1 Cache，从而无法测试 L1 之外内存系统性能。针对高端处理器系统，可考虑 [SPEC](https://spec.org) 等其他基准测试。

若你使用的是将程序存放在 Flash 中的微控制器，且处理器具有指令缓存与数据缓存，多数情况下应同时开启 I-Cache 和 D-Cache 才能获得最佳性能。这是因为程序镜像同时包含指令与常量数据。

通常情况下，CoreMark 工程可放入 32KB ROM/Flash，RAM 使用量小于 32KB。RAM 中栈和堆的大小取决于处理器架构与所用工具链。  
例如，一些工具链在 `printf` 与浮点库上会占用更多 RAM（注意：基准结果计算可能会用到浮点运算）。在典型 32 位微控制器工具链下，CoreMark 通常使用小于 4KB 的栈和 4KB 的堆。

很多微控制器厂商和部分工具链厂商都会提供应用笔记，指导如何配置 CoreMark 工程以获得最佳性能。


