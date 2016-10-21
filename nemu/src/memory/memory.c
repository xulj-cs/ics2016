#include "common.h"

#define HAS_CACHE
uint32_t dram_read(hwaddr_t, size_t);
uint32_t cache_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);
void cache_write(hwaddr_t, size_t, uint32_t);
/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {

#ifdef HAS_CACHE
//	if(addr==0x801200)
//		Log("%x",dram_read(addr,4));
/*	uint32_t t1=dram_read(addr,len) & (~0u >> ((4 - len) << 3));
	uint32_t t2=cache_read(addr,len) & (~0u >> ((4 - len) << 3));
	if(t1!=t2){
		Log("addr:%x,len:%x",addr,len);
		Log("%x,%x",t1,t2);
	}
*/
	Log("%x",cache_read(addr,len) & (~0u >> ((4 - len) << 3)));
	return cache_read(addr, len) & (~0u >> ((4 - len) << 3));
#else
//	if(addr==0x801200)
//		Log("%x",dram_read(addr,4));
	return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
#endif
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {

#ifdef HAS_CACHE
	
//	if(addr==0x801200)
//		Log("%x,%x",dram_read(addr,4),data);

//	Log("%x",cache_read(addr,4));
//	Log("%x,%x",dram_read(addr,4),data);
	
//	Log("dram:%x,cache:%x",dram_read(addr,len),cache_read(addr,len));
//	Log("data:%x,%x",len,data);
	cache_write(addr, len, data);
//	Log("dram:%x,cache:%x",dram_read(addr,len),cache_read(addr,len));
#else
//	if(addr==0x801200)
//		Log("%x,%x",dram_read(addr,4),data);
//	Log("%x,%x",dram_read(addr,4),data);
	dram_write(addr, len, data);
#endif
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	hwaddr_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	return lnaddr_read(addr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_write(addr, len, data);
}

