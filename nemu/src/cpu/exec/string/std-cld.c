#include "cpu/exec/helper.h"
#define instr std

make_helper(std){

	cpu.DF = 1;
	print_asm_template1();
	return 1;
}

#undef instr

#define instr cld

make_helper(cld){

	cpu.DF = 0;
	print_asm_template1();
	return 1;
}
