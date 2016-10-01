#include "cpu/exec/template-start.h"
#define instr push


static void do_execute(){
/*	if(op_src->type == OP_TYPE_IMM )
		reg_l(R_ESP) -= 4;
	else
*/
		reg_l(R_ESP) -= DATA_BYTE;
	MEM_W(reg_l(R_ESP),op_src->val);

	print_asm_template1();
}
#if DATA_BYTE == 2 || DATA_BYTE == 4

make_instr_helper(r)
make_instr_helper(rm)   //in fact only can be m

#endif

make_instr_helper(i)
#include "cpu/exec/template-end.h"
