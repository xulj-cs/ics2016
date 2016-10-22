#include "cpu/exec/template-start.h"

#define instr lods

make_helper(concat(lods_,SUFFIX)){
	 REG(R_EAX) =  MEM_R( reg_l(R_ESI),DS ) ;
	if(!cpu.DF){
		reg_l(R_ESI)+=DATA_BYTE;
	}
	else{
		reg_l(R_ESI)-=DATA_BYTE;
	}
	print_asm(str(instr) str(SUFFIX) " %s%%%s","%ds:(%esi),",REG_NAME(R_EAX));
//	print_asm(str(%ds:(%esi),%es:(%edi)));
	return 1;
}

#include "cpu/exec/template-end.h"
