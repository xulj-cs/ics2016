#include "cpu/exec/helper.h"

#include "cpu/reg.h"


#define DATA_BYTE 2
#include "cpu/exec/template-start.h" 
make_helper(concat(leave_,SUFFIX)){
	reg_l(R_ESP)=reg_l(R_EBP);
	
	REG(R_EBP)= MEM_R( reg_l(R_ESP) ) ;

	reg_l(R_ESP) +=DATA_BYTE;

	print_asm(str(leave));

	return 1;
}
#include "cpu/exec/template-end.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cpu/exec/template-start.h"
make_helper(concat(leave_,SUFFIX)){
	reg_l(R_ESP)=reg_l(R_EBP);
	
	REG(R_EBP)=MEM_R(reg_l(R_ESP));

	reg_l(R_ESP) +=DATA_BYTE;

	print_asm(str(leave));

	return 1;
}
#include "cpu/exec/template-end.h"
#undef DATA_BYTE

make_helper_v(leave)
