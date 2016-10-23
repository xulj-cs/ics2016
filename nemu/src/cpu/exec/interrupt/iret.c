#include "cpu/exec/helper.h"
#include "cpu/reg.h"
#include "memory/memory.h"


make_helper(iret){

	cpu.eip = swaddr_read(cpu.esp,4,SS);
	Log("%x",cpu.eip);
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

	//pop_eflags
	cpu.CF=swaddr_read(cpu.esp,1,SS);
	cpu.esp+=1;
	cpu.PF=swaddr_read(cpu.esp,1,SS);
	cpu.esp+=1;
	cpu.ZF=swaddr_read(cpu.esp,1,SS);
	cpu.esp+=1;
	cpu.SF=swaddr_read(cpu.esp,1,SS);
	cpu.esp+=1;
	cpu.IF=swaddr_read(cpu.esp,1,SS);
	cpu.esp+=1;
	cpu.DF=swaddr_read(cpu.esp,1,SS);
	cpu.esp+=1;
	cpu.OF=swaddr_read(cpu.esp,1,SS);
	cpu.esp+=1;
	
	print_asm(str(iret));
	return 1;
	
}

