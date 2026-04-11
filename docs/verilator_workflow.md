# Verilator Workflow

## 环境
- Verilator
- Python 3
- `riscv64-unknown-elf-*` 工具链（编译CoreMark）

## CoreMark 一键链路
1. 构建与镜像转换  
   `python3 script/coremark/build_coremark.py --iterations 2000 --data-size 2000`
2. 运行仿真  
   `python3 script/coremark/run_coremark.py`
3. 解析日志  
   `python3 script/coremark/parse_coremark_log.py --log build/coremark/logs/coremark_run.log`

## 功能回归链路
1. 生成用例清单  
   `python3 script/tests/gen_testlist.py`
2. 构建镜像  
   `python3 script/tests/build_tests.py`
3. 全量回归  
   `python3 script/tests/run_tests.py`

## 关键约束
- 默认DUT：`student_top`
- CoreMark默认：`TOTAL_DATA_SIZE=2000`，`ITERATIONS=2000`
- 主计时口径：TB统计 `cycles`
- 输出要求：终端先显示CoreMark原生报告，日志落盘到 `build/*/logs`
