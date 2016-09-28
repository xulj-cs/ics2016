#include "cpu/exec/template-start.h"

#define instr call

#if DATA_BYTE == 2 || DATA_BYTE == 4
static void do_execute(){
	reg_l(R_ESP) -= DATA_BYTE;
	MEM_W(reg_l(R_ESP),cpu.eip + 1 + DATA_BYTE);
	
	if(DATA_BYTE == 2)
		cpu.eip=(cpu.eip+op_src->val) & 0x0000ffff;
	else 
		cpu.eip += op_src->val;


//	print_asm_template1();
//	print_asm(str(instr) " %s",cpu.eip + 1 + DATA_BYTE)

	printf("%s\t%x\n",str(cpu.eip),cpu.eip+1+DATA_BYTE);

}
//#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(i)
#endif

#include "cpu/exec/template-end.h"
