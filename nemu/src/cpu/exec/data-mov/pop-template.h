#include "cpu/exec/template-start.h"

#define instr pop

#if DATA_BYTE == 2 || DATA_BYTE == 4

static void do_execute(){
	OPERAND_W( op_src , MEM_R(reg_l(R_ESP)) );
	reg_l(R_ESP) += DATA_BYTE;

	print_asm_template1();
}


make_instr_helper(r)
make_instr_helper(rm)  //in fact only can be m

#endif

#include "cpu/exec/template-end.h"
