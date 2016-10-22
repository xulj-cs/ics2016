#include "common.h"
#include <time.h>
#include <stdlib.h>
#include "x86-inc/mmu.h"
#include "cpu/reg.h"

#define Num_of_PTE 64

uint32_t hwaddr_read(hwaddr_t , size_t);

typedef struct{
	PTE pte;
	bool valid;
	int tag;
}TLB;

TLB tlb[Num_of_PTE];

void init_tlb(){
	int i;
	for(i = 0; i<Num_of_PTE;i++)
		tlb[i].valid = false;
}

bool FindWay(int tag, int *way){

	int i;
	for(i=0;i<Num_of_PTE;i++){
	
		if(!tlb[i].valid)
			continue;
		
		if(tlb[i].tag == tag)
			break;
	}
	*way = i;
	if(i == Num_of_PTE)
		return false;
	else
		return true;
}

int load_pte(uint32_t addr){

	int i;
	for(i=0;i<Num_of_PTE;i++){
		if(!tlb[i].valid)
			break;
	}
	if( i == Num_of_PTE){
	
		srand((uint32_t)time(NULL));

		i = rand() % Num_of_PTE ;
		tlb[i].valid = false;
		
	}
	
	tlb[i].valid = true;
	tlb[i].tag = addr >> 12;
  
    int pdir_idx,ptab_idx;
    pdir_idx = addr >> 22;
    ptab_idx = addr << 10 >> 22;


    hwaddr_t pdir_base = cpu.cr3.page_directory_base << 12;
    PDE temp1;

    temp1.val = hwaddr_read(pdir_base + pdir_idx*4, 4);
    Assert(temp1.present==1,"not in the memory");

    hwaddr_t ptab_base = temp1.page_frame << 12;
    PTE temp2 ;
    temp2.val = hwaddr_read(ptab_base + ptab_idx*4, 4);
    Assert(temp2.present==1,"not in the memory");

	tlb[i].pte=temp2;

	return i;
}
PTE read_tlb(lnaddr_t addr){

	int tag = addr >> 12;
	int way;

	if(!FindWay(tag,&way)){
		way = load_pte(addr);
	}
	return tlb[way].pte;
}

