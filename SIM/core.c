#include "core.h"

#if WIN32
#define _INLINE_ __inline
#else
#define _INLINE_ inline
#endif

#define CORE_VALIDITY_CHECK() if (hCore51 == NULL) { return ERR_VOID_PTR; }\
if (hCore51->rom == NULL) { return ERR_VOID_PTR; }

/*����ACC�е�ֵ����P*/
 void _INLINE_ Core51UpdateP(HCORE_51 hCore51) {
	uint8_t acc = _ACC_(hCore51);
	uint8_t i = 0;
	uint8_t count = 0;
	for (i = 0; i < 8; i++) {
		if (((acc >> i) & 0x1)) {
			count++;
		}
	}
	if (count % 2) {
		_SetP_(hCore51);
	}
	else {
		_ClrP_(hCore51);
	}
}
#define _UPDATE_OV(sum) if ((((sum)) > 0x7f) || (((sum)) < -0x80)){ _SetOV_(hCore51); }else{  _ClrOV_(hCore51);}
#define _UPDATE_C(sum) if ((sum) > 0xff){ _SetC_(hCore51);} else{ _ClrC_(hCore51);}
#define _UPDATE_AC(sum) if ((sum) > 0xf){ _SetAC_(hCore51);} else{ _ClrAC_(hCore51);}



 const InstrTable instrTable[] = {
 { Core51NOP ,1},/*00*/
 { Core51AJMP_ADDR,2,1},/*01*/
 { Core51LJMP_ADDR,3,1},/*02*/
 { Core51RR_A,1},/*03*/
 { Core51INC_A,1},/*04*/
 { Core51INC_D,2},/*05*/
 { Core51INC_SR,1},/*06*/
 { Core51INC_SR,1},/*07*/
 { Core51INC_R,1},/*08*/
 { Core51INC_R,1},/*09*/
 { Core51INC_R,1},/*0A*/
 { Core51INC_R,1},/*0B*/
 { Core51INC_R,1},/*0C*/
 { Core51INC_R,1},/*0D*/
 { Core51INC_R,1},/*0E*/
 { Core51INC_R,1},/*0F*/
 { Core51JBC,3,1},/*10*/
 { Core51ACALL,2,1},//11
 { Core51LCALL,3,1},//12
 { Core51RRC_A,1},//13
 { Core51DEC_A,1},//14
 { Core51DEC_D,2},//15
 { Core51DEC_SR,1},//16
 { Core51DEC_SR,1},//17
 { Core51DEC_R,1},//18
 { Core51DEC_R,1},//19
 { Core51DEC_R,1},//1A
 { Core51DEC_R,1},//1B
 { Core51DEC_R,1},//1C
 { Core51DEC_R,1},//1D
 { Core51DEC_R,1},//1E
 { Core51DEC_R,1},//1F
 { Core51JB,3,1},//20
 { Core51AJMP_ADDR,2,1},//21
 { Core51RET,1,1},
 { Core51RL_A,1},
 { Core51ADD_AaddSD,2},
 { Core51ADD_AaddD,2},
 { Core51ADD_AaddSR,1},//26
 { Core51ADD_AaddSR,1},//27
 { Core51ADD_AaddR,1},//28
 { Core51ADD_AaddR,1},//29
 { Core51ADD_AaddR,1},//2A
 { Core51ADD_AaddR,1},//2B
 { Core51ADD_AaddR,1},//2C
 { Core51ADD_AaddR,1},//2D
 { Core51ADD_AaddR,1},//2E
 { Core51ADD_AaddR,1},//2F
 { Core51JNB,3,1},
 { Core51ACALL,2,1},//31
 { Core51RETI,1},
 { Core51RLC_A,1},
 { Core51ADDC_AaddSD,2},
 { Core51ADDC_AaddD,2},
 { Core51ADDC_AaddSR,1},//36
 { Core51ADDC_AaddSR,1},//37
 { Core51ADDC_AaddR,1},
 { Core51ADDC_AaddR,1},
 { Core51ADDC_AaddR,1},
 { Core51ADDC_AaddR,1},
 { Core51ADDC_AaddR,1},
 { Core51ADDC_AaddR,1},
 { Core51ADDC_AaddR,1},
 { Core51ADDC_AaddR,1},//3F
 { Core51JC,2,1},
 { Core51AJMP_ADDR,2,1},//41
 { Core51ORL_DA,2},
 { Core51ORL_DSD,3},
 { Core51ORL_ASD,2},
 { Core51ORL_AD,2},
 { Core51ORL_ASR,1},//46
 { Core51ORL_ASR,1},//47
 { Core51ORL_AR,1},
 { Core51ORL_AR,1},
 { Core51ORL_AR,1},
 { Core51ORL_AR,1},
 { Core51ORL_AR,1},
 { Core51ORL_AR,1},
 { Core51ORL_AR,1},
 { Core51ORL_AR,1},//4F
 { Core51JNC,2,1},
 { Core51ACALL,2,1},//51
 { Core51ANL_DA,2},
 { Core51ANL_DSD,3},
 { Core51ANL_ASD,2},
 { Core51ANL_AD,2},
 { Core51ANL_ASR,1},//56
 { Core51ANL_ASR,1},
 { Core51ANL_AR,1},
 { Core51ANL_AR,1},
 { Core51ANL_AR,1},
 { Core51ANL_AR,1},
 { Core51ANL_AR,1},
 { Core51ANL_AR,1},
 { Core51ANL_AR,1},
 { Core51ANL_AR,1},//5F
 { Core51JZ,2,1},
 { Core51AJMP_ADDR,2,1},//61
 { Core51XRL_DA,2},
 { Core51XRL_DSD,3},
 { Core51XRL_ASD,2},
 { Core51XRL_AD,2},
 { Core51XRL_ASR,1},//66
 { Core51XRL_ASR,1},
 { Core51XRL_AR,1},
 { Core51XRL_AR,1},
 { Core51XRL_AR,1},
 { Core51XRL_AR,1},
 { Core51XRL_AR,1},
 { Core51XRL_AR,1},
 { Core51XRL_AR,1},
 { Core51XRL_AR,1},//6F
 { Core51JNZ,2,1},//70
 { Core51ACALL,2,1},//71
 { Core51ORL_Cbit,2},
 { Core51JMP_AaddrDPTR,1},
 { Core51MOV_SD2A,2},
 { Core51MOV_SD2D,3},
 { Core51MOV_SD2SR,2},//76
 { Core51MOV_SD2SR,2},
 { Core51MOV_SD2R,2},
 { Core51MOV_SD2R,2},
 { Core51MOV_SD2R,2},
 { Core51MOV_SD2R,2},
 { Core51MOV_SD2R,2},
 { Core51MOV_SD2R,2},
 { Core51MOV_SD2R,2},
 { Core51MOV_SD2R,2},//7f
 { Core51SJMP_ADDR,2,1},
 { Core51AJMP_ADDR,2,1},//81
 { Core51ANL_Cbit,2},
 { Core51MOVC_SAaddPC2A,1,1},
 { Core51DIV_AB,1},
 { Core51MOV_D2D,3},
 { Core51MOV_SR2D,2},//86
 { Core51MOV_SR2D,2},
 { Core51MOV_R2D,2},
 { Core51MOV_R2D,2},
 { Core51MOV_R2D,2},
 { Core51MOV_R2D,2},
 { Core51MOV_R2D,2},
 { Core51MOV_R2D,2},
 { Core51MOV_R2D,2},
 { Core51MOV_R2D,2},//8F
 { Core51MOV_SD162DPTR,3},
 { Core51ACALL,2,1},//91
 { Core51MOV_bitC,2},
 { Core51MOVC_SAaddDPRT2A,1},
 { Core51SUBB_AsubSD,2},
 { Core51SUBB_AsubD,2},
 { Core51SUBB_AsubSR,1},//96
 { Core51SUBB_AsubSR,1},
 { Core51SUBB_AsubR,1},
 { Core51SUBB_AsubR,1},
 { Core51SUBB_AsubR,1},
 { Core51SUBB_AsubR,1},
 { Core51SUBB_AsubR,1},
 { Core51SUBB_AsubR,1},
 { Core51SUBB_AsubR,1},
 { Core51SUBB_AsubR,1},//9F
 { Core51ORL_Cnbit,2},
 { Core51AJMP_ADDR,2,1},//A1
 { Core51MOV_Cbit,2},
 { Core51INC_DPTR,1},
 { Core51MUL_AB,1},
 { NULL,0 },
 { Core51MOV_D2SR,2},//A6
 { Core51MOV_D2SR,2},
 { Core51MOV_D2R,2},
 { Core51MOV_D2R,2},
 { Core51MOV_D2R,2},
 { Core51MOV_D2R,2},
 { Core51MOV_D2R,2},
 { Core51MOV_D2R,2},
 { Core51MOV_D2R,2},
 { Core51MOV_D2R,2},//AF
 { Core51ANL_Cnbit,2},//B0
 { Core51ACALL,2,1},
 { Core51CPL_bit,2},
 { Core51CPL_C,1},
 { Core51CJNE_ASDr,3,1},
 { Core51CJNE_ADr,3,1},
 { Core51CJNE_SRSDr,3,1},//B6
 { Core51CJNE_SRSDr,3,1},
 { Core51CJNE_RSDr,3,1},
 { Core51CJNE_RSDr,3,1},
 { Core51CJNE_RSDr,3,1},
 { Core51CJNE_RSDr,3,1},
 { Core51CJNE_RSDr,3,1},
 { Core51CJNE_RSDr,3,1},
 { Core51CJNE_RSDr,3,1},
 { Core51CJNE_RSDr,3,1},//BF
 { Core51PUSH_D,2},//C0
 { Core51AJMP_ADDR,2,1},//C1
 { Core51CLR_bit,2},
 { Core51CLR_C,1},
 { Core51SWAP_A,1},
 { Core51XCH_AD,2},
 { Core51XCH_ASR,1},//C6
 { Core51XCH_ASR,1},
 { Core51XCH_AR,1},
 { Core51XCH_AR,1},
 { Core51XCH_AR,1},
 { Core51XCH_AR,1},
 { Core51XCH_AR,1},
 { Core51XCH_AR,1},
 { Core51XCH_AR,1},
 { Core51XCH_AR,1},//CF
 { Core51POP_D,2},
 { Core51ACALL,2,1},//D1
 { Core51SETB_bit,2},
 { Core51SETB_C,1},
 { Core51DA_A,1},
 { Core51DJNZ_Dr,3,1},
 { Core51XCHD_ASR,1},//D6
 { Core51XCHD_ASR,1},
 { Core51DJNZ_Rr,2,1},
 { Core51DJNZ_Rr,2,1},
 { Core51DJNZ_Rr,2,1},
 { Core51DJNZ_Rr,2,1},
 { Core51DJNZ_Rr,2,1},
 { Core51DJNZ_Rr,2,1},
 { Core51DJNZ_Rr,2,1},
 { Core51DJNZ_Rr,2,1},//DF
 { Core51MOVX_SDPTR2A,1},
 { Core51AJMP_ADDR,2,1},
 { Core51MOVX_SR2A,1},//E2
 { Core51MOVX_SR2A,1},
 { Core51CLR_A,1},
 { Core51MOV_D2A,2},
 { Core51MOV_SR2A,1},//E6
 { Core51MOV_SR2A,1},
 { Core51MOV_R2A,1},
 { Core51MOV_R2A,1},
 { Core51MOV_R2A,1},
 { Core51MOV_R2A,1},
 { Core51MOV_R2A,1},
 { Core51MOV_R2A,1},
 { Core51MOV_R2A,1},
 { Core51MOV_R2A,1},//EF
 { Core51MOVX_A2SDPTR,1},
 { Core51ACALL,2,1},
 { Core51MOVX_A2SR,1},//F2
 { Core51MOVX_A2SR,1},
 { Core51CPL_A,1},
 { Core51MOV_A2D,2},
 { Core51MOV_A2SR,1},//F6
 { Core51MOV_A2SR,1},
 { Core51MOV_A2R,1},
 { Core51MOV_A2R,1},
 { Core51MOV_A2R,1},
 { Core51MOV_A2R,1},
 { Core51MOV_A2R,1},
 { Core51MOV_A2R,1},
 { Core51MOV_A2R,1},
 { Core51MOV_A2R,1},//FF
 };
 
void Core51ADDUpdateOV(HCORE_51 hCore51,uint8_t a,uint8_t b,uint8_t res) {
	/*һ��һ����Ӳ��������*/
	/*������ӿ������*/
	if (!(a & 0x80) && !(b & 0x80) && (res & 0x80)) {
		/*�����*/
		_SetOV_(hCore51);
	}
	else if ((a & 0x80) && (b & 0x80) && !(res & 0x80)) {
		/*�����*/
		_SetOV_(hCore51);
	}
	else {
		_ClrOV_(hCore51);
	}
}
/*��ȡ�Ĵ����飬����PSW[3-4]*/
uint8_t _INLINE_ * Core51GetRegSet(HCORE_51 hCore51) {

	switch (_GetRS(_PSW(hCore51->dataMem))) {
	case 0:
		return _REG_BLOCK_0(hCore51->dataMem);
	case 1:
		return _REG_BLOCK_1(hCore51->dataMem);
	case 2:
		return _REG_BLOCK_2(hCore51->dataMem);
	case 3:
		return _REG_BLOCK_3(hCore51->dataMem);
	}
	return NULL;
}
//NOP 00 
void Core51NOP(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	/*ɶҲ����*/
}
//AJMP addr alO a9 a8 O 0001 a7 a6 a5 a4 a3 A2 al aO ����ת��  2�ֽ� PC��Ҫ�ȼ�2 
void Core51AJMP_ADDR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	uint16_t addr;
	addr = ((pcMemByte[0] >> 5) << 8) | pcMemByte[1];
	_GetPC(hCore51) &= ~0x7FF;
	_GetPC(hCore51) |= addr;
}
//LJMP addr 16 0x02 addr(15~8) ��ת��addr(7~0) 3�ֽ�
void Core51LJMP_ADDR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetPC(hCore51) = (pcMemByte[1] << 8) | pcMemByte[2];
}
//RR A 03 A�һ���
void Core51RR_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	register uint8_t HSB;
	HSB = _ACC_(hCore51) & 0x01;
	_ACC_(hCore51) >>= 1;
	_ACC_(hCore51) |= (HSB ? 0x80 : 0);
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//INC A 04 A��1
void Core51INC_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC(_GetDateMem(hCore51))++;

	Core51UpdateP(hCore51);/*����P��־λ*/
}
//INC dircet 05 dircet ֱ���ֽڼ�1 2�ֽ�
void Core51INC_D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]]++;
}
//INC @Ri 06~07 ���RAM��1
void Core51INC_SR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]]++;
}
//INC Rn 08~0F �Ĵ�����1
void Core51INC_R(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	regSet[pcMemByte[0] & 0x7]++;
}
//JBC bit, rel; 10 bit rel 3�ֽ�
void Core51JBC(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (pcMemByte[1] >= 0x00 && pcMemByte[1] <= 0x7f) {
		if (_GET_LOW_ADDR_BIT(hCore51, pcMemByte)) {
			_CLR_BIT(_GetDateMem(hCore51)[(pcMemByte[1] >> 3) + 0x20], pcMemByte[1] % 8);
			_GetPC(hCore51) += (int8_t)pcMemByte[2];

		}
	}
	else {
		if (_GET_HIGHT_ADDR_BIT(hCore51, pcMemByte)) {
			_CLR_BIT(_GetDateMem(hCore51)[(((uint8_t)(pcMemByte[1] >> 3)) << 3)], pcMemByte[1] % 8);
			_GetPC(hCore51) += (int8_t)pcMemByte[2];
		}
	}

}
//ACALL addr alO a9 a8 1 0001 a7 a6 a5 a4 a3 a2 al aO �����ӳ������ 2�ֽ�
void Core51ACALL(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_SP_(hCore51)++;
	_GetDateMem(hCore51)[_SP(_GetDateMem(hCore51))] = _GetPC(hCore51) & 0xff;
	_SP_(hCore51)++;
	_GetDateMem(hCore51)[_SP(_GetDateMem(hCore51))] = (_GetPC(hCore51) >> 8) & 0xff;

	_GetPC(hCore51) = ((pcMemByte[0] >> 5) << 8) | pcMemByte[1];
}
//LCALL addr 16 12 addr(15~8) ���ӳ������ 3�ֽ�
void Core51LCALL(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_SP_(hCore51)++;
	_GetDateMem(hCore51)[_SP(_GetDateMem(hCore51))] = _GetPC(hCore51) & 0xff;
	_SP_(hCore51)++;
	_GetDateMem(hCore51)[_SP(_GetDateMem(hCore51))] = (_GetPC(hCore51) >> 8) & 0xff;

	_GetPC(hCore51) = (pcMemByte[1] << 8) | pcMemByte[2];
}
//RRC A 13 Aͨ����λ�һ���
void Core51RRC_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	register uint8_t tC;
	register uint8_t LSB;
	LSB = (_ACC_(hCore51) & 0x01);
	tC = _GetC_(hCore51);

	_ACC_(hCore51) >>= 1;

	LSB ? _SetC_(hCore51) : _ClrC_(hCore51);

	_ACC_(hCore51) |= (tC ? 0x80 : 0);
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//DEC A 14 A��1 
void Core51DEC_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC(_GetDateMem(hCore51))--;
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//DEC dircet 15 dircet ֱ���ֽڼ�1 ˫�ֽ�
void Core51DEC_D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]]--;
}
//DEC @Ri 16~17 ���RAM��1
void Core51DEC_SR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]]--;
}
//DEC Rn 18~1F �Ĵ�����1
void Core51DEC_R(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	regSet[pcMemByte[0] & 0x7]--;
}
//JB bit, rel;  20 3�ֽ�
void Core51JB(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (pcMemByte[1] >= 0x00 && pcMemByte[1] <= 0x7f) {
		if (_GET_LOW_ADDR_BIT(hCore51, pcMemByte)) {
			_GetPC(hCore51) += pcMemByte[2];
		}
	}
	else {
		if (_GET_HIGHT_ADDR_BIT(hCore51, pcMemByte)) {
			_GetPC(hCore51) += pcMemByte[2];
		}
	}

}

//RET 22 �ӳ�����÷���
void Core51RET(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	uint8_t pcH;
	pcH = _GetDateMem(hCore51)[_SP(_GetDateMem(hCore51))];
	_SP_(hCore51)--;
	_GetPC(hCore51) = (pcH << 8) | _GetDateMem(hCore51)[_SP(_GetDateMem(hCore51))];
	_SP_(hCore51)--;
}
//RL A 23 A����
void Core51RL_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	register uint8_t HSB;
	HSB = _ACC_(hCore51) & 0x80;
	_ACC_(hCore51) <<= 1;
	_ACC_(hCore51) |= (HSB ? 1 : 0);
	Core51UpdateP(hCore51);/*����P��־λ*/
}
void _INLINE_ Core51ADD_BASE(HCORE_51 hCore51, uint8_t a, uint8_t b, uint8_t* res) {
	register int16_t sum;

	sum = (int16_t)((int8_t)a)+(int16_t)((int8_t)b);
	_UPDATE_OV(sum); /*�������*/
	sum = (a & 0xf) + (b & 0xf);
	_UPDATE_AC(sum);/*���λ*/
	sum = a + b;
	_UPDATE_C(sum);/*��λ*/
	*res = sum;

	Core51UpdateP(hCore51);/*����P��־λ*/
}
//ADD A, #data 24 data �������ӵ�A ˫�ֽ�
void Core51ADD_AaddSD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	Core51ADD_BASE(hCore51, (_ACC_(hCore51)), pcMemByte[1], &_ACC_(hCore51));
}
//ADD A, dircet 25 dircet ֱ���ֽڼӵ�A 2�ֽ�
void Core51ADD_AaddD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	Core51ADD_BASE(hCore51, (_ACC_(hCore51)), _GetDateMem(hCore51)[pcMemByte[1]], &_ACC_(hCore51));
}
//ADD A, @Ri 26~27 ���RAM�ӵ�A
void Core51ADD_AaddSR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	Core51ADD_BASE(hCore51, (_ACC_(hCore51)),
		_GetDateMem(hCore51)[(pcMemByte[0] & 0x01) ? _REG_1(regSet) : _REG_0(regSet)], &_ACC_(hCore51));
}
//ADD A,Rn 28~2F �Ĵ����ӵ�A ���ֽ�
void Core51ADD_AaddR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {

	Core51ADD_BASE(hCore51, regSet[pcMemByte[0] & 0x7], _ACC_(hCore51), &_ACC_(hCore51));
}
//JNB bit, rel; 30 3�ֽ�
void Core51JNB(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (pcMemByte[1] >= 0x00 && pcMemByte[1] <= 0x7f) {
		if (!_GET_LOW_ADDR_BIT(hCore51, pcMemByte)) {
			_GetPC(hCore51) += (int8_t)pcMemByte[2];
		}
	}
	else {
		if (!_GET_HIGHT_ADDR_BIT(hCore51, pcMemByte)) {
			_GetPC(hCore51) += (int8_t)pcMemByte[2];
		}
	}
}
//RETI addr 11 32 �жϵ��÷���
void Core51RETI(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	uint8_t pcH;
	pcH = _GetDateMem(hCore51)[_SP(_GetDateMem(hCore51))];
	_SP_(hCore51)--;
	_GetPC(hCore51) = (pcH << 8) | _GetDateMem(hCore51)[_SP(_GetDateMem(hCore51))];
	_SP_(hCore51)--;
}
//RLC A 33 Aͨ����λ����
void Core51RLC_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	register uint8_t tC;
	register uint8_t HSB;
	HSB = (_ACC_(hCore51) & 0x80);
	tC = _GetC_(hCore51) ? 1 : 0;

	_ACC_(hCore51) <<= 1;

	HSB ? _SetC_(hCore51) : _ClrC_(hCore51);

	_ACC_(hCore51) |= tC;
	Core51UpdateP(hCore51);/*����P��־λ*/
}
void _INLINE_ Core51ADDC_BASE(HCORE_51 hCore51, uint8_t a, uint8_t b, uint8_t* res) {
	register int16_t sum;

	sum = (int16_t)((int8_t)a) + (int16_t)((int8_t)b) + _GetC_(hCore51);
	_UPDATE_OV(sum); /*�������*/
	sum = (a & 0xf) + (b & 0xf) + _GetC_(hCore51);
	_UPDATE_AC(sum);/*���λ*/
	sum = a + b + _GetC_(hCore51);
	_UPDATE_C(sum);/*��λ*/
	*res = sum;

	Core51UpdateP(hCore51);/*����P��־λ*/
}
//ADDC A, data 34 data �������ͽ�λλ�ӵ�A ˫�ֽ�
void Core51ADDC_AaddSD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	Core51ADDC_BASE(hCore51, (_ACC_(hCore51)), pcMemByte[1], &_ACC_(hCore51));
}
//ADDC A, dircet 35dircet ֱ���ֽںͽ�λλ�ӵ�A 2�ֽ�
void Core51ADDC_AaddD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	Core51ADDC_BASE(hCore51, (_ACC_(hCore51)), _GetDateMem(hCore51)[pcMemByte[1]], &_ACC_(hCore51));
}
//ADDC A, @Ri 36~37 ����ֽںͽ�λλ�ӵ�A
void Core51ADDC_AaddSR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	Core51ADDC_BASE(hCore51, (_ACC_(hCore51)), _GetDateMem(hCore51)[pcMemByte[0] & 0x01 ? _REG_1(regSet) : _REG_0(regSet)], &_ACC_(hCore51));
}
//ADDC A, Rn 38~3F �Ĵ����ͽ�λλ�ӵ�A 
void Core51ADDC_AaddR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	Core51ADDC_BASE(hCore51, (_ACC_(hCore51)), regSet[pcMemByte[0] & 0x7], &_ACC_(hCore51));
}
//JC rel; 40 rel 2�ֽ�
void Core51JC(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (_GetC_(hCore51)) {
		_GetPC(hCore51) += (int8_t)pcMemByte[1];
	}
}
//ORL dircet, A 42 dircet A���򡱵�ֱ���ֽ� 2�ֽ�
void Core51ORL_DA(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]] |= _ACC_(hCore51);
}
//ORL dircet, #data 43 dircet data ���������򡱵�ֱ���ֽ� 3�ֽ�
void Core51ORL_DSD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]] |= pcMemByte[2];
}
//ORL A, #data 44 data ���������򡱵�A 2�ֽ�
void Core51ORL_ASD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) |= pcMemByte[1];
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//ORL A, dircet 45 dircet ֱ���ֽڡ��򡱵�A 2�ֽ�
void Core51ORL_AD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) |= _GetDateMem(hCore51)[pcMemByte[1]];
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//ORL A, @Ri 46~47 ���RAM���򡱵�A
void Core51ORL_ASR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) |= _GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]];
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//ORL A, Rn 48~4F �Ĵ������򡱵�A
void Core51ORL_AR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) |= regSet[pcMemByte[0] & 0x7];
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//JNC rel; 50 rel 2�ֽ�
void Core51JNC(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (!_GetC_(hCore51)) {
		_GetPC(hCore51) += (int8_t)pcMemByte[1];
	}
}
//ANL dircet A 52 dircet A���롱��ֱ���ֽ� 2�ֽ�
void Core51ANL_DA(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]] &= _ACC_(hCore51);
}
//ANL dircet, #data 53 dircet data ���������롱��ֱ���ֽ�
void Core51ANL_DSD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]] &= pcMemByte[2];
}
//ANL A, #data 54 data ���������롱��A 2�ֽ�
void Core51ANL_ASD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) &= pcMemByte[1];
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//ANL A, dircet 55 dircet ֱ���ֽڡ��롱��A 2�ֽ�
void Core51ANL_AD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) &= _GetDateMem(hCore51)[pcMemByte[1]];
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//ANL A, @Ri 56~57 ���RAm���롱��A
void Core51ANL_ASR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) &= _GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]];
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//ANL A, Rn 58~5F �Ĵ������롱��A
void Core51ANL_AR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) &= regSet[pcMemByte[0] & 0x7];
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//JZ rel 60 rel AΪ��ת�� 2�ֽ� PC��Ҫ�ȼ�2�ֽ�
void Core51JZ(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (!_ACC_(hCore51)) {
		_GetPC(hCore51) += (int8_t)pcMemByte[1];
	}
}
//XRL dircet A 62 dircet A����򡱵�ֱ���ֽ� 2�ֽ�
void Core51XRL_DA(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]] ^= _ACC_(hCore51);
}
//XRL dircet, #data 63 dircet data ����������򡱵�ֱ���ֽ� 3�ֽ�
void Core51XRL_DSD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]] ^= pcMemByte[2];
}
//XRL A, #data 64 data ����������򡱵�A 2�ֽ�
void Core51XRL_ASD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) ^= pcMemByte[1];
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//XRL A, dircet 65 dircet ֱ���ֽڡ���򡱵�A 2�ֽ�
void Core51XRL_AD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) ^= _GetDateMem(hCore51)[pcMemByte[1]];
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//XRL A, @Ri 66~67 ���RAM����򡱵�A
void Core51XRL_ASR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) ^= _GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]];
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//XRL A, Rn 68~6F �Ĵ�������򡱵�A
void Core51XRL_AR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) ^= regSet[pcMemByte[0] & 0x7];
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//JNZ rel 70 rel AΪ��ת�� 2�ֽ� PC��Ҫ�ȼ�2�ֽ�
void Core51JNZ(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (_ACC_(hCore51)) {
		_GetPC(hCore51) += (int8_t)pcMemByte[1];
	}
}
//ORL C, bit; (CY)��(bit)��CY 72 bit
void Core51ORL_Cbit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (pcMemByte[1] >= 0x00 && pcMemByte[1] <= 0x7f) {
		if (_GetC_(hCore51) || (_GET_LOW_ADDR_BIT(hCore51, pcMemByte))) {
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}
	else {
		if (_GetC_(hCore51) || (_GET_HIGHT_ADDR_BIT(hCore51, pcMemByte))) {
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}
}
//JMP @A+DPTR 73 �����DPTR���ת��
void Core51JMP_AaddrDPTR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetPC(hCore51) = _ACC_(hCore51) + _DPTR_(hCore51);
}
/*MOV A,#data 74 data ��������A ˫�ֽ�*/
void Core51MOV_SD2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC(_GetDateMem(hCore51)) = pcMemByte[1];
	Core51UpdateP(hCore51);
}
//MOV dircet, #data 75 dircet data ��������ֱ���ֽ� ���ֽ�
void Core51MOV_SD2D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]] = pcMemByte[2];
}
//MOV @Ri,#data 76~77 data �������ͼ��RAM ���ֽ�
void Core51MOV_SD2SR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]] = pcMemByte[1];
}
//MOV Rn, #data 78~7F data �������ͼĴ��� ˫�ֽ�
void Core51MOV_SD2R(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	regSet[pcMemByte[0]&0x7] = pcMemByte[1];
}
//SJMP rel 80 rel ��ת�ƣ����ת�� 2�ֽ� PC��Ҫ�ȼ�2�ֽ�
void Core51SJMP_ADDR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetPC(hCore51) += (int8_t)pcMemByte[1];
}
//ANL C, bit; (CY)��(bit)��CY 82 bit 2�ֽ�
void Core51ANL_Cbit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (pcMemByte[1] >= 0x00 && pcMemByte[1] <= 0x7f) {
		if (_GetC_(hCore51)  && _GET_LOW_ADDR_BIT(hCore51, pcMemByte)) {
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}
	else {
		if (_GetC_(hCore51) && _GET_HIGHT_ADDR_BIT(hCore51, pcMemByte)) {
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}
}
//MOVC A, @A+PC 83 ��((A)+(PC))��Ѱַ�ĳ���������ֽ���A ��ָ����ҪPC��+1
void Core51MOVC_SAaddPC2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC(_GetDateMem(hCore51)) = _GetRom(hCore51)[_ACC(_GetDateMem(hCore51)) + _GetPC(hCore51)];
	Core51UpdateP(hCore51); 
}
//DIV AB 84 A����B
void Core51DIV_AB(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	register uint8_t divNum;
	divNum = _B_(hCore51);
	if (divNum) {
		_B_(hCore51) = _ACC_(hCore51) % divNum;
		_ACC_(hCore51) = _ACC_(hCore51) / divNum;
		_ClrOV_(hCore51);
	}
	else {
		_SetOV_(hCore51);/*����Ϊ0*/
	}

	Core51UpdateP(hCore51);/*����P��־λ*/
}
//MOV dircet1, dircet2 85 dircet1 dircet2 ֱ���ֽ���ֱ���ֽ� ���ֽ�
void Core51MOV_D2D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[2]] = _GetDateMem(hCore51)[pcMemByte[1]];
}
//MOV dircet, @Ro 86~87 ���RAM��ֱ���ֽ� ˫�ֽ�
void Core51MOV_SR2D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]] = _GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]];
}
//MOV dircet, Rn 88~8F dircet �Ĵ�����ֱ���ֽ� ˫�ֽ�
void Core51MOV_R2D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]] = regSet[pcMemByte[0] & 0x7];
}
//MOV DPTR, #data16 90 data 15~8 16λ����������ָ�� data7~0
void Core51MOV_SD162DPTR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_DPL(_GetDateMem(hCore51)) = pcMemByte[2];
	_DPH(_GetDateMem(hCore51)) = pcMemByte[1];
}
//mov bit,c 92 2�ֽ�
void Core51MOV_bitC(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {

	if (pcMemByte[1] >= 0x00 && pcMemByte[1] <= 0x7f) {
		if (_GetC_(hCore51)) {
			_SET_BIT(_GetDateMem(hCore51)[(pcMemByte[1] >> 3) + 0x20], pcMemByte[1] % 8);
		}
		else {
			_CLR_BIT(_GetDateMem(hCore51)[(pcMemByte[1] >> 3) + 0x20], pcMemByte[1] % 8);
		}
	}
	else {
		if (_GetC_(hCore51)) {
			_SET_BIT(_GetDateMem(hCore51)[(((pcMemByte[1] >> 3)) << 3)], pcMemByte[1] % 8);
		}
		else {
			_CLR_BIT(_GetDateMem(hCore51)[(((pcMemByte[1] >> 3)) << 3)], pcMemByte[1] % 8);
		}
	}

}
//MOVC A, @A+DPTR 93 ��((A)+(DPTR))Ѱַ�ĳ���������ֽ�ѡA
void Core51MOVC_SAaddDPRT2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC(_GetDateMem(hCore51)) = _GetRom(hCore51)[_ACC(_GetDateMem(hCore51)) + _DPTR(_GetDateMem(hCore51))];
	Core51UpdateP(hCore51);
}
void _INLINE_ Core51SUBB_BASE(HCORE_51 hCore51, uint8_t a, uint8_t b, uint8_t* res) {
	register int16_t sum;

	sum = (int16_t)((int8_t)a) - (int16_t)((int8_t)b) -_GetC_(hCore51);
	_UPDATE_OV(sum); /*�������*/
	sum = (a & 0xf) - (b & 0xf) - _GetC_(hCore51);
	//_UPDATE_AC(sum);/*���λ*/
	if ((sum) <0) { _SetAC_(hCore51); }
	else { _ClrAC_(hCore51); }
	sum = a - b - _GetC_(hCore51);
	//_UPDATE_C(sum);/*��λ*/
	if ((sum) < 0) { _SetC_(hCore51); }
	else { _ClrC_(hCore51); }
	*res = sum;

	Core51UpdateP(hCore51);/*����P��־λ*/
}
//SUBB A, #data 94 data A��ȥ�������ͽ�λλ 2�ֽ�
void Core51SUBB_AsubSD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	Core51SUBB_BASE(hCore51, _ACC_(hCore51), pcMemByte[1], &_ACC_(hCore51));
}
//SUBB A, dircet 95 dircet A��ȥֱ���ֽںͽ�λλ 2�ֽ�
void Core51SUBB_AsubD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	Core51SUBB_BASE(hCore51, _ACC_(hCore51), _GetDateMem(hCore51)[pcMemByte[1]], &_ACC_(hCore51));
}
//SUBB A, @Ri 96~97 A��ȥ���RAM�ͽ�λλ
void Core51SUBB_AsubSR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	Core51SUBB_BASE(hCore51, _ACC_(hCore51), _GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]], &_ACC_(hCore51));
}
//SUBB A, Rn 98~9F A��ȥ�Ĵ����ͽ�λλ
void Core51SUBB_AsubR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	Core51SUBB_BASE(hCore51, _ACC_(hCore51), regSet[pcMemByte[0] & 0x7], &_ACC_(hCore51));
}
//ORL C, / bit; (CY)��()��CY A0 /bit
void Core51ORL_Cnbit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (pcMemByte[1] >= 0x00 && pcMemByte[1] <= 0x7f) {
		if (_GetC_(hCore51) || (!_GET_LOW_ADDR_BIT(hCore51, pcMemByte))) {
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}
	else {
		if (_GetC_(hCore51) || (!_GET_HIGHT_ADDR_BIT(hCore51, pcMemByte))) {
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}
}
//mov c,bit  c A2 2�ֽ�
void Core51MOV_Cbit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (pcMemByte[1] >= 0x00 && pcMemByte[1] <= 0x7f) {
		/*�õ�00H-7FH��ĳһλ*/
		if (_GET_LOW_ADDR_BIT(hCore51, pcMemByte)) {
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}
	else {
		/*�õ�80H-F7H��ĳһλ*/
		if (_GET_HIGHT_ADDR_BIT(hCore51, pcMemByte)) {
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}

	}
}
//INC DPTR A3 ����ָ���1
void Core51INC_DPTR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	uint16_t dptrAdd;
	dptrAdd = _DPTR(_GetDateMem(hCore51)) + 1;
	_DPL(_GetDateMem(hCore51)) = (dptrAdd) & 0xff;
	_DPH(_GetDateMem(hCore51)) = (dptrAdd >> 8) & 0xff;
}
//MUL AB A4 A����B
void Core51MUL_AB(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	uint16_t res;
	res = _ACC_(hCore51) * _B_(hCore51);
	_ACC_(hCore51) = res & 0xff;
	_B_(hCore51) = (res >> 8) & 0xff;

	if (res > 255) {
		_SetOV_(hCore51);
	}
	else {
		_ClrOV_(hCore51);
	}

	Core51UpdateP(hCore51);/*����P��־λ*/
}
//MOV @Ri,direct A6~A7 direct ���RAM�ͼ��RAM  ���ֽ�
void Core51MOV_D2SR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]] = _GetDateMem(hCore51)[pcMemByte[1]];
}
//MOV Rn, dircet A8~AF dircet ֱ���ֽ��ͼĴ��� ˫�ֽ�
void Core51MOV_D2R(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	regSet[pcMemByte[0] & 0x7] = _GetDateMem(hCore51)[pcMemByte[1]];
}
//ANL C, / bit; (CY)��()��CY B0 /bit
void Core51ANL_Cnbit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (pcMemByte[1] >= 0x00 && pcMemByte[1] <= 0x7f) {
		if (_GetC_(hCore51) && (!_GET_LOW_ADDR_BIT(hCore51, pcMemByte))) {
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}
	else {
		if (_GetC_(hCore51) && (!_GET_HIGHT_ADDR_BIT(hCore51, pcMemByte))) {
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}
}
//CPL bit B2 ֱ��λȡ�� 2�ֽ�
void Core51CPL_bit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (pcMemByte[1] >= 0x00 && pcMemByte[1] <= 0x7f) {
		if (_GET_LOW_ADDR_BIT(hCore51, pcMemByte)) {
			_CLR_BIT(_GetDateMem(hCore51)[(pcMemByte[1] >> 3) + 0x20], pcMemByte[1] % 8);
		}
		else {
			_SET_BIT(_GetDateMem(hCore51)[(pcMemByte[1] >> 3) + 0x20], pcMemByte[1] % 8);
		}
	}
	else {
		if (_GET_HIGHT_ADDR_BIT(hCore51, pcMemByte)) {
			_CLR_BIT(_GetDateMem(hCore51)[(((uint8_t)(pcMemByte[1] >> 3)) << 3)], pcMemByte[1] % 8);
		}
		else {
			_SET_BIT(_GetDateMem(hCore51)[(((uint8_t)(pcMemByte[1] >> 3)) << 3)], pcMemByte[1] % 8);
		}

	}
}
//CPL C B3 ��λȡ��
void Core51CPL_C(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (_GetC_(hCore51)) {
		_ClrC_(hCore51);
	}
	else {
		_SetC_(hCore51);
	}
}
//CJNE A, #data, rel B4 data rel ��������A�Ƚϣ�������ת��
void Core51CJNE_ASDr(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (_ACC_(hCore51) != pcMemByte[1]) {
		_GetPC(hCore51) += (int8_t)pcMemByte[2];
		if (_ACC_(hCore51) < pcMemByte[1]) {/*��һ��������С�ڵڶ���������C*/
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}

}
//CJNE A, dircet, rel B5 dircet rel ֱ���ֽ���A�Ƚϣ�������ת�� 3�ֽ� PC�ȼ�3
void Core51CJNE_ADr(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (_ACC_(hCore51) != _GetDateMem(hCore51)[pcMemByte[1]]) {
		_GetPC(hCore51) += (int8_t)pcMemByte[2];
		if (_ACC_(hCore51) < _GetDateMem(hCore51)[pcMemByte[1]]) {/*��һ��������С�ڵڶ���������C*/
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}
}
//CJNE @Ri,#data, rel B6~B7 data rel ����������RAM�Ƚϣ�������ת�� 3�ֽ�
void Core51CJNE_SRSDr(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (_GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]] != pcMemByte[1]) {
		_GetPC(hCore51) += (int8_t)pcMemByte[2];
		if (_GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]] < pcMemByte[1]) {/*��һ��������С�ڵڶ���������C*/
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}
}
//CJNE Rn, #data, rel B8~BF data rel ��������Ĵ����Ƚϣ�������ת�� 3�ֽ�
void Core51CJNE_RSDr(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (regSet[pcMemByte[0] & 0x7] != pcMemByte[1]) {
		_GetPC(hCore51) += (int8_t)pcMemByte[2];
		if (regSet[pcMemByte[0] & 0x7] < pcMemByte[1]) {/*��һ��������С�ڵڶ���������C*/
			_SetC_(hCore51);
		}
		else {
			_ClrC_(hCore51);
		}
	}
}
//PUSH dircet C0 dircet ֱ���ֽڽ�ջ��SP��1 2�ֽ�
void Core51PUSH_D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_SP(_GetDateMem(hCore51))++;
	_GetDateMem(hCore51)[_SP(_GetDateMem(hCore51))] = _GetDateMem(hCore51)[pcMemByte[1]];
}
//CLR bit C2 ���� 2�ֽ�
void Core51CLR_bit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (pcMemByte[1] >= 0x00 && pcMemByte[1] <= 0x7f) {
		_CLR_BIT(_GetDateMem(hCore51)[(pcMemByte[1] >> 3) + 0x20], pcMemByte[1] % 8);
	}
	else {
		_CLR_BIT(_GetDateMem(hCore51)[(((uint8_t)(pcMemByte[1] >> 3)) << 3)], pcMemByte[1] % 8);
	}
}
//CLR C C3 ����
void Core51CLR_C(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ClrC_(hCore51);
}
//SWAP A C4
void Core51SWAP_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	register uint8_t temp;
	register uint8_t temp1;

	temp = _ACC(_GetDateMem(hCore51)) & 0xf;
	temp1 = (_ACC(_GetDateMem(hCore51)) >> 4) & 0xf;
	_ACC(_GetDateMem(hCore51)) = (temp << 4) | temp1;
}
//XCH A, dircet C5 dircet ����A��ֱ���ֽ� 2�ֽ�
void Core51XCH_AD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	register uint8_t temp;
	temp = _ACC(_GetDateMem(hCore51));
	_ACC(_GetDateMem(hCore51)) = _GetDateMem(hCore51)[pcMemByte[1]];
	_GetDateMem(hCore51)[pcMemByte[1]] = temp;
	Core51UpdateP(hCore51);
}
//XCH A, @Ri C6~C7 ����A�ͼ��RAM
void Core51XCH_ASR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	register uint8_t temp;
	temp = _ACC(_GetDateMem(hCore51));
	_ACC(_GetDateMem(hCore51)) = _GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]];
	_GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]] = temp;
	Core51UpdateP(hCore51);
}
//XCH A, Rn C8~CF ����A�ͼĴ���
void Core51XCH_AR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	register uint8_t temp;
	temp = _ACC(_GetDateMem(hCore51));
	_ACC(_GetDateMem(hCore51)) = regSet[pcMemByte[0] & 0x7];
	regSet[pcMemByte[0] & 0x7] = temp;
	Core51UpdateP(hCore51);
}
//POP dircet D0 dircet ֱ���ֽ���ջ��SP��1 2�ֽ�
void Core51POP_D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]] = _GetDateMem(hCore51)[_SP(_GetDateMem(hCore51))];
	_SP(_GetDateMem(hCore51))--;
}
//SETB bit; 1��bit, ��λĳһλ D2 2�ֽ�
void Core51SETB_bit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	if (pcMemByte[1] >= 0x00 && pcMemByte[1] <= 0x7f) {
		_SET_BIT(_GetDateMem(hCore51)[(pcMemByte[1] >> 3) + 0x20], pcMemByte[1] % 8);
	}
	else {
		_SET_BIT(_GetDateMem(hCore51)[(((pcMemByte[1] >> 3)) << 3)], pcMemByte[1] % 8);
	}
}
//SETB C; 1��CY, ��λCY D3 
void Core51SETB_C(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_SetC_(hCore51);
}
//DA A D4 A��ʮ���Ƽӷ����� 
void Core51DA_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	/*zhangzheng �����û��ʵ��*/

	Core51UpdateP(hCore51);/*����P��־λ*/
}
//DJNZ dircet, rel D5 dircet rel ֱ���ֽڼ�1����Ϊ����ת�� 3�ֽ�
void Core51DJNZ_Dr(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]]--;
	if (_GetDateMem(hCore51)[pcMemByte[1]]) {
		_GetPC(hCore51) += (int8_t)pcMemByte[2];
	}
}
//XCHD A, @Ri D6~D7 ����A�ͼ��RAM�ĵ�λ 
void Core51XCHD_ASR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	register uint8_t temp;
	register uint8_t temp1;

	temp = _ACC(_GetDateMem(hCore51)) & 0xf;
	temp1 = _GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]] & 0xf;
	_GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]] &= 0xf;
	_GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]] |= temp;
	_ACC(_GetDateMem(hCore51)) &= 0xf;
	_ACC(_GetDateMem(hCore51)) |= temp1;
	Core51UpdateP(hCore51);
}
// DJNZ Rn, rel D8~DF rel �Ĵ�����1����Ϊ����ת�� 2�ֽ�
void Core51DJNZ_Rr(HCORE_51 hCore51, uint8_t * regSet, uint8_t * pcMemByte) {
	regSet[pcMemByte[0] & 0x7]--;
	if (regSet[pcMemByte[0] & 0x7]) {
		_GetPC(hCore51) += (int8_t)pcMemByte[1];
	}
}
//MOVX A, @DPTR E0 ���ⲿ���ݣ�16λ��ַ����A 1�ֽ�
void Core51MOVX_SDPTR2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC(_GetDateMem(hCore51)) = _GetExDateMem(hCore51)[
		_DPTR_(hCore51)
	];
	Core51UpdateP(hCore51);
}
//MOVX A, @Ri E2~E3 ���ⲿ���ݣ�8λ��ַ����A 1�ֽ�
void Core51MOVX_SR2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC(_GetDateMem(hCore51)) = _GetExDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]];
	Core51UpdateP(hCore51);
}
//CLR A E4 ����
void Core51CLR_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) = 0;
	Core51UpdateP(hCore51);/*����P��־λ*/
}
/*MOV A,direct E5 dircet ֱ���ֽ���A ˫�ֽ�*/
void Core51MOV_D2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC(_GetDateMem(hCore51)) = _GetDateMem(hCore51)[pcMemByte[1]];
	Core51UpdateP(hCore51);
}
/*MOV A,@Ri E6~E7 ���RAM��A */
void Core51MOV_SR2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC(_GetDateMem(hCore51)) = _GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]];
	Core51UpdateP(hCore51);
}
/*MOV A, Rn E8~EF �Ĵ���A ���ֽ�*/
void Core51MOV_R2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC(_GetDateMem(hCore51)) = regSet[pcMemByte[0] & 0x7];
	Core51UpdateP(hCore51);
}
//MOVX @DPTR,A F0 A���ⲿ���ݣ�16λ��ַ�� 1�ֽ�
void Core51MOVX_A2SDPTR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetExDateMem(hCore51)[_DPTR_(hCore51)] = _ACC(_GetDateMem(hCore51));
}
//MOVX @Ri,A F2~F3 A���ⲿ���ݣ�8λ��ַ��1�ֽ�
void Core51MOVX_A2SR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetExDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]] = _ACC(_GetDateMem(hCore51));
}
//CPL A F4 Aȡ��
void Core51CPL_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_ACC_(hCore51) = ~_ACC_(hCore51);
	Core51UpdateP(hCore51);/*����P��־λ*/
}
//MOV dircet, A F5 dircet A��ֱ���ֽ� ˫�ֽ�
void Core51MOV_A2D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[pcMemByte[1]] = _ACC(_GetDateMem(hCore51));
}
//MOV @Ri,A F6~F7 A�ͼ��RAM
void Core51MOV_A2SR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	_GetDateMem(hCore51)[regSet[pcMemByte[0] & 0x1]] = _ACC(_GetDateMem(hCore51));
}
/*MOV Rn, A F8~FF A�ͼĴ���*/
void Core51MOV_A2R(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte) {
	regSet[pcMemByte[0] & 0x7] = _ACC(_GetDateMem(hCore51));
}

void Core51Init(HCORE_51 hCore51,uint8_t *rom,uint8_t* exMem) {
	if (hCore51 == NULL) { return; }
	hCore51->PC = 0;
	memset(hCore51->dataMem, 0, sizeof(hCore51->dataMem));
	hCore51->rom = rom;
	hCore51->exDateMem = exMem;

	_SP_(hCore51) = 0x07;
	_P0_(hCore51) = 0xFF;
	_P1_(hCore51) = 0xFF;
	_P2_(hCore51) = 0xFF;
	_P3_(hCore51) = 0xFF;
}
#if _CORE_51_DEBUG
#include <stdio.h>
void InfoPrintf(HCORE_51 hCore51,uint8_t* regSet) {
	printf("R0:%x\t",regSet[0]);
	printf("R1:%x\t",regSet[1]);
	printf("R2:%x\t",regSet[2]);
	printf("R3:%x\t",regSet[3]);
	printf("R4:%x\t",regSet[4]);
	printf("R5:%x\t",regSet[5]);
	printf("R6:%x\t",regSet[6]);
	printf("R7:%x\t",regSet[7]);
	printf("SP:%x\r\n",_PSW_(hCore51));
	printf("ACC:%x\t",_ACC_(hCore51));
	printf("SP:%x\t",_SP_(hCore51));
	printf("PC:%x\r\n",_GetPC(hCore51));
	
}
#endif // _CORE_51_DEBUG
//int lastP1 = 0;
int count = 0;
Core51Err Core51Run(HCORE_51 hCore51) {
	uint8_t* regSet;/*�Ĵ�����*/
	uint8_t pcMemByte[4];
	CORE_VALIDITY_CHECK();

	regSet = Core51GetRegSet(hCore51);
	if (regSet == NULL) { return ERR_GET_SEG_SET; }

	pcMemByte[0] = _ROM_GET_BYTE(hCore51,0);
#if _CORE_51_DEBUG
	printf("%2x", pcMemByte[0]);
#endif
	if (instrTable[pcMemByte[0]].bytes == 2) {
		pcMemByte[1] = _ROM_GET_BYTE(hCore51, 1);
#if _CORE_51_DEBUG
		printf("%2x", pcMemByte[1]);
#endif
	}else if (instrTable[pcMemByte[0]].bytes == 3) {
		pcMemByte[1] = _ROM_GET_BYTE(hCore51, 1);
		pcMemByte[2] = _ROM_GET_BYTE(hCore51, 2);
#if _CORE_51_DEBUG
		printf("%2x", pcMemByte[1]);
		printf("%2x", pcMemByte[2]);
#endif
	}
#if _CORE_51_DEBUG
	printf("\r\n");
#endif
	if (instrTable[pcMemByte[0]].flag) {
		_PC_ADD_NUM(hCore51, instrTable[pcMemByte[0]].bytes);/*pc����*/
	}
	instrTable[pcMemByte[0]].instrRunFuntion(hCore51, regSet, pcMemByte);/*ִ��ָ��*/
	if (!instrTable[pcMemByte[0]].flag) {
		_PC_ADD_NUM(hCore51, instrTable[pcMemByte[0]].bytes);/*pc����*/
	}
#if _CORE_51_DEBUG
	//if (regSet[0] == 0) {
	//	printf("--------\r\n");
	//}
	if (_GetPC(hCore51) == 0x800) {
		printf("--------\r\n");
	}
	InfoPrintf(hCore51, regSet);
#endif
	
	//if (_GetPC(hCore51)<0x896&& _GetPC(hCore51) >0x8b5) {
	/*	if (_P1_(hCore51) != 0xff && lastP1!= _P1_(hCore51)) {
			printf("P1:%x\r\n", _P1_(hCore51));
			lastP1 = _P1_(hCore51);
		}*/
		
	//}
	if (count == 0) {
		printf("count:%d\r\n", 0);
	}
	if (count == 100000000) {
		printf("count:%d\r\n", count);
	}
	count++;
	return ERR_NO;
}

