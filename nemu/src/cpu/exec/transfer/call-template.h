#include "cpu/exec/template-start.h"

#define instr call

#if DATA_BYTE == 2 || DATA_BYTE == 4
static void do_execute(){    //for imm
	reg_l(R_ESP) -= DATA_BYTE;
	MEM_W(reg_l(R_ESP),cpu.eip + 1 + DATA_BYTE);
	
	if(DATA_BYTE == 2)
		cpu.eip=(cpu.eip+op_src->val) & 0x0000ffff;
	else 
		cpu.eip += op_src->val;


//	print_asm_template1();
	print_asm(str(instr) " %x",cpu.eip + 1 + DATA_BYTE);
//	print_asm(str(instr) str(SUFFIX) " %s", op_src->str)
//	printf("%s\t%x\n",str(instr),cpu.eip+1+DATA_BYTE);

}
//#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(i)

make_helper(concat3(instr,_rm_,SUFFIX)){
	    
	int len = concat( decode_rm_,SUFFIX)(eip);
	
	reg_l(R_ESP) -= DATA_BYTE;
	MEM_W(reg_l(R_ESP),cpu.eip + 1 + len);
		
			
	cpu.eip = op_src->val;
			
	if(DATA_BYTE == 2)
		cpu.eip = cpu.eip & 0x0000ffff;
							
	print_asm(str(instr) " *%s",op_src->str);
								
	return 0;
									
									
}

#endif

#include "cpu/exec/template-end.h"
