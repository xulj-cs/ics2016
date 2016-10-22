#include "cpu/exec/template-start.h"

#define instr stos

make_helper(concat(stos_,SUFFIX)){
	// REG(R_EAX) =  MEM_R( reg_l(R_ESI) ) ;
	MEM_W( reg_l(R_EDI) , REG(R_EAX),ES);
	if(!cpu.DF){
		reg_l(R_EDI)+=DATA_BYTE;
	}
	else{
		reg_l(R_EDI)-=DATA_BYTE;
	}
	print_asm(str(instr) str(SUFFIX) " %%%s%s", REG_NAME(R_EAX) ,",%es:(%edi)");
//	print_asm(str(%ds:(%esi),%es:(%edi)));
	return 1;
}

#include "cpu/exec/template-end.h"
