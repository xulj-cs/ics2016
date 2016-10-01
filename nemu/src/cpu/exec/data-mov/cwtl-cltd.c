#include "cpu/exec/helper.h"
#include "cpu/reg.h"

make_helper(cwtl){
	if((int16_t)reg_w(R_EAX)<0)
		reg_w(R_EDX)=0x0ffff;
	else
		reg_w(R_EDX)=0;
	
	print_asm(str(cwtl));
	return 1;
		
	}

make_helper(cltd){
	if((int32_t)reg_l(R_EAX)<0 )
		reg_l(R_EDX)= 0xffffffff;
	else
		reg_l(R_EDX)=0;
	
	print_asm(str(cltd));
	return 1;
	}

make_helper(cwtlORcltd){
	return (ops_decoded.is_operand_size_16? cwtl:cltd)(eip);
	}
