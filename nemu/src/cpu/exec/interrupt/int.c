#include "cpu/exec/helper.h"
#include "cpu/decode/decode.h"

void raise_intr(uint8_t NO);

#define instr _int

make_helper(_int){

	int len = decode_i_b( eip+1 );
	
	cpu.eip += len + 1;
	print_asm_template1();
	raise_intr((uint8_t)op_src->val);

	print_asm_template1();
	Log("reach here");
	//a bug here
	return 0;
}


