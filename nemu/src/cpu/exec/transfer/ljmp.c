#include "cpu/exec/helper.h"

make_helper(ljmp){

	uint32_t temp1=swaddr_read(eip+1,4,CS);
	uint16_t temp2=swaddr_read(eip+1+4,2,CS);

	cpu.CS.selector.val=temp2;

	Assert(cpu.CS.selector.TI==0,"no LGTR");

	uint32_t base=cpu.GDTR.Base;
	int max_index = ( cpu.GDTR.Limit+1 ) / sizeof(SegDesc) -1;
	int index = cpu.CS.selector.INDEX;
	if(index > max_index)
		panic("Index out of range");

	Log("%d",index);
	uint8_t temp[8];
	int j;
	for(j=0;j<8;j++){
		temp[j]=swaddr_read(base+index*8+j , 1 , CS);
	}

	memcpy(&cpu.CS.descriptor,temp,8);
	cpu.eip=temp1;

	print_asm(str(ljmp) "%x,%x",temp2,temp1);
	Log("here3");
	return 0;
}
