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
int main()
{
	Core51Init(&core51, acmain, NULL);
	while (1) {
		Core51Run(&core51);
	}
	//testRun();
}
