#include "cpu/exec/template-start.h"
#include "cpu/decode/modrm.h"
#define instr add

//#if DATA_BYTE == 2 ||DATA_BYTE == 4 
static void do_execute()
{
	DATA_TYPE result;
	//if(DATA_BYTE == 2 || DATA_BYTE == 4)
	//	result = op_dest->val - (DATA_TYPE_S)op_src->val;
	//else
		result = op_dest->val + op_src->val;
	
	OPERAND_W(op_dest,result);

//	Log("%d-%d\n",op_dest->val,op_src->val);
	
	cpu.OF=concat(OF_,SUFFIX)(op_dest->val,op_src->val,'+');
	cpu.SF=MSB(result);
	cpu.ZF=!result;
	cpu.PF=concat(PF_,SUFFIX)(result);
	cpu.CF=concat(CF_,SUFFIX)(op_dest->val,op_src->val,'+');

	print_asm_template2();

}
make_instr_helper(r2rm)

//#endif

#include "cpu/exec/template-end.h"
