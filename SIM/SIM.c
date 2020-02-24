/*
*date:2020/2/23
*author:zspace
*email:1358745329@qq.com
*/
#include <stdint.h>
#include <stdio.h>
#include "core.h"
#include "core_test.h"
#include "test_rom.h"
CORE_51 core51;
void Core51WDetectFun(void* hObject, uint16_t addr, uint8_t flag) {
	HCORE_51 hCore51 = hObject;
	if (flag == _INTER_ADDR) {
		if (addr == 0x80) {
			printf("P0:%x\r\n", hCore51->dataMem[addr]);
		}
	}
}
int main()
{
	Core51Init(&core51, acmain, NULL);
	core51.core51WDetectCb = Core51WDetectFun;
	while (1) {
		Core51Run(&core51);
	}
	//testRun();
}
