#include "cpu/exec/helper.h"
#include "cpu/reg.h"
#include "memory/memory.h"

void pop_eflags();

make_helper(iret){

	cpu.eip = swaddr_read(cpu.esp,4,SS);
	cpu.esp +=4;

	cpu.CS.selector.val=swaddr_read(cpu.esp,2,SS);
	cpu.esp +=2;
	
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

	pop_eflags();

	print_asm(str(iret));
	return 1;
	
}

