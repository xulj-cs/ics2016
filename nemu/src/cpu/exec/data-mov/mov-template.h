#include "cpu/exec/template-start.h"

#define instr mov

static void do_execute() {
	OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}

make_instr_helper(i2r)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

make_helper(concat(mov_a2moffs_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	MEM_W(addr, REG(R_EAX),DS);

	print_asm("mov" str(SUFFIX) " %%%s,0x%x", REG_NAME(R_EAX), addr);
	return 5;
}

make_helper(concat(mov_moffs2a_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	REG(R_EAX) = MEM_R(addr,DS);

	print_asm("mov" str(SUFFIX) " 0x%x,%%%s", addr, REG_NAME(R_EAX));
	return 5;
}
#if DATA_BYTE == 4
make_helper(mov_r2cr){
	int len=decode_rm_l(eip+1);
	Assert(op_src->type == OP_TYPE_REG,"mod!=3");

	if(op_src2->reg==0)
		cpu.cr0.val=op_src->val;
	else if(op_src2->reg==3)
		cpu.cr3.val=op_src->val;
	else
		panic("no this CR");
	Log("here!");
	print_asm(str(instr) " %s,%%cr%d",op_src->str,op_src2->reg);
	return len+1;
}

make_helper(mov_cr2r){
	int len=decode_rm_l(eip+1);
	Assert(op_src->type == OP_TYPE_REG,"mod!=3");
	
	if(op_src2->reg==0)
		reg_l(op_src->reg)=cpu.cr0.val;
	else if(op_src2->reg==3)
		reg_l(op_src->reg)=cpu.cr3.val;
	else
		panic("no this CR");
		
	print_asm(str(instr) " %%cr%d,%s",op_src2->reg,op_src->str);
	return len+1;
}
#endif

#include "cpu/exec/template-end.h"
