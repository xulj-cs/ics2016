#include "cpu/exec/helper.h"
void pop_eflags();

make_helper(popad){
	pop_eflags();
	print_asm(str(popad));

	return 1;
}
