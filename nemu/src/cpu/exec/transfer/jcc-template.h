#include "cpu/exec/template-start.h"

//#define instr jz
//#if DATA_BYTE == 1

static void do_execute(){
	
	#ifdef JZ
	if(cpu.ZF)
	#endif

	#ifdef JBE
	if(cpu.ZF || cpu.CF)
	#endif

	#ifdef JLE
	if(cpu.ZF || cpu.SF!=cpu.OF)
	#endif

	{	
		cpu.eip += op_src->val;
		if(DATA_BYTE == 2)
			cpu.eip = cpu.eip & 0x0000ffff;
	}
	if(DATA_BYTE==1)
		print_asm(str(instr) " %x",cpu.eip+1+1);
	else
		print_asm(str(instr) " %x",cpu.eip+1+4);
}
//#if DATA_BYTE == 1 ||DATA_BYTE == 4
//make_instr_helper(si)
//#endif
//#endif
make_helper(concat3(instr,_si_,SUFFIX)){
	
	int len;
	if(DATA_BYTE == 1)
		len=decode_si_b(eip+1);
	else
		len=decode_si_l(eip+1);
	do_execute();

	return 1+len;
		
	
	}
#include "cpu/exec/template-end.h"
