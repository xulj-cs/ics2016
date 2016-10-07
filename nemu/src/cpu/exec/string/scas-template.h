#include "cpu/exec/template-start.h"

#define instr scas

make_helper(concat(scas_,SUFFIX)){
	DATA_TYPE  result = REG(R_EAX) -  MEM_R( reg_l(R_EDI) ) ;
	if(!cpu.DF){
		reg_l(R_EDI)+=DATA_BYTE;
	}
	else{
		reg_l(R_EDI)-=DATA_BYTE;
	}
	
	cpu.OF=concat(OF_,SUFFIX)( REG(R_EAX),MEM_R( reg_l(R_EDI) ),'-' );
	cpu.SF=MSB(result);
	cpu.ZF=!result;
	cpu.PF=concat(PF_,SUFFIX)(result);
	cpu.CF=concat(CF_,SUFFIX)( REG(R_EAX),MEM_R( reg_l(R_EDI)), '-' );

	print_asm(str(instr) str(SUFFIX) " %s%s","%es:(%edi),%",REG_NAME(R_EAX));
//	print_asm(str(%ds:(%esi),%es:(%edi)));
	return 1;
}

#include "cpu/exec/template-end.h"
