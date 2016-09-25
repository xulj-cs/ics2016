#include "cpu/exec/helper.h"

#include "cpu/reg.h"

#define MEM_R(addr) swaddr_read(addr,DATA_BYTE)

#define DATA_BYTE 2
make_helper(ret_w){
	cpu.ip=MEM_R(reg_l(R_ESP));
	eip = eip & 0x0000ffff;
	reg_l(R_ESP) += DATA_BYTE;
	
	print_asm_template1();
	return 0;
}
#undef DATA_BYTE

#define DATA_BYTE 4
make_helper(ret_l){
	cpu.eip=MEM_R(reg_l(R_ESP));
	
	reg_l(R_ESP) += DATA_BYTE;

	print_asm_template1();
	return 0;
}
#undef DATA_BYTE



make_helper_v(ret)
