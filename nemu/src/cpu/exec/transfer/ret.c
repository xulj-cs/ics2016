#include "cpu/exec/helper.h"


#define MEM_R(addr,sreg) swaddr_read(addr,DATA_BYTE,sreg)

#define DATA_BYTE 2
make_helper(ret_near_w){
	cpu.ip=MEM_R(reg_l(R_ESP),SS);
	cpu.eip = cpu.eip & 0x0000ffff;
	reg_l(R_ESP) += DATA_BYTE;
	print_asm(str(ret));
	return 0;
}

make_helper(ret_near_i_w){
	//ret_near_w(eip);
	cpu.ip=MEM_R(reg_l(R_ESP),SS);
	cpu.eip = cpu.eip & 0x0000ffff;
	reg_l(R_ESP) += DATA_BYTE;
	
	decode_i_w(eip+1);
	reg_l(R_ESP) += op_src->val;
	
	print_asm(str(ret) " $0x%x",op_src->val);
	return 0;
}
#undef DATA_BYTE


#define DATA_BYTE 4
make_helper(ret_near_l){
	cpu.eip=MEM_R(reg_l(R_ESP),SS);
	//Log("eip==0x%x\n",cpu.eip);	
	reg_l(R_ESP) += DATA_BYTE;

	print_asm(str(ret));
	return 0;
}

make_helper(ret_near_i_l){
	//	ret_near_l(eip);
	cpu.eip=MEM_R(reg_l(R_ESP),SS);
	
	reg_l(R_ESP) += DATA_BYTE;

	decode_i_w(eip+1);
	reg_l(R_ESP) +=  op_src->val;

	print_asm(str(ret) " $0x%x",op_src->val);

	return 0;
}

#undef DATA_BYTE


make_helper_v(ret_near)
make_helper_v(ret_near_i)
