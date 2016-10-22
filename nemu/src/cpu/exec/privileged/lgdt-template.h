#include "cpu/exec/template-start.h"

#define instr lgdt

static void do_execute(){
	swaddr_t addr=op_src->addr;
	
	cpu.GDTR.Limit=swaddr_read(addr,2,0);
	cpu.GDTR.Base=(swaddr_t)swaddr_read((swaddr_t)(addr+2),4,0);

	Log("%x,%x",swaddr_read(addr,4,0),swaddr_read(addr+4,4,0));	
	print_asm_template1();
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"

