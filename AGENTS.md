# 项目概述

# 技术栈
- 前端 ：完成对./tests目录下相关原测试集用scripts脚本转化成 sv 能直接readmem 并且仿真的 .hex
- 后端 ： 使用tb下的sv 和cpp等，完成verilator仿真，生成的 结果分类放置在./build文件夹下

# 约定
- 若无重大错误，不允许修改/rtl 文件夹
- 不需要阅读 /fpga文件夹

# 目标
- tb下 选择合适的dut进行仿真，可选择分类
- 实现对tests下所有测试的仿真
- 自动化makefile 方便实现，例如
 make build rv32ui  --完成rv32ui的前端
 make run rv32ui -isa addi -wave 1 --完成单独一条指令仿真
 make run rv32ui                   --完成rv32ui所有指令仿真
 make build src0 
 make run src0     等等
 - 注意测试不仅需要显示是否通过，还需要显示所消耗的时钟周期，以及分支预测的命中率