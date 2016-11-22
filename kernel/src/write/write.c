#include "common.h"
void serial_printc(char);
int write(int fd,const void *buf,size_t len){

	if( (fd==1||fd==2)&&len!=0 ){
//		asm volatile (".byte 0xd6"::"a"(2),"c"(buf),"d"(len));
		int i;
		for(i=0; i<len; i++)
			serial_printc((char)*((uint8_t*)buf+i));
		return len;
	}
	else
		return -1;


}

