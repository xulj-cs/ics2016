#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"
make_helper(mov_r2sreg){

	int len=decode_rm_l(eip+1);
	Assert(op_src->type == OP_TYPE_REG,"mod!=3");
	
	Assert(0<=op_src2->reg && op_src2->reg<=3,"no this sreg");

	cpu.sreg[op_src2->reg].selector.val=op_src->val;
	
	Assert(cpu.sreg[op_src2->reg].selector.TI==0,"no LGTR");
		
	lnaddr_t base=cpu.GDTR.Base;
	int max_index = ( cpu.GDTR.Limit+1 ) / sizeof(SegDesc) -1;
    int index = cpu.sreg[op_src2->reg].selector.INDEX;
    if(index > max_index)
        panic("Index out of range");
						
    uint8_t temp[8];
    int j;
    for(j=0;j<8;j++){
        temp[j]=lnaddr_read(base+index*8+j , 1);
    }
									
    memcpy(&cpu.sreg[op_src2->reg].descriptor,temp,8);

	print_asm(str(mov) " %%%s,%%%s",regsl[op_src->reg],sreg[op_src2->reg]);
	return len+1;
}
