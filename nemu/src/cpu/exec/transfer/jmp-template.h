#include "cpu/exec/template-start.h"

#define instr jmp
//#if DATA_BYTE == 1

static void do_execute(){
	
	cpu.eip += op_src->val;

	if(DATA_BYTE == 2)
		cpu.eip = cpu.eip & 0x0000ffff;
	if(DATA_BYTE == 1)
		print_asm(str(instr) " %x",cpu.eip+1+1);
	else
		print_asm(str(instr) " %x",cpu.eip+1+4);
}

make_instr_helper(i)
//#endif

#include "cpu/exec/template-end.h"
