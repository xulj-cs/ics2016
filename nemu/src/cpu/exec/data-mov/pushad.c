#include "cpu/exec/helper.h"
void push_eflags();

make_helper(pushad){
	push_eflags();
	print_asm(str(pushad));

	return 1;
}
