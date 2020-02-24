/*
*date:2020/2/23
*author:zspace
*email:1358745329@qq.com
*/
#include "core_test.h"
#include "core.h"
#include <stdio.h>
extern  const InstrTable instrTable[];

#define _DEBUG printf

typedef uint8_t (*TestFun)(HCORE_51 hCore51, uint8_t* regSet, uint16_t index);



uint8_t nop_test(HCORE_51 hCore51, uint8_t* regSet,uint16_t index) {
	uint8_t pcMemByte[4];
	instrTable[0].instrRunFuntion(hCore51, regSet,pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	return 1;
}
uint8_t AJMP_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = 0xe1;
	pcMemByte[1] = 0xff;
	_GetPC(hCore51) = 0;
	instrTable[1].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetPC(hCore51) == 0x7ff) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t LJMP_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = 0x02;
	pcMemByte[1] = 0xff;
	pcMemByte[2] = 0xff;
	_GetPC(hCore51) = 0;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetPC(hCore51) == 0xffff) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t RR_A_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = 0x03;
	_GetPC(hCore51) = 0;
	_ACC_(hCore51) = 0x3;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_ACC_(hCore51)==0x81) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51INC_A_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = 0x04;
	_GetPC(hCore51) = 0;
	_ACC_(hCore51) = 0x1;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_ACC_(hCore51) == 2 && _GetP_(hCore51)) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51INC_D_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = 0x05;
	pcMemByte[1] = 0x0A;
	_GetPC(hCore51) = 0;
	_ACC_(hCore51) = 0;

	_GetDateMem(hCore51)[0xA] = 5;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetDateMem(hCore51)[0xA] == 6 ) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51INC_SR_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;
	regSet[index&0x1] = 0xA;

	_GetDateMem(hCore51)[0xA] = 5;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetDateMem(hCore51)[0xA] == 6) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51INC_R_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;
	regSet[index&0x7] = 0x5;

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (regSet[index & 0x7] == 6) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51JBC_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = 0x57;
	pcMemByte[2] = 0x10;
	_GetPC(hCore51) = 0;
	_GetDateMem(hCore51)[0x2A] = 0x80;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetPC(hCore51) == 0x10) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51ACALL_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = 0xFF;
	_GetPC(hCore51) = 0x1234;
	_SP_(hCore51) = 0x7;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetPC(hCore51) == (((pcMemByte[0]>>5)<<8)| 0xFF)
		&& _SP_(hCore51)==9
		&& _GetDateMem(hCore51)[0x8]==0x34
		&& _GetDateMem(hCore51)[0x9]==0x12
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51LCALL_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = 0xFF;
	pcMemByte[2] = 0xFF;
	_GetPC(hCore51) = 0x1234;
	_SP_(hCore51) = 0x7;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetPC(hCore51) == 0xFFFF
		&& _SP_(hCore51) == 9
		&& _GetDateMem(hCore51)[0x8] == 0x34
		&& _GetDateMem(hCore51)[0x9] == 0x12
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51RRC_A_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;

	_SetC_(hCore51);
	_ACC_(hCore51)=0x02;

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetC_(hCore51)==0 && _ACC_(hCore51)==0x81) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51DEC_A_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;

	//_SetC_(hCore51);
	_ACC_(hCore51) = 0x03;

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if ( _ACC_(hCore51) == 0x02) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51DEC_D_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = 0x8;
	_GetPC(hCore51) = 0;

	_GetDateMem(hCore51)[0x8] = 3;

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetDateMem(hCore51)[0x8] == 0x02) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51DEC_SR_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;
	regSet[index & 0x1] = 0x8;

	_GetDateMem(hCore51)[0x8] = 3;

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetDateMem(hCore51)[0x8] == 0x02) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51DEC_R_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;
	regSet[index & 0x7] = 0x3;

	//_GetDateMem(hCore51)[0x8] = 1;

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (regSet[index & 0x7] == 0x02) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51JB_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = 0x57;
	pcMemByte[2] = 0x10;
	_GetPC(hCore51) = 0;

	_GetDateMem(hCore51)[0x2A] = 0x80;

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetPC(hCore51)==0x10) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51RET_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0xA;

	_GetDateMem(hCore51)[0xA] = 0x12;
	_GetDateMem(hCore51)[0x9] = 0x34;

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetPC(hCore51) == 0x1234 && _SP_(hCore51) ==0x8) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51RL_A_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_GetDateMem(hCore51)[0xA] = 0x12;

	_ACC_(hCore51) = 0x80;

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_ACC_(hCore51) == 0x01) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51ADD_AaddSD_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = (uint8_t)(-30);
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_GetDateMem(hCore51)[0xA] = 0x12;

	_ACC_(hCore51) = (uint8_t)(-100);

	_PSW_(hCore51) = 0x00;

 	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_ACC_(hCore51) == 0x7e
		&& _PSW_(hCore51)==0x84
		) {
		//return 1;
	}
	else {
		return 0;
	}
	pcMemByte[1] = (uint8_t)(255);
	_ACC_(hCore51) = (uint8_t)(255);
	_PSW_(hCore51) = 0x00;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	if (_ACC_(hCore51) == 0xFe
		&& _PSW_(hCore51) == 0xc1
		) {
	}
	else {
		return 0;
	}

	pcMemByte[1] = (uint8_t)(0xf);
	_ACC_(hCore51) = (uint8_t)(0xf);
	_PSW_(hCore51) = 0x00;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	if (_ACC_(hCore51) == 0x1e
		&& _PSW_(hCore51) == 0x40
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51ADD_AaddD_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = 0xa;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_GetDateMem(hCore51)[0xA] = (uint8_t)(-30);

	_ACC_(hCore51) = (uint8_t)(-100);

	_PSW_(hCore51) = 0x00;

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_ACC_(hCore51) == 0x7e
		&& _PSW_(hCore51) == 0x84
		) {
		//return 1;
	}
	else {
		return 0;
	}
	_GetDateMem(hCore51)[0xA] = (uint8_t)(255);
	_ACC_(hCore51) = (uint8_t)(255);
	_PSW_(hCore51) = 0x00;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	if (_ACC_(hCore51) == 0xFe
		&& _PSW_(hCore51) == 0xc1
		) {
	}
	else {
		return 0;
	}

	_GetDateMem(hCore51)[0xA] = (uint8_t)(0xf);
	_ACC_(hCore51) = (uint8_t)(0xf);
	_PSW_(hCore51) = 0x00;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	if (_ACC_(hCore51) == 0x1e
		&& _PSW_(hCore51) == 0x40
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51ADD_AaddSR_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;

	regSet[index & 0x1] = 0xA;

	_GetDateMem(hCore51)[0xA] = (uint8_t)(-30);

	_ACC_(hCore51) = (uint8_t)(-100);

	_PSW_(hCore51) = 0x00;

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_ACC_(hCore51) == 0x7e
		&& _PSW_(hCore51) == 0x84
		) {
		//return 1;
	}
	else {
		return 0;
	}
	_GetDateMem(hCore51)[0xA] = (uint8_t)(255);
	_ACC_(hCore51) = (uint8_t)(255);
	_PSW_(hCore51) = 0x00;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	if (_ACC_(hCore51) == 0xFe
		&& _PSW_(hCore51) == 0xc1
		) {
	}
	else {
		return 0;
	}

	_GetDateMem(hCore51)[0xA] = (uint8_t)(0xf);
	_ACC_(hCore51) = (uint8_t)(0xf);
	_PSW_(hCore51) = 0x00;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	if (_ACC_(hCore51) == 0x1e
		&& _PSW_(hCore51) == 0x40
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51ADD_AaddR_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;

	regSet[index & 0x7] = (uint8_t)(-30);

	//_GetDateMem(hCore51)[0xA] = (uint8_t)(-30);

	_ACC_(hCore51) = (uint8_t)(-100);

	_PSW_(hCore51) = 0x00;

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_ACC_(hCore51) == 0x7e
		&& _PSW_(hCore51) == 0x84
		) {
		//return 1;
	}
	else {
		return 0;
	}
	//_GetDateMem(hCore51)[0xA] = (uint8_t)(255);
	regSet[index & 0x7] = (uint8_t)(255);
	_ACC_(hCore51) = (uint8_t)(255);
	_PSW_(hCore51) = 0x00;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	if (_ACC_(hCore51) == 0xFe
		&& _PSW_(hCore51) == 0xc1
		) {
	}
	else {
		return 0;
	}

	//_GetDateMem(hCore51)[0xA] = (uint8_t)(0xf);
	regSet[index & 0x7] = (uint8_t)(0xf);
	_ACC_(hCore51) = (uint8_t)(0xf);
	_PSW_(hCore51) = 0x00;
	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	if (_ACC_(hCore51) == 0x1e
		&& _PSW_(hCore51) == 0x40
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51JNB_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = 0x57;
	pcMemByte[2] = 0x10;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_ACC_(hCore51) = 0x00;
	_PSW_(hCore51) = 0x00;

	_GetDateMem(hCore51)[0x2A] = (uint8_t)(0);

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetPC(hCore51)==0x10
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51RETI_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	return  Core51RET_test( hCore51,  regSet,  index);
}
uint8_t Core51RLC_A_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_ACC_(hCore51) = 0x40;
	_PSW_(hCore51) = 0x80;

	_GetDateMem(hCore51)[0x2A] = (uint8_t)(0);

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_ACC_(hCore51) == 0x81 && _PSW_(hCore51)==0x00
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51JC_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = 0x10;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_ACC_(hCore51) = 0x00;
	_PSW_(hCore51) = 0x80;

	//_GetDateMem(hCore51)[0x2A] = (uint8_t)(0);

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetPC(hCore51)==0x10
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51ORL_Cbit_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = 0x57;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_ACC_(hCore51) = 0x00;
	_PSW_(hCore51) = 0x80;

	_GetDateMem(hCore51)[0x2A] = (uint8_t)(0x00);

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_PSW_(hCore51) == 0x80
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51ANL_Cbit_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = 0x57;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_ACC_(hCore51) = 0x00;
	_PSW_(hCore51) = 0x80;

	_GetDateMem(hCore51)[0x2A] = (uint8_t)(0x80);

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_PSW_(hCore51) == 0x80
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51DIV_AB_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_ACC_(hCore51) = 255;
	_B_(hCore51) = 0x5;
	_PSW_(hCore51) = 0x00;

	_GetDateMem(hCore51)[0x2A] = (uint8_t)(0x00);

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_ACC_(hCore51) == 0x33
		&&_B_(hCore51)==0x00
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51MOV_bitC_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = 0x57;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_ACC_(hCore51) = 0;
	_B_(hCore51) = 0;
	_PSW_(hCore51) = 0x80;

	_GetDateMem(hCore51)[0x2A] = (uint8_t)(0x00);

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_GetDateMem(hCore51)[0x2A]==0x80
		) {
		return 1;
	}
	else {
		return 0;
	}
}

uint8_t Core51SUBB_AsubSD_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	pcMemByte[1] = (uint8_t)(-128);
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_ACC_(hCore51) = 10;
	_B_(hCore51) = 0;
	_PSW_(hCore51) = 0x00;

	_GetDateMem(hCore51)[0x2A] = (uint8_t)(0x00);

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_ACC_(hCore51) == 0x8a && _PSW_(hCore51)==0x85
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51MUL_AB_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_ACC_(hCore51) = (uint8_t)(-10);
	_B_(hCore51) = 100;
	_PSW_(hCore51) = 0x00;

	_GetDateMem(hCore51)[0x2A] = (uint8_t)(0x00);

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_ACC_(hCore51) == 0x18 && _B_(hCore51) ==0x60 && _PSW_(hCore51) == 0x04
		) {
		return 1;
	}
	else {
		return 0;
	}
}
uint8_t Core51DA_A_test(HCORE_51 hCore51, uint8_t* regSet, uint16_t index) {
	uint8_t pcMemByte[4];
	pcMemByte[0] = index;
	_GetPC(hCore51) = 0;
	_SP_(hCore51) = 0;
	_ACC_(hCore51) = (uint8_t)(0xC9);
	_B_(hCore51) = 100;
	_PSW_(hCore51) = 0x00;

	_GetDateMem(hCore51)[0x2A] = (uint8_t)(0x00);

	instrTable[index].instrRunFuntion(hCore51, regSet, pcMemByte);
	_DEBUG("%s\t字节数:%d\tflag:%d\r\n", __FUNCTION__, instrTable[index].bytes, instrTable[index].flag);
	if (_ACC_(hCore51)== 0x29 && _GetC_(hCore51)
		) {
		return 1;
	}
	else {
		return 0;
	}
}
TestFun testFun[] = {
	nop_test,
	AJMP_test,
	LJMP_test,
	RR_A_test,
	Core51INC_A_test,
	Core51INC_D_test,
	Core51INC_SR_test,
	Core51INC_SR_test,
	Core51INC_R_test,
	Core51INC_R_test,
	Core51INC_R_test,
	Core51INC_R_test,
	Core51INC_R_test,
	Core51INC_R_test,
	Core51INC_R_test,
	Core51INC_R_test,
	Core51JBC_test,
	Core51ACALL_test,
	Core51LCALL_test,
	Core51RRC_A_test,
	Core51DEC_A_test,
	Core51DEC_D_test,
	Core51DEC_SR_test,
	Core51DEC_SR_test,
	Core51DEC_R_test,
	Core51DEC_R_test,
	Core51DEC_R_test,
	Core51DEC_R_test,
	Core51DEC_R_test,
	Core51DEC_R_test,
	Core51DEC_R_test,
	Core51DEC_R_test,
	Core51JB_test,
	AJMP_test,
	Core51RET_test,
	Core51RL_A_test,
	Core51ADD_AaddSD_test,
	Core51ADD_AaddD_test,
	Core51ADD_AaddSR_test,
	Core51ADD_AaddSR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51JNB_test,
	Core51ACALL_test,
	Core51RETI_test,
	Core51RLC_A_test,
	/*addc利用add测试函数也可以测试*/
	Core51ADD_AaddSD_test,
	Core51ADD_AaddD_test,
	Core51ADD_AaddSR_test,
	Core51ADD_AaddSR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	Core51ADD_AaddR_test,
	/******************************/
	Core51JC_test,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	Core51ORL_Cbit_test,
};
uint16_t testFunLen = sizeof(testFun) / sizeof(TestFun);
void testRun(void) {
	CORE_51 Core51;
	uint16_t i;
	uint8_t* regSet;
	uint8_t	exRAM[2048];
	Core51Init(&Core51, NULL, exRAM);
	regSet = Core51GetRegSet(&Core51);
	if (regSet == NULL) { return ; }
	for (i = 0; i < testFunLen; i++) {
		if (testFun[i] != NULL) {
			if (testFun[i](&Core51, regSet, i) == 0) {
				printf("测试失败\r\n");
			}
			else {
				//printf("测试成功\r\n");
			}
		}
	}
	if (Core51ANL_Cbit_test(&Core51, regSet, 0x82) == 0) {
		printf("测试失败\r\n");
	}
	else {
		//printf("测试成功\r\n");
	}
	if (Core51DIV_AB_test(&Core51, regSet, 0x84) == 0) {
		printf("测试失败\r\n");
	}
	else {
		//printf("测试成功\r\n");
	}
	if (Core51MOV_bitC_test(&Core51, regSet, 0x92) == 0) {
		printf("测试失败\r\n");
	}
	else {
		//printf("测试成功\r\n");
	}
	if (Core51SUBB_AsubSD_test(&Core51, regSet, 0x94) == 0) {
		printf("测试失败\r\n");
	}
	else {
		//printf("测试成功\r\n");
	}
	if (Core51MUL_AB_test(&Core51, regSet, 0xA4) == 0) {
		printf("测试失败\r\n");
	}
	else {
		//printf("测试成功\r\n");
	}
	if (Core51DA_A_test(&Core51, regSet, 0xD4) == 0) {
		printf("测试失败\r\n");
	}
	else {
		//printf("测试成功\r\n");
	}
	
}
