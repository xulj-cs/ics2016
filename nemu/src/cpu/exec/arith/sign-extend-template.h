#include "cpu/exec/template-start.h"

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_helper(concat(sign_extend_,SUFFIX)){

	#if DATA_BYTE == 2
	reg_w(R_EAX)=((int16_t)reg_b(R_EAX))<<8 >>8;
	#endif

	#if DATA_BYTE == 4
	reg_l(R_EAX)=((int32_t)reg_w(R_EAX))<<16 >>16;
	#endif

	print_asm("sign_extend");
	return 1;
}
#endif

#include "cpu/exec/template-end.h"
