#include "cpu/exec/template-start.h"

#define instr jmp
//#if DATA_BYTE == 1

static void do_execute(){    //for imm
	
//	if( op_src->type == OP_TYPE_IMM )
		cpu.eip += op_src->val;

	if(DATA_BYTE == 2)
		cpu.eip = cpu.eip & 0x0000ffff;
	
//	if(op_src->type == OP_TYPE_IMM)
	{	
		if(DATA_BYTE == 1)
			print_asm(str(instr) " %x",cpu.eip+1+1);
		else
			print_asm(str(instr) " %x",cpu.eip+1+4);
	}
}
/*make_helper(concat3(instr,_si_,SUFFIX)){
	
	int len;
	if(DATA_BYTE == 1)
		len=decode_si_b(eip+1);
	else
		len=decode_si_l(eip+1);
	do_execute();

	return 1+len;
}
*/
make_instr_helper(si)
#if DATA_BYTE == 2 || DATA_BYTE == 4
//make_instr_helper(rm)
make_helper(concat3(instr,_rm_,SUFFIX)){
	concat( decode_rm_,SUFFIX)(eip+1);
	
	cpu.eip = op_src->val;

	if(DATA_BYTE == 2)
		cpu.eip = cpu.eip & 0x0000ffff;
	
	print_asm(str(instr) " *%s",op_src->str);

	return 0;

	
	}
#endif
//#endif

#include "cpu/exec/template-end.h"
