#include "cpu/exec/template-start.h"

#define instr in

static void do_execute(){

	OPERAND_W(op_dest ,pio_read(op_src->val,DATA_BYTE));
	print_asm(str(instr) " (%s),%s",op_src->str,op_dest->str);

}

make_instr_helper(i2r)
make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
