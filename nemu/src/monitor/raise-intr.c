#include <setjmp.h>
#include "common.h"
#include "cpu/reg.h"
#include "memory/memory.h"

extern jmp_buf jbuf;

void push_eflags();

void raise_intr(uint8_t NO){

	push_eflags();

	cpu.IF=0;
	
	cpu.esp -=2;
	swaddr_write(cpu.esp,cpu.CS.selector.val,2,SS);

	cpu.esp -=4;
	swaddr_write(cpu.esp,cpu.eip,4,SS);

	lnaddr_t base=cpu.IDTR.Base;
	int max_index = (cpu.IDTR.Limit+1) / sizeof(GateDesc) -1;
	Assert(NO <= max_index,"Index out of range");
	
	uint8_t temp[sizeof(GateDesc)];
    int i;
	for(i=0;i<sizeof(GateDesc);i++){
	
		temp[i] = lnaddr_read(base + NO*4*sizeof(GateDesc)+i , 1);
	}
	GateDesc gatedesc ;

	memcpy(&gatedesc , temp , sizeof(GateDesc));

	cpu.CS.selector.val = gatedesc.segment;
	//load the Sreg Desc-cache
	{
		int max_index = (cpu.GDTR.Limit + 1) /sizeof(SegDesc) -1;
		int index = cpu.CS.selector.INDEX;
		Assert(index <= max_index,"Index out of range");

		uint8_t temp[sizeof(SegDesc)];
		int j;
		for(j=0;j<sizeof(SegDesc);j++){
			temp[j] = lnaddr_read( cpu.GDTR.Base + index*sizeof(SegDesc)+j,1 );
		}
		memcpy(&cpu.CS.descriptor,temp,sizeof(SegDesc));
	}
	cpu.eip = ( gatedesc.offset_31_16 << 16 ) + gatedesc.offset_15_0;	

	longjmp(jbuf,1);
}
