#include <setjmp.h>
#include <common.h>

extern jmp_buf jbuf;

void raise_intr(uint8_t NO){

	//NO is the index of IDT

	longjmp(jbuf,1);
}
