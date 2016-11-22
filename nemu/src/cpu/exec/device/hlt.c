#include "cpu/exec/helper.h"
#include "cpu/reg.h"

make_helper(hlt){

	while(1){
		if(cpu.IF && cpu.INTR)
			break;
	}
	print_asm(str(hlt));
	return 1;
}
