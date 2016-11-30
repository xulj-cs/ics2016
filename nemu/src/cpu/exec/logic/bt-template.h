#include "cpu/exec/template-start.h"

#define instr bt

static void do_execute(){
	
	int offset = op_src->val % (8*DATA_BYTE);
	cpu.CF = op_dest->val<<(31-offset)>>offset;
	print_asm_template2();
	
}

make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
