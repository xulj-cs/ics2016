#include "common.h"
#include "memory.h"
#include <string.h>
#include "x86.h"
#define VMEM_ADDR 0xa0000
#define SCR_SIZE (320 * 200)

/* Use the function to get the start address of user page directory. */
PDE* get_updir();

static PTE kptable[16] align_to_page;

void create_video_mapping() {
	/* TODO: create an identical mapping from virtual memory area 
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memory area 
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */
	// 0xa0000 == 0|160|0
	// a0,000-af,a00
	PDE *pdir = get_updir();
	PTE *ptable = (PTE*)va_to_pa(kptable);
	pdir[0].val=make_pde(ptable);
	

	int idx;
	for(idx=0xa0;idx<=0xaf;idx+=0x1){
		PTE *ptable = (void *)((pdir->page_frame << 12) + idx*sizeof(PTE));
		ptable->page_frame = idx;
		ptable->present = 1;
	}


//	panic("please implement me");
}

void video_mapping_write_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		buf[i] = i;
	}
}

void video_mapping_read_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		assert(buf[i] == i);
	}
}

void video_mapping_clear() {
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
}

