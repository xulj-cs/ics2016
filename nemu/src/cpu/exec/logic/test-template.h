#include "cpu/exec/template-start.h"
#define instr test
/*int concat(bool_PF__,SUFFIX)(DATA_TYPE n)
{
	int c=0;
	int i=8;
	while(i--)
	{	c += n&1;
		n >>=1;
	}
	if(c%2==0)
		return 1;
	else
		return 0;
}
*/
static void do_execute( ){
	//DATA_TYPE op_dest_val=MEM_R(op_dest);
	DATA_TYPE op_dest_val;
//	if (op_dest->type==OP_TYPE_REG)
	{
		op_dest_val=REG(op_dest->reg);
	}
	DATA_TYPE result=op_dest_val & op_src -> val;
	cpu.OF = cpu.CF = 0;
	cpu.ZF = ! result;
	cpu.SF = MSB(result);
	cpu.PF = concat(PF_,SUFFIX)(result);

	print_asm_template2();
}
make_instr_helper(r2rm)
make_instr_helper(i2rm)
make_instr_helper(i2a)
#include "cpu/exec/template-end.h"
