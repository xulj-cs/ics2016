/*
    Name_of_Cache
	Size_of_Cache_Block
	Size_of_Cache
	Num_of_Block
	Num_of_Set
	Num_of_Way

	valid bit 
	dirty bit

	write through/write back
	not write allocate/write allocate

*/
#define Cache concat(Cache_,TYPE)
#define Cache_Block concat(Cache_Block_,TYPE)

#define FindWay concat(Find_Way_,TYPE)
#define block_read concat(block_read_,TYPE)
#define load_block concat(load_block_,TYPE)
#define cache_read concat(cache_read_,TYPE)
#define init_cache concat(init_cache_,TYPE)

#define Num_of_Block (Size_of_Cache/Size_of_Cache_Block)
#define Num_of_Set (Num_of_Block/Num_of_Way)
#define Size_of_Set (Size_of_Cache_Block * Num_of_Way)

typedef struct{
	uint8_t block[Size_of_Cache_Block];
	int tag;
	bool valid;
#ifdef Write_Back
	bool dirty;
#endif
}Cache_Block;

//Cache_Block Cache_Set[Num_of_Way]; 
Cache_Block Cache[Num_of_Set][Num_of_Way];

bool FindWay(int set, int tag, int *way){

	int i;
	for(i=0;i<Num_of_Way;i++){
		if( !Cache[set][i].valid )
			continue;
		if( Cache[set][i].tag == tag)
			break;
	}
	if( i == Num_of_Way)
		return false;
	else{
	
		*way=i;
		return true;
	}


}
int load_block(hwaddr_t addr, int set){
	
	int i;
	for(i=0;i<Num_of_Way;i++){
		if( !Cache[set][i].valid )
			break;	
	}
	if( i == Num_of_Way ){
		
	//	Replace
		i = 0;	//how to random??
		Cache[set][i].valid=false;
#ifdef Write_Back
		if(Cache[set][i].dirty)
			dram_write()
		Cache[set][i].dirty=false;
#endif

	
	}
	Cache[set][i].valid=true;
	Cache[set][i].tag=(addr/Size_of_Set)/Size_of_Cache_Block;
		
	//	memcpy(Cache[set][i].block, addr, Size_of_Cache_Block);
	uint32_t start= ( addr/Size_of_Cache_Block )*Size_of_Cache_Block;
//	uint32_t end= (addr/Size_of_Cache_Block + 1)*Size_of_Cache_Block;
	int j;
	for(j=0;j<Size_of_Cache_Block;j++,start++){
		
//		memcpy( &(Cache[set][i].block+j) , dram_read(addr,len))
		Cache[set][i].block[j] = dram_read(start, 1) & 0xff;
	}
	return i;
}
void block_read(hwaddr_t addr,void *data){

	
	int set=(addr/Size_of_Set) % Num_of_Set;
	int tag=(addr%Size_of_Set)/Size_of_Cache_Block;
	int way;
	if(!FindWay(set, tag, &way))
	{
		//dram -->> cache;
		way = load_block(addr,set);
		Log("notFind");
	}

	memcpy(data, Cache[set][way].block , Size_of_Cache_Block);
	
}
uint32_t cache_read(hwaddr_t addr, size_t len){
	
	uint32_t offset=addr & (Size_of_Cache_Block - 1);
	uint8_t temp[2*Size_of_Cache_Block];

	block_read(addr, temp);

	if(offset + len > Size_of_Cache_Block){
	
		block_read(addr+Size_of_Cache_Block , temp+Size_of_Cache_Block);
		Log("unalign");
	
	}

	return unalign_rw(temp+offset, 4);
}

void init_cache(){
	
	int i,j;
	for(i=0;i<Num_of_Set;i++)
		for(j=0;j<Num_of_Way;j++)
			Cache[i][j].valid=false;
}
#undef Cache
#undef Cache_Block

#undef FindWay
#undef block_read
#undef load_block
#undef cache_read
#undef init_cache

#undef Num_of_Block
#undef Num_of_Set
#undef Size_of_Set