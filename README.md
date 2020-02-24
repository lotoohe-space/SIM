# SIM
McS-51 MCU instruction simulator, all instructions can be simulated.
MCS-51单片机指令模拟器，全部指令都可以模拟。

2020/2/23
The simulation of 254 instructions has been realized and tested, but the test is not complete. Only the key instructions have been tested. Other instructions have been checked manually.
实现了254条指令的模拟，并进行测试，但是测试还不够完整，只对关键指令完成测试，其它指令测试均人为检查过，DA指令还未实现，后面会实现。

2020/2/24
Improved performance, realized simulation of DA instruction, realized exploration of data writing to RAM, enabled configuration by macro definition, and configured detection function by code, with examples in the code.
提高了性能，实现了DA指令的模拟,实现了对RAM的数据写入的探查，可通过宏定义启用配置，并通过代码配置侦测函数，代码中有示例。
