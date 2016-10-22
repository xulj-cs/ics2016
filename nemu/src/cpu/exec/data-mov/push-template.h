#include "cpu/exec/template-start.h"
#define instr push


static void do_execute(){
	if(op_src->type == OP_TYPE_IMM ){
		
		if(ops_decoded.is_operand_size_16){
			reg_l(R_ESP) -= 2;
			swaddr_write(reg_l(R_ESP),2,op_src->val,SS);

		}
		else
		{
			reg_l(R_ESP) -= 4;
			swaddr_write(reg_l(R_ESP),4,op_src->val,SS);
		}
		
	}
	else

		reg_l(R_ESP) -= DATA_BYTE;
	MEM_W(reg_l(R_ESP),op_src->val,SS);

	print_asm_template1();
}
#if DATA_BYTE == 2 || DATA_BYTE == 4

make_instr_helper(r)
make_instr_helper(rm)   //in fact only can be m
/*
make_helper(concat(push_rm_,SUFFIX)){

	int len=concat(decode_rm_,SUFFIX)(eip+1);
	if(op_src->type==OP_TYPE_REG)
	{	
		op_src->val=MEM_R(op_src->val);

		reg_l(R_ESP) -=DATA_BYTE;
		MEM_W(reg_l(R_ESP),op_src->val);
	
		print_asm(str(instr) str(SUFFIX) " *%s",op_src->str);
	}
	else
		do_execute();
	return len+1;

}
*/
#endif

make_instr_helper(si)
#include "cpu/exec/template-end.h"
