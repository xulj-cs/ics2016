#include "cpu/exec/helper.h"

make_helper(popa){

    int i;
    for(i=0;i<8;i++){
        if(i!=R_ESP)
			reg_l(i)=swaddr_read( cpu.esp , 4, SS);
        cpu.esp +=4;
    }


	print_asm(str(popa));

	return 1;
}
