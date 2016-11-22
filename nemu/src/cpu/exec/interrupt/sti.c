#include "cpu/exec/helper.h"
#define instr sti

make_helper(sti){

	cpu.IF = 1;
	print_asm(str(instr));
	return 1;
}

