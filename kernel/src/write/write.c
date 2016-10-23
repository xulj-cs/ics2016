#include "common.h"

int write(int fd,const void *buf,size_t len){

	if( (fd==1||fd==2)&&len!=0 ){
		asm volatile (".byte 0xd6"::"a"(2),"c"(buf),"d"(len));
		return len;
	}
	else
		return -1;


}

