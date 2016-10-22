#include "cpu/exec/helper.h"

make_helper(ljmp){

	uint32_t temp1=swaddr_read(eip+1,4,CS);
	uint16_t temp2=swaddr_read(eip+1+4,2,CS);
	Log("here1");
	cpu.CS.selector.val=temp2;

	Assert(cpu.CS.selector.TI==0,"no LGTR");

	int max_index = cpu.GDTR.Limit / sizeof(SegDesc) -1;
	if(cpu.CS.selector.INDEX > max_index)
		panic("Index out of range");

	SegDesc *gdt_addr = (void *)cpu.GDTR.Base;
	Log("%x",cpu.GDTR.Base);
	cpu.CS.descriptor=gdt_addr[cpu.CS.selector.INDEX];
	Log("here2");
	cpu.eip=temp1;

	print_asm(str(ljmp) "%x,%x",temp2,temp1);
	Log("here3");
	return 0;
}
