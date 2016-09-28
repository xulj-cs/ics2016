#include "cpu/exec/template-start.h"
#include "cpu/decode/modrm.h"
#define instr sub

#if DATA_BYTE == 2 ||DATA_BYTE == 4 
static void do_execute()
{
	DATA_TYPE_S result;
	if(DATA_BYTE == 2 || DATA_BYTE == 4)
		result = op_dest->val - (DATA_TYPE_S)op_src->val;
	else
		result = op_dest->val - op_src->val;
	
	OPERAND_W(op_dest,result);

//	Log("%d-%d\n",op_dest->val,op_src->val);
	
	cpu.OF=concat(OF_,SUFFIX)(op_dest->val,op_src->val,'-');
	cpu.SF=MSB(result);
	cpu.ZF=!result;
	cpu.PF=concat(PF_,SUFFIX)(result);
	cpu.CF=concat(CF_,SUFFIX)(op_dest->val,op_src->val,'-');

	print_asm_template2();

}
/*make_helper(concat(sub_ib2rm_,SUFFIX))
{
	//
	int len = concat(decode_rm_,SUFFIX)(eip +1);
	op_dest->type=OP_TYPE_IMM;
	op_dest->imm=instr_fetch(eip+1+len,1);
	op_dest->val = op_dest->imm;
	snprintf(op_dest->str, OP_STR_SIZE, "$0x%x", op_dest->imm);	
	len +=2;
	//
	op_dest->size = DATA_BYTE;
	int len =read_ModR_M( eip+1 ,op_dest,op_src2);
//	snprintf(op_src2->str, OP_STR_SIZE, "%%%s", REG_NAME(reg->reg));
	op_src->type=OP_TYPE_IMM;
	op_src->imm=instr_fetch(eip+1+len,1);
	op_src->val = op_src->imm;
	snprintf(op_src->str, OP_STR_SIZE, "$0x%x", op_src->imm);	


	do_execute();

	return len+1+1;
}
*/
make_instr_helper(rm_imm)

#endif

#include "cpu/exec/template-end.h"
