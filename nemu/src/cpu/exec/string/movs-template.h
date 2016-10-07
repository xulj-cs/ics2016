#include "cpu/exec/template-start.h"

#define instr movs


make_helper(concat(movs_,SUFFIX)){
	MEM_W( reg_l(R_EDI) , MEM_R( reg_l(R_ESI) ) );
	if(!cpu.DF){
		reg_l(R_EDI)+=DATA_BYTE;
		reg_l(R_ESI)+=DATA_BYTE;
	}
	else{
		reg_l(R_EDI)-=DATA_BYTE;
		reg_l(R_ESI)-=DATA_BYTE;
	}
	print_asm(str(instr) str(SUFFIX) " %s","%ds:(%esi),%es:(%edi)");
//	print_asm(str(%ds:(%esi),%es:(%edi)));
	return 1;
}

#include "cpu/exec/template-end.h"
