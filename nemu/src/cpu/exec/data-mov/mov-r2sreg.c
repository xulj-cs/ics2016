#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"
make_helper(mov_r2sreg){

	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	Assert(m.mod==3,"mod!=3");
	
	Assert(0<=m.reg&&m.reg<=3,"no this sreg");

	cpu.sreg[m.reg].selector.val=reg_l(m.R_M);
	
	Assert(cpu.sreg[m.reg].selector.TI==0,"no LGTR");
		
	lnaddr_t base=cpu.GDTR.Base;
	int max_index = ( cpu.GDTR.Limit+1 ) / sizeof(SegDesc) -1;
    int index = cpu.sreg[m.reg].selector.INDEX;
    if(index > max_index)
        panic("Index out of range");
						
    uint8_t temp[8];
    int j;
    for(j=0;j<8;j++){
        temp[j]=lnaddr_read(base+index*8+j , 1);
    }
									
    memcpy(&cpu.sreg[m.reg].descriptor,temp,8);

	print_asm(str(mov) " %%%s,%%%s",regsl[m.R_M],sreg[m.reg]);
	return 2;
}
