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
			uint8_t P0 = hCore51->dataMem[addr];
			//sbit LCD_CS     =P0^0;     //片选	
			//sbit LCD_DC     =P0^2;	  //数据/命令切换
			//sbit LCD_SDI    =P0^5;	  //数据
			//sbit LCD_SCK    =P0^7;	  //时钟
			//sbit LCD_REST   =P0^1;	  //复位  
			if (_GET_BIT(P0, 2)) {
				//OLED_DC_Set();
			}
			else {
				//OLED_DC_Clr();
			}
			if (_GET_BIT(P0, 5)) {
				//OLED_SDIN_Set();
			}
			else {
				//OLED_SDIN_Clr();
			}
			if (_GET_BIT(P0, 7)) {
				//OLED_SCLK_Set();
			}
			else {
				//OLED_SCLK_Clr();
			}
			if (_GET_BIT(P0, 1)) {
				//OLED_RES_Set();
			}
			else {
				//OLED_RES_Clr();
			}

			if (_GET_BIT(P0, 0)) {
				//OLED_BLK_Set();
			}
			else {
				//OLED_BLK_Clr();
			}
		}
	}
	else if (flag == _BIT_ADDR) {
		if (_GET_BIT_ADDR_VAL(hCore51 , addr) == 0X80) {
			uint8_t index = _GET_BIT_ADDR_INDEX(addr);
			uint8_t P0 = hCore51->dataMem[0x80];
			switch (index) {
			case 0:
				if (_GET_BIT(P0, 0)) {
					//OLED_BLK_Set();
				}
				else {
					//OLED_BLK_Clr();
				}
				break;
			case 1:
				if (_GET_BIT(P0, 1)) {
					//OLED_RES_Set();
				}
				else {
					//OLED_RES_Clr();
				}

				break;
			case 2:
				if (_GET_BIT(P0, 2)) {
					//OLED_DC_Set();
				}
				else {
					//OLED_DC_Clr();
				}
				break;
			case 5:
				if (_GET_BIT(P0, 5)) {
					//OLED_SDIN_Set();
				}
				else {
					//OLED_SDIN_Clr();
				}
				break;
			case 7:
				if (_GET_BIT(P0, 7)) {
					//OLED_SCLK_Set();
				}
				else {
					//LED_SCLK_Clr();
				}
				break;
			}
		}
	}
}
uint8_t exRam[2048];
int main()
{
	Core51Init(&core51, (uint8_t*)rom, exRam);
	core51.core51WDetectCb = Core51WDetectFun;
	while (1) {
		Core51Run(&core51);
	}
	//testRun();
}
