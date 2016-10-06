#include "cpu/exec/helper.h"

#include "cpu/reg.h"

#define MEM_R(addr) swaddr_read(addr,DATA_BYTE)

#define DATA_BYTE 2
make_helper(ret_near_w){
	cpu.ip=MEM_R(reg_l(R_ESP));
	cpu.eip = cpu.eip & 0x0000ffff;
	reg_l(R_ESP) += DATA_BYTE;
	print_asm(str(ret));
	return 0;
}
#undef DATA_BYTE


#define DATA_BYTE 4
make_helper(ret_near_l){
	cpu.eip=MEM_R(reg_l(R_ESP));
	
	reg_l(R_ESP) += DATA_BYTE;

	print_asm(str(ret));
	return 0;
}
#undef DATA_BYTE

make_helper(ret_near_i_w){
	reg_l(R_ESP) += decode_i_w(eip+1);
	ret_near_w(eip);
	return 0;
}

make_helper(ret_near_i_l){
	reg_l(R_ESP) += decode_i_w(eip+1);
	ret_near_l(eip);
	return 0;
}



make_helper_v(ret_near)
make_helper_v(ret_near_i)
