#include "cpu/exec/template-start.h"

#define instr in
/*
make_helper(concat(in_i2a_,SUFFIX)){
	int len = docode_i_b( eip+1 );
	OPERAND_W(op_dest ,pio_read(op_src->val,DATA_BYTE));
	print_asm(str(instr) str(SUFFIX) " (%s),%s",op_src->str,op_dest->str);

}
*/


make_helper(concat(in_d2a_,SUFFIX)){

	REG(R_EAX) = pio_read(reg_w(R_EDX),DATA_BYTE );
	print_asm(str(instr) str(SUFFIX) " (%%%s),%%%s",regsw[R_EDX],REG_NAME(R_EAX));
	return 1;
}
#include "cpu/exec/template-end.h"
