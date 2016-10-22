#include "cpu/reg.h"
#include "cpu/helper.h"

void push_eflags(){
	int i;
	for(i=0;i<8;i++){
		cpu.esp -=4;
		swaddr_write(cpu.esp, reg_l(i), 4 , SS);
	}
}

void pop_eflags(){
	int i;
	for(i=0;i<8;i++){
		reg_l(i)=swaddr_read( cpu.esp , 4, SS);
		cpu.esp +=4;
	}
}
