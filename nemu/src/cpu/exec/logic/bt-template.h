#include "cpu/exec/template-start.h"

#define instr bt

static void do_execute(){
	
	int offset = op_dest->val % (8*DATA_BYTE);
	Log("%x,%x",op_src->val,op_dest->val);
	cpu.CF = op_src->val<<(31-offset)>>offset;
	print_asm_template2();
	
}

make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
