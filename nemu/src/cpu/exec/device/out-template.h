#include "cpu/exec/template-start.h"

#define instr out

make_helper(concat(out_a2i_,SUFFIX)){
	int len = concat(decode_i_,SUFFIX)(eip+1);
	pio_write(op_src->val,DATA_BYTE,REG(R_EAX));
	print_asm(str(instr) str(SUFFIX) " (%s),%s",op_src->str,REG_NAME(R_EAX));	
	return len+1;
}

make_helper(concat(out_a2d_,SUFFIX)){

	pio_write(REG(R_EDX),DATA_BYTE,REG(R_EAX));
	print_asm(str(instr) str(SUFFIX) " (%s),%s",REG_NAME(R_EAX),REG_NAME(R_EDX));
	return 1;
}
#include "cpu/exec/template-end.h"
