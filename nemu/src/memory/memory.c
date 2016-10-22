#include "common.h"
#include "cpu/reg.h"
#include "debug.h"

#define HAS_CACHE
uint32_t dram_read(hwaddr_t, size_t);
uint32_t cache_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);
void cache_write(hwaddr_t, size_t, uint32_t);

lnaddr_t seg_translate(swaddr_t addr,size_t len ,uint8_t sreg){

    SegDesc temp;
	uint8_t	RPL; 
    switch (sreg){
        case 0x2E:temp = cpu.CS.descriptor;RPL=cpu.CS.selector.RPL; break;
        case 0x36:temp = cpu.SS.descriptor;RPL=cpu.SS.selector.RPL; break;
        case 0x3E:temp = cpu.DS.descriptor;RPL=cpu.DS.selector.RPL; break;
        case 0x26:temp = cpu.ES.descriptor;RPL=cpu.ES.selector.RPL; break;
	    default:panic("no this seg_regs");
	}

/*	int max_index = cpu.GDTR.Limit / sizeof(SegDesc) - 1;
	if(index > max_index)
		panic("Index out of range");
	
	SegDesc *gdt_addr =(void *) cpu.GDTR.Base;
*/
	
	if(temp.privilege_level<cpu.CS.selector.RPL || temp.privilege_level<RPL)
		panic("Permission denied");
    
	Assert(temp.present==1,"not in the memory");
 
 	uint32_t limit=temp.limit_15_0+(temp.limit_19_16<<16);
	if(temp.granularity)
		limit *= 4*1024;

 	if(limit<addr+len)
		panic("Address out of range");
 
 	uint32_t base = temp.base_15_0+(temp.base_23_16<<16)+(temp.base_31_24<<24);
    uint32_t offset = addr;
    return base+offset;
								
								
}

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
//	Log("%x",addr);
//	Log("%x",cache_read(addr,len) & (~0u >> ((4 - len) << 3)));
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

uint32_t swaddr_read(swaddr_t addr, size_t len , uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	if(cpu.cr0.protect_enable==0 )
		return lnaddr_read(addr,len);
	
	lnaddr_t lnaddr = seg_translate(addr,len,sreg);	
	return lnaddr_read(lnaddr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data, uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	if(cpu.cr0.protect_enable==0 )
		 lnaddr_write(addr,len,data);
	else{
	
		lnaddr_t lnaddr = seg_translate(addr,len,sreg);	
		lnaddr_write(lnaddr, len, data);
	}
}

