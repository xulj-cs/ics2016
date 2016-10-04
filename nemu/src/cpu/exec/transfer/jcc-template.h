#include "cpu/exec/template-start.h"

//#define instr jz
//#if DATA_BYTE == 1

static void do_execute(){
	
//#if DATA_BYTE == 
//	JCXZ JECXZ????

#ifdef JA
	if(!cpu.CF && !cpu.ZF)
#endif 

#ifdef JAE
	if(!cpu.CF)
#endif

#ifdef JB
	if(cpu.CF)
#endif

#ifdef JBE
	if(cpu.ZF || cpu.CF)
#endif

//JC == JB

#ifdef JE
	if(cpu.ZF)
#endif
	
//JZ == JE

#ifdef JG
	if(!cpu.ZF && cpu.SF==cpu.OF)
#endif

#ifdef JGE
	if(cpu.SF==cpu.OF)
#endif

#ifdef JL
	if(cpu.SF!=cpu.OF)
#endif

#ifdef JLE
	if(cpu.ZF || cpu.SF!=cpu.OF)
#endif

//JNA == JBE

//JNAE == JB

//JNB == JAE

//JNBE == JA

//JNC == JAE
	
#ifdef JNE
	if(!cpu.ZF)
#endif

//JNG == JLE

//JNGE == JL

//JNL == JGE

//JNLE ==  JG

#ifdef JNO
	if( !cpu.OF )
#endif

#ifdef JNP
	if( !cpu.PF)
#endif

#ifdef JNS
	if( !cpu.SF)
#endif

//JNZ == JNE

#ifdef JO
	if( cpu.OF)
#endif

#ifdef JP
	if( cpu.PF)
#endif

//JPE == JP

//JPO == JNP

#ifdef JS
	if( cpu.SF)
#endif

//JZ ==JE

	{	
		cpu.eip += op_src->val;
		if(DATA_BYTE == 2)
			cpu.eip = cpu.eip & 0x0000ffff;
	}
	if(DATA_BYTE==1)
		print_asm(str(instr) " %x",cpu.eip+1+1);
	else
		print_asm(str(instr) " %x",cpu.eip+2+4);
}
//#if DATA_BYTE == 1 ||DATA_BYTE == 4
make_instr_helper(si)
//#endif
//#endif
/*make_helper(concat3(instr,_si_,SUFFIX)){
	
	int len;
	if(DATA_BYTE == 1)
		len=decode_si_b(eip+1);
	else
		len=decode_si_l(eip+1);
	do_execute();

	return 1+len;
		
	
	}
	*/
#include "cpu/exec/template-end.h"
