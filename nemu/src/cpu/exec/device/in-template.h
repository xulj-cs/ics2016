#include "cpu/exec/template-start.h"

#define instr in

static void do_execute(){

	OPERAND_W(op_dest ,pio_read(op_src->val,DATA_BYTE));
	print_asm(str(instr) str(SUFFIX) " (%s),%s",op_src->str,op_dest->str);

}

make_instr_helper(i2a)


make_helper(concat(in_d2a_,SUFFIX)){

	REG(R_EAX) = pio_read(REG(R_EDX),DATA_BYTE);
	print_asm(str(instr) str(SUFFIX) " (%s),%s",REG_NAME(R_EDX),REG_NAME(R_EAX));
	return 1;
}
#include "cpu/exec/template-end.h"
