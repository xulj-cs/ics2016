#include "common.h"
#include "macro.h"

#include <stdlib.h>
#include <time.h>
uint32_t dram_read(hwaddr_t , size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

/*the impletation of Cache_L2*/
#define TYPE L2
#define l2
#define Size_of_Cache_Block (64)
#define Size_of_Cache (4*1024*1024)
#define Num_of_Way (16)
#define Write_Back
#define Write_Allocate

#include "cache-template.h"

#undef TYPE
#undef l2
#undef Size_of_Cache_Block
#undef Size_of_Cache
#undef Num_of_Way
#undef Write_Back
#undef Write_Allocate

/*the impletation of Cache_L1*/
#define TYPE L1
#define l1
#define Size_of_Cache_Block (64)
#define Size_of_Cache (64*1024)
#define Num_of_Way (8)
#define Write_Through
#define Not_Write_Allocate

#include "cache-template.h"

#undef TYPE
#undef l1
#undef Size_of_Cache_Block
#undef Size_of_Cache
#undef Num_of_Way
#undef Write_Through
#undef Not_Write_Allocate



uint32_t cache_read(hwaddr_t addr, size_t len){
	
	return cache_read_L1(addr, len);
}
void cache_write(hwaddr_t addr, size_t len, uint32_t data){
	
	cache_write_L1(addr, len, data);
}

void ui_cache_read(char *args){
	
	ui_cache_read_L1(args);

}
void init_cache(){
	init_cache_L1();
	init_cache_L2();
}
