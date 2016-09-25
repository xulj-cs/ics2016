#include "cpu/exec/template-start.h"

#define instr jz
//#if DATA_BYTE == 1

static void do_execute(){
	
	if(cpu.ZF)
	{	
		cpu.eip += op_src->val;
		if(DATA_BYTE == 2)
			cpu.eip = cpu.eip & 0x0000ffff;
	}
	print_asm_template1();
}

make_instr_helper(i)
//#endif

#include "cpu/exec/template-end.h"
