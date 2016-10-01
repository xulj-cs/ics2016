#include "cpu/exec/template-start.h"

#define instr movsx

//static void do_execute(){
//	OPERAND_W (op_dest,op_src->val);
//	print_asm_template2();
//}

make_helper ( concat(movsx_srmb2r_,SUFFIX )){
	
	op_src->size = 1;
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	op_dest->type = OP_TYPE_REG;
	op_dest->reg = m.reg;
	int len;
	if(m.mod == 3){
		op_src->type = OP_TYPE_REG;
		op_src->reg = m.R_M;
		op_src->val = (int8_t)reg_b(m.R_M);

		len = 1;
	}

	else
	{
		len = load_addr( eip+1, &m , op_src);
		op_src -> val = (int8_t)swaddr_read(op_src->addr,op_src->size);
		
	}
	
//	do_execute();
	OPERAND_W (op_dest,op_src->val);

	print_asm(str(movsb)str(SUFFIX) " %s,%s",op_src->str,op_dest->str);

	return 1+len; 
}

#if DATA_BYTE == 4
make_helper(movsx_srmw2r_l){
	
	op_src->size = 2;
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	op_dest->type = OP_TYPE_REG;
	op_dest->reg = m.reg;
	int len;
	if(m.mod == 3){
		op_src->type = OP_TYPE_REG;
		op_src->reg = m.R_M;
		op_src->val = (int8_t)reg_w(m.R_M);

		len = 1;
	}

	else
	{
		len = load_addr( eip+1, &m , op_src);
		op_src -> val = (int8_t)swaddr_read(op_src->addr,op_src->size);
		
	}
	
//	do_execute();

	OPERAND_W (op_dest,op_src->val);

	print_asm(str(movsw)str(SUFFIX) " %s,%s",op_src->str,op_dest->str);
	return 1+len; 
	
	
}
#endif

#include "cpu/exec/template-end.h"





