#include "cpu/exec/template-start.h"

#define instr lidt

static void do_execute(){
	swaddr_t addr=op_src->addr;
	
	cpu.IDTR.Limit=swaddr_read(addr,2,0);
	cpu.IDTR.Base=(swaddr_t)swaddr_read((swaddr_t)(addr+2),4,0);

	print_asm_template1();
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"

