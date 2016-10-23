#include "cpu/exec/helper.h"

make_helper(popa){

    int i;
    for(i=7;i>=0;i--){
        if(i!=R_ESP && i!=R_EAX)
			reg_l(i)=swaddr_read( cpu.esp , 4, SS);
        cpu.esp +=4;
    }


	print_asm(str(popa));

	return 1;
}
