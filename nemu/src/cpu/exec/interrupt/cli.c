#include "cpu/exec/helper.h"
#define instr cli

make_helper(cli){

	cpu.IF = 0;
	print_asm(str(instr));
	return 1;
}

