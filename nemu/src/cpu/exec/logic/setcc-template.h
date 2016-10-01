#include "cpu/exec/template-start.h"

//#define instr jz
//#if DATA_BYTE == 1

static void do_execute(){
	

#ifdef SETA
	if(!cpu.CF && !cpu.ZF)
#endif 

#ifdef SETAE
	if(!cpu.CF)
#endif

#ifdef SETB
	if(cpu.CF)
#endif

#ifdef SETBE
	if(cpu.ZF || cpu.CF)
#endif

//SETC == SETB

#ifdef SETE
	if(cpu.ZF)
#endif
	
//SETZ == SETE

#ifdef SETG
	if(!cpu.ZF && cpu.SF==cpu.OF)
#endif

#ifdef SETGE
	if(cpu.SF==cpu.OF)
#endif

#ifdef SETL
	if(cpu.SF!=cpu.OF)
#endif

#ifdef SETLE
	if(cpu.ZF || cpu.SF!=cpu.OF)
#endif

//SETNA == SETBE

//SETNAE == SETB

//SETNB == SETAE

//SETNBE == SETA

//SETNC == SETAE
	
#ifdef SETNE
	if(!cpu.ZF)
#endif

//SETNG == SETLE

//SETNGE == SETL

//SETNL == SETGE

//SETNLE ==  SETG

#ifdef SETNO
	if( !cpu.OF )
#endif

#ifdef SETNP
	if( !cpu.PF)
#endif

#ifdef SETNS
	if( !cpu.SF)
#endif

//SETNZ == SETNE

#ifdef SETO
	if( cpu.OF)
#endif

#ifdef SETP
	if( cpu.PF)
#endif

//SETPE == SETP

//SETPO == SETNP

#ifdef SETS
	if( cpu.SF)
#endif

//SETZ ==SETE

	{	
		OPERAND_W(op_src,1);
	}
	else
	{
		OPERAND_W(op_src,0);
	}

	print_asm_template1();
}
//#if DATA_BYTE == 1 ||DATA_BYTE == 4
//make_instr_helper(si)
//#endif


make_instr_helper(rm)
#include "cpu/exec/template-end.h"
