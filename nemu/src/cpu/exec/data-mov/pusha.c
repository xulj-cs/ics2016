#include "cpu/exec/helper.h"

make_helper(pusha){
	
    int i;
    for(i=0;i<8;i++){
        cpu.esp -=4;
        swaddr_write(cpu.esp, 4, reg_l(i),  SS);
    }

	print_asm(str(pusha));

	return 1;
}
