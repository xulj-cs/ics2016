#include "cpu/exec/template-start.h"
#define instr cmp

#if DATA_BYTE == 2 ||DATA_BYTE == 4 
static void do_execute()
{
	DATA_TYPE result;
	result = op_dest->val - op_src->val;
	Log("%d%d",op_dest->val,op_src->val);
	cpu.OF=concat(OF_,SUFFIX)(op_dest->val,op_src->val,'-');
	cpu.SF=MSB(result);
	cpu.ZF=!result;
	cpu.PF=concat(PF_,SUFFIX)(result);
	cpu.CF=concat(CF_,SUFFIX)(op_dest->val,op_src->val,'-');
	print_asm_template2();
}
make_helper(concat(cmp_ib2rm_,SUFFIX))
{
	int len = concat(decode_rm_,SUFFIX)(eip);
	
	op_src->type=OP_TYPE_IMM;
	op_src->imm=instr_fetch(eip+1+len,1);
	op_src->val = op_src->imm;
	
	len +=2;
	Log("%d",len);
	do_execute();

	return len;
}

#endif

#include "cpu/exec/template-end.h"
