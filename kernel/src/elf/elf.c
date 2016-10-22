#include "common.h"
#include "memory.h"

#include <string.h>
#include <elf.h>

#define ELF_OFFSET_IN_DISK 0

#ifdef HAS_DEVICE
void ide_read(uint8_t *, uint32_t, uint32_t);
#else
void ramdisk_read(uint8_t *, uint32_t, uint32_t);
//void ramdisk_write(uint8_t *, uint32_t, uint32_t);

#endif

#define STACK_SIZE (1 << 20)

void create_video_mapping();
uint32_t get_ucr3();

uint32_t loader() {
	Elf32_Ehdr *elf;
	Elf32_Phdr *ph = NULL;

	uint8_t buf[4096];

#ifdef HAS_DEVICE
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
#else
	ramdisk_read(buf, ELF_OFFSET_IN_DISK, 4096);
#endif

	elf = (void*)buf;

	/* TODO: fix the magic number with the correct one */
	const uint32_t elf_magic = 0x464c457f;
	uint32_t *p_magic = (void *)buf;
	nemu_assert(*p_magic == elf_magic);

	//elf->e_phoff;
	//elf->e_phentsize;
	//elf->e_phnum;
/*	nemu_assert(elf->e_phoff==52);
	nemu_assert(elf->e_phentsize==32);
	nemu_assert(elf->e_phnum==3);	
*/	
	/* Load each program segment */
	//panic("please implement me");

	ph = (void *) &buf[elf->e_phoff];

/*	nemu_assert(ph->p_offset==0);
	nemu_assert(ph->p_vaddr==0x800000);
	nemu_assert(ph->p_filesz==0x27a8);
*/
//	nemu_assert(0);
//	memset((void *)0x800000,0,elf->e_phentsize*elf->e_phnum);

	int i;
	for(i=0;i<elf->e_phnum ;i++ ) {
		/* Scan the program header table, load each segment into memory */
		if(ph->p_type == PT_LOAD) {
			uint32_t hwaddr	= mm_malloc(ph->p_vaddr ,ph->p_memsz);
//			mm_malloc(ph->p_vaddr ,ph->p_memsz);
			Log("%x,%x",hwaddr,ph->p_vaddr);
			/* TODO: read the content of the segment from the ELF file 
			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
			 */
//			ramdisk_write(&buf[ph->p_offset],ph->p_vaddr,ph->p_filesz);
//			memcpy((void *)(ph->p_vaddr),&buf[ph->p_offset],ph->p_filesz);
			memcpy((void *)ph->p_vaddr,(void *)(ELF_OFFSET_IN_DISK+ph->p_offset),ph->p_filesz);
//			memcpy((void *)hwaddr,(void *)(ELF_OFFSET_IN_DISK+ph->p_offset),ph->p_filesz);
//			ATTENTION:BUGS HERE!!!!!	bugs here!!!after the implementation of the device
//			nemu_assert(0);
			/* TODO: zero the memory region 
			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
			 */
			memset((void *)ph->p_vaddr+ph->p_filesz,0,ph->p_memsz-ph->p_filesz);
//			memset((void *)hwaddr+ph->p_filesz,0,ph->p_memsz-ph->p_filesz);


#ifdef IA32_PAGE
			/* Record the program break for future use. */
			extern uint32_t cur_brk, max_brk;
			uint32_t new_brk = ph->p_vaddr + ph->p_memsz - 1;
			if(cur_brk < new_brk) { max_brk = cur_brk = new_brk; }
#endif
		}
		ph=(void *)((uint8_t*)ph + elf->e_phentsize);
		//ph++;
//		nemu_assert(0);
	}
//	nemu_assert(0);
	volatile uint32_t entry = elf->e_entry;

#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);

#ifdef HAS_DEVICE
	create_video_mapping();
#endif

	write_cr3(get_ucr3());
#endif

	return entry;
}
