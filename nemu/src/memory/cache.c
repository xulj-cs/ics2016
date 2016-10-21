#include "common.h"
#include "macro.h"


uint32_t dram_read(hwaddr_t , size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

/*the impletation of Cache_L1*/
#define TYPE L1
#define Size_of_Cache_Block (64)
#define Size_of_Cache (64*1024)
#define Num_of_Way (8)
#define Write_Through
#define Not_Write_Allocate

#include "cache-template.h"

#undef TYPE
#undef Size_of_Cache_Block
#undef Size_of_Cache
#undef Num_of_Way
#undef Write_Through
#undef Not_Write_Allocate


uint32_t cache_read(hwaddr_t addr, size_t len){
	
	return cache_read_L1(addr, len);
}
