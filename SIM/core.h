/*
*date:2020/2/23
*author:zspace
*email:1358745329@qq.com
*/
#ifndef _CORE_H__
#define _CORE_H__

#include <stdint.h>
#include <string.h>

#define _CORE_51_DEBUG			0	/*是否开启调试*/

#define _CORE_51_WRITE_DETECT	1	/*开启内存写入探查*/
#define _INTER_ADDR				0
#define _EX_ADDR				1
#define _BIT_ADDR				2

#if _CORE_51_WRITE_DETECT
typedef void (*Core51WDetectFunction)(void* hObject, uint16_t addr, uint8_t flag);
#endif

typedef struct {
	uint16_t	PC;							/*PC寄存器*/
	uint8_t		dataMem[0xFF];				/*数据存储器*/
	uint8_t*	exDateMem;					/*外部数据存储单元*/
	uint8_t*	rom;						/*rom指针指向被运行的ROM*/
#if _CORE_51_WRITE_DETECT
	Core51WDetectFunction core51WDetectCb;	/*写入探查函数*/
#endif
}*HCORE_51,CORE_51;

typedef enum {
	ERR_VOID_PTR = 0,
	ERR_GET_SEG_SET=1,
	ERR_NO=2,
}Core51Err;

/*指令表*/
typedef void (*InstrRunFuntion)(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);
typedef struct {
	InstrRunFuntion instrRunFuntion;
	uint8_t		 bytes;
	uint8_t		 flag;
}InstrTable;



/*获取ROM*/
#define _GetRom(a)			((a)->rom)
/*获取PC*/
#define	_GetPC(a)			((a)->PC)
/*获取寄存器区域*/
#define _GetDateMem(a)		((a)->dataMem)
/*获取拓展内存区域*/
#define _GetExDateMem(a)	((a)->exDateMem)

/*获取ROM中相对PC的偏移*/
#define _ROM_GET_BYTE(a,b)	_GetRom((a))[_GetPC((a))+(b)]
/*PC地址加上num*/
#define _PC_ADD_NUM(a,num) ((a)->PC+=(num))

 /*获取00-7f的位逻辑值*/
#define _GET_LOW_ADDR_BIT(a,b) ((_GetDateMem(a)[((uint8_t)(b[1] >> 3)) + 0x20]) & ((1 << (b[1] % 8))))
/*得到80H-F7H的某一位*/
#define _GET_HIGHT_ADDR_BIT(a,b) ((_GetDateMem(a)[(((uint8_t)(b[1] >> 3)) << 3)]) & ((1 << (b[1] % 8))))

#define _GET_BIT_ADDR_VAL(a,b)	(((b) >= 0x00 && (b) <= 0x7f)?\
((((uint8_t)b) >> 3) + 0x20):(((uint8_t)((b) >> 3)) << 3))

#define _GET_BIT_ADDR_INDEX(a)	((a) % 8)

/*获取寄存器中的值*/
#define _B(a)		(*((a)+0xF0))/*获得B的值*/
#define _B_(a)		_B(_GetDateMem((a)))/*通过结构体过去到ACC*/
#define _ACC(a)		(*((a)+0xE0))
#define _ACC_(a)	_ACC(_GetDateMem((a)))/*通过结构体过去到ACC*/
#define _PSW(a)		(*((a)+0xD0))
#define _PSW_(a)	_PSW(_GetDateMem((a)))/*通过结构体过去到ACC*/
#define _TH2(a)		(*((a)+0xCD))
#define _TL2(a)		(*((a)+0xCC))
#define _RCAP2H(a)	(*((a)+0xCB))
#define _RCAP2L(a)	(*((a)+0xCA))
#define _T2CON(a)	(*((a)+0xC8))
#define _IP(a)		(*((a)+0xB8))
#define _P3(a)		(*((a)+0xB0))
#define _P3_(a)		_P3(_GetDateMem((a)))/*通过结构体过去到ACC*/
#define _IE(a)		(*((a)+0xA8))
#define _P2(a)		(*((a)+0xA0))
#define _P2_(a)		_P2(_GetDateMem((a)))/*通过结构体过去到ACC*/
#define _SBUF(a)	(*((a)+0x99))
#define _SCON(a)	(*((a)+0x98))
#define _P1(a)		(*((a)+0x90))
#define _P1_(a)		_P1(_GetDateMem((a)))/*通过结构体过去到ACC*/
#define _TH1(a)		(*((a)+0x8D))
#define _TH0(a)		(*((a)+0x8C))
#define _TL1(a)		(*((a)+0x8B))
#define _TL0(a)		(*((a)+0x8A))
#define _TMOD(a)	(*((a)+0x89))
#define _TCON(a)	(*((a)+0x88))
#define _DPH(a)		(*((a)+0x83))
#define _DPL(a)		(*((a)+0x82))
#define _SP(a)		(*((a)+0x81))
#define _SP_(a)		_SP(_GetDateMem((a)))/*通过结构体过去到ACC*/
#define _P0(a)		(*((a)+0x80))
#define _P0_(a)		_P0(_GetDateMem((a)))/*通过结构体过去到ACC*/
#define _PCON(a)	(*((a)+0x87))


#define _DPTR(a)	((_DPH(a)<<8)|_DPL(a))
#define _DPTR_(a)	(((_DPH(_GetDateMem(a)))<<8)|(_DPL(_GetDateMem(a))))

/*获取PSW中的各位*/
#define _GetC(a)	((a)&0x80)
#define _GetC_(a)	(_GetC(_PSW(_GetDateMem((a)))))
#define _GetAC(a)	((a)&0x40)
#define _GetAC_(a)	(_GetAC(_PSW(_GetDateMem((a)))))
#define _GetF0(a)	((a)&0x20)
#define _GetRS1(a)	((a)&0x10)
#define _GetRS0(a)	((a)&0x08)
#define _GetOV(a)	((a)&0x04)
#define _GetOV_(a)	(_GetOV(_PSW(_GetDateMem((a)))))
#define _GetP(a)	((a)&0x01)
#define _GetP_(a)	(_GetP(_PSW(_GetDateMem((a)))))
#define _GetRS(a)	(((a)>>3)&0x3)

/*设置PSW中的各位*/
#define _SetC(a)	((a)=((a)|0x80))
#define _SetC_(a)	(_SetC(_PSW(_GetDateMem((a)))))
#define _SetAC(a)	((a)=((a)|0x40))
#define _SetAC_(a)	(_SetAC(_PSW(_GetDateMem((a)))))
#define _SetF0(a)	((a)=((a)|0x20))
#define _SetRS1(a)	((a)=((a)|0x10))
#define _SetRS0(a)	((a)=((a)|0x08))
#define _SetOV(a)	((a)=((a)|0x04))
#define _SetOV_(a)	(_SetOV(_PSW(_GetDateMem((a)))))
#define _SetP(a)	((a)=((a)|0x01))
#define _SetP_(a)	(_SetP(_PSW(_GetDateMem((a)))))

/*清除PSW中的各位*/
#define _ClrC(a)	((a)^=((a)&0x80))
#define _ClrC_(a)	(_ClrC(_PSW(_GetDateMem((a)))))
#define _ClrAC(a)	((a)^=((a)&0x40))
#define _ClrAC_(a)	(_ClrAC(_PSW(_GetDateMem((a)))))
#define _ClrF0(a)	((a)^=((a)&0x20))
#define _ClrRS1(a)	((a)^=((a)&0x10))
#define _ClrRS0(a)	((a)^=((a)&0x08))
#define _ClrOV(a)	((a)^=((a)&0x04))
#define _ClrOV_(a)	(_ClrOV(_PSW(_GetDateMem((a)))))
#define _ClrP(a)	((a)^=((a)&0x01))
#define _ClrP_(a)	(_ClrP(_PSW(_GetDateMem((a)))))

/*获取寄存器组的指针*/
#define _REG_BLOCK_0(a) ((a)+0x00)
#define _REG_BLOCK_1(a) ((a)+0x08)
#define _REG_BLOCK_2(a) ((a)+0x10)
#define _REG_BLOCK_3(a) ((a)+0x18)

#define _REG_0(a)	(*((a)+0))
#define _REG_1(a)	(*((a)+1))
#define _REG_2(a)	(*((a)+2))
#define _REG_3(a)	(*((a)+3))
#define _REG_4(a)	(*((a)+4))
#define _REG_5(a)	(*((a)+5))
#define _REG_6(a)	(*((a)+6))
#define _REG_7(a)	(*((a)+7))

#define _SET_0_REG_0(a)	(*((a)+0))
#define _SET_0_REG_1(a)	(*((a)+1))
#define _SET_0_REG_2(a)	(*((a)+2))
#define _SET_0_REG_3(a)	(*((a)+3))
#define _SET_0_REG_4(a)	(*((a)+4))
#define _SET_0_REG_5(a)	(*((a)+5))
#define _SET_0_REG_6(a)	(*((a)+6))
#define _SET_0_REG_7(a)	(*((a)+7))

#define _SET_1_REG_0(a)	(*((a)+0x08+0))
#define _SET_1_REG_1(a)	(*((a)+0x08+1))
#define _SET_1_REG_2(a)	(*((a)+0x08+2))
#define _SET_1_REG_3(a)	(*((a)+0x08+3))
#define _SET_1_REG_4(a)	(*((a)+0x08+4))
#define _SET_1_REG_5(a)	(*((a)+0x08+5))
#define _SET_1_REG_6(a)	(*((a)+0x08+6))
#define _SET_1_REG_7(a)	(*((a)+0x08+7))

#define _SET_2_REG_0(a)	(*((a)+0x10+0))
#define _SET_2_REG_1(a)	(*((a)+0x10+1))
#define _SET_2_REG_2(a)	(*((a)+0x10+2))
#define _SET_2_REG_3(a)	(*((a)+0x10+3))
#define _SET_2_REG_4(a)	(*((a)+0x10+4))
#define _SET_2_REG_5(a)	(*((a)+0x10+5))
#define _SET_2_REG_6(a)	(*((a)+0x10+6))
#define _SET_2_REG_7(a)	(*((a)+0x10+7))

#define _SET_3_REG_0(a)	(*((a)+0x18+0))
#define _SET_3_REG_1(a)	(*((a)+0x18+1))
#define _SET_3_REG_2(a)	(*((a)+0x18+2))
#define _SET_3_REG_3(a)	(*((a)+0x18+3))
#define _SET_3_REG_4(a)	(*((a)+0x18+4))
#define _SET_3_REG_5(a)	(*((a)+0x18+5))
#define _SET_3_REG_6(a)	(*((a)+0x18+6))
#define _SET_3_REG_7(a)	(*((a)+0x18+7))


#define _SET_BIT(a,b) ((a)|=(1<<(b)))
#define _CLR_BIT(a,b) ((a)&=~(1<<(b)))
#define _GET_BIT(a,b) (((a)>>(b))&0x1)
/*检测最高位，如果为1，则转换为int8_t 否则，uint8_t*/
#define _S_CK_TRAN(a) ((a)&0x80?(int8_t)(a):(uint8_t)(a))


void Core51NOP(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51AJMP_ADDR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51LJMP_ADDR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51RR_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51INC_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51INC_D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51INC_SR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51INC_R(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51JBC(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ACALL(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51LCALL(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51RRC_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51DEC_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51DEC_D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51DEC_SR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51DEC_R(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51JB(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51RET(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51RL_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ADD_AaddSD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ADD_AaddD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ADD_AaddSR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ADD_AaddR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51JNB(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51RETI(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51RLC_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ADDC_AaddSD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ADDC_AaddD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ADDC_AaddSR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ADDC_AaddR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51JC(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ORL_DA(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ORL_DSD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ORL_ASD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ORL_AD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ORL_ASR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ORL_AR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51JNC(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ANL_DA(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ANL_DSD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ANL_ASD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ANL_AD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ANL_ASR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ANL_AR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51JZ(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51XRL_DA(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51XRL_DSD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51XRL_ASD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51XRL_AD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51XRL_ASR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51XRL_AR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51JNZ(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ORL_Cbit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51JMP_AaddrDPTR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_SD2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_SD2D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_SD2SR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_SD2R(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51SJMP_ADDR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ANL_Cbit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOVC_SAaddPC2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51DIV_AB(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_D2D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_SR2D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_R2D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_SD162DPTR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_bitC(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOVC_SAaddDPRT2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51SUBB_AsubSD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51SUBB_AsubD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51SUBB_AsubSR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51SUBB_AsubR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ORL_Cnbit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_Cbit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51INC_DPTR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MUL_AB(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_D2SR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_D2R(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51ANL_Cnbit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51CPL_bit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51CPL_C(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51CJNE_ASDr(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51CJNE_ADr(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51CJNE_SRSDr(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51CJNE_RSDr(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51PUSH_D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51CLR_bit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51CLR_C(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51SWAP_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51XCH_AD(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51XCH_ASR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51XCH_AR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51POP_D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51SETB_bit(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51SETB_C(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51DA_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51DJNZ_Dr(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51XCHD_ASR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51DJNZ_Rr(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOVX_SDPTR2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOVX_SR2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51CLR_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_D2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_SR2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_R2A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOVX_A2SDPTR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOVX_A2SR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51CPL_A(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_A2D(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_A2SR(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void Core51MOV_A2R(HCORE_51 hCore51, uint8_t* regSet, uint8_t* pcMemByte);

void		Core51Init(HCORE_51 hCore51, uint8_t* rom, uint8_t* exMem);
Core51Err	Core51Run(HCORE_51 hCore51);


#endif


