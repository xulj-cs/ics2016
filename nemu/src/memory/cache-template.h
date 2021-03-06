/*
    Name_of_Cache
	Size_of_Block
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
#define block_write concat(block_write_,TYPE)
#define cache_write concat(cache_write_,TYPE)
#define ui_cache_read concat(ui_cache_read_,TYPE)

#define Num_of_Block (Size_of_Cache/Size_of_Block)
#define Num_of_Set (Num_of_Block/Num_of_Way)
#define Size_of_Set (Size_of_Block * Num_of_Way)

typedef struct{
	uint8_t block[Size_of_Block];
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
		//if( !Cache[set][i].valid )
		//	continue;
/*		uint32_t start= (	Cache[set][i].tag/Size_of_Block )*Size_of_Block;
		uint32_t end= (	Cache[set][i].tag/Size_of_Block + 1)*Size_of_Block;
		if( start<=tag && tag<end )	
*/
		if(Cache[set][i].valid && Cache[set][i].tag == tag )
			break;
	}
	*way=i;
	if( i == Num_of_Way){
		
		return false;
	}
	else{
	
		return true;
	}


}
int load_block(hwaddr_t addr, int set){		//dram-->>cache
	
	int i;
	for(i=0;i<Num_of_Way;i++){
		if( !Cache[set][i].valid )
			break;	
	}
	if( i == Num_of_Way ){
		
	//	Replace
	//	srand((uint32_t)time(NULL));

	//	i = rand()%Num_of_Way;	//how to random??
		i = time(NULL) & Num_of_Way;
		Cache[set][i].valid=false;
#ifdef Write_Back
		if(Cache[set][i].dirty){
			//cache -- >> dram
			
			uint32_t dram_addr = ( Cache[set][i].tag/Size_of_Block )*Size_of_Block;
			int j;
			for(j=0;j<Size_of_Block;j++,dram_addr++){
			
	//			Log("%x,%x",Cache[set][i].block[j],dram_read(dram_addr,1)&0xff);
				dram_write(dram_addr,1,Cache[set][i].block[j]);
	//			Log("%x",dram_read(dram_addr,1)&0xff);
			
			}
		}
			
		Cache[set][i].dirty=false;
#endif
	
	}
	Cache[set][i].valid=true;
	Cache[set][i].tag= (addr / Size_of_Block ) / Num_of_Set; 

	uint32_t start= ( addr/Size_of_Block )*Size_of_Block;
//	uint32_t end= (addr/Size_of_Block + 1)*Size_of_Block;
	int j;
	for(j=0;j<Size_of_Block;j++,start++){
		
		Cache[set][i].block[j] = dram_read(start, 1) & 0xff;
	
	}

	
	return i;
}
void block_read(hwaddr_t addr,void *data){

	
//	int set=(addr/Size_of_Set) % Num_of_Set;
//	uint32_t tag=addr;
	int set = (addr /Size_of_Block) % Num_of_Set;
	int tag = (addr /Size_of_Block) / Num_of_Set;
	int way;
/*	if(tag==4&&set==5){
		Log("0x%x",addr);	
	}
*/
	if(!FindWay(set, tag, &way))
	{
		//dram -->> cache;
#ifdef l1
		block_read_L2(addr,data);
		return;
#else
		way = load_block(addr,set);

#endif
	}
	memcpy(data, Cache[set][way].block , Size_of_Block);
	
}
void ui_cache_read(char *args){

	uint32_t addr;
	sscanf(args,"0x%x",&addr);
//	int set=(addr/Size_of_Set) % Num_of_Set;
//	uint32_t tag=addr;
	int set = (addr /Size_of_Block) % Num_of_Set;
	int tag = (addr /Size_of_Block) / Num_of_Set;
	int way;
	if(!FindWay(set, tag, &way))
	{
#ifdef l1
	ui_cache_read_L2(args);
	return ;
#else
	printf("No This Cache\n");
	return ;
#endif
	}
	printf("The Cache :");
	int i;
	for(i=0;i<Size_of_Block;i++){
		printf("%02x",Cache[set][way].block[i]);
	}
#ifdef Write_Back
	printf("the dirty bit is %x",Cache[set][way].dirty);	
#endif
	printf("\n");
	
}
uint32_t cache_read(hwaddr_t addr, size_t len){
	
	uint32_t offset=addr & (Size_of_Block - 1);
	uint8_t temp[2*Size_of_Block];

//	uint32_t t1,t2;
//	t1=dram_read(0x801200,4);
//	Log("%x",t1);

	block_read(addr, temp);
	
	if(offset + len > Size_of_Block){
	
		block_read(addr+Size_of_Block , temp+Size_of_Block);
	
	}
//	t2=dram_read(0x801200,4);
//	Log("%x",t2);
//	if(t1!=t2)
//		Log("error!!");	
//	Log("\n");

	return unalign_rw(temp+offset, 4);
}
void block_write(hwaddr_t addr, size_t len, uint32_t* pdata){

	uint32_t offset=addr & (Size_of_Block-1);
//	int set=(addr/Size_of_Set) % Num_of_Set;
//	uint32_t tag=addr;
	int set = (addr /Size_of_Block) % Num_of_Set;
	int tag = (addr /Size_of_Block) / Num_of_Set;
	int way;
	len=offset+len>Size_of_Block?Size_of_Block-offset:len;
	if(!FindWay(set, tag, &way))
	{
#ifdef l1
		block_write_L2(addr,len,pdata);
		return ;
#else
#ifdef Not_Write_Allocate
		return;
#else	//Write_Allocate
		way = load_block(addr,set);		
#endif

#endif
	}
/*		int i;
		for(i=0;i<len;i++){
			Log("%x",Cache[set][way].block[offset+i]);
		}

		Log("before :%x,%x",*pdata,len);
*/
/*		if(Cache[set][way].tag/64*64==0x7ffef80)
		{
			Log("%d,%d,%x,%d,%d",set,way,*pdata,len,offset);
		}
*/
		memcpy(Cache[set][way].block+offset, pdata, len);
/*		for(i=0;i<len;i++){
			Log("%x",Cache[set][way].block[offset+i]);
		}
		Log("\n\n");
*/
#ifdef Write_Back
		Cache[set][way].dirty=true;
#endif
	

}
void cache_write(hwaddr_t addr, size_t len, uint32_t data){
#ifdef Write_Through
	dram_write(addr, len, data);
#endif
	uint32_t offset=addr & (Size_of_Block -1);
	block_write(addr, len, &data);
	if(offset + len >Size_of_Block){
		int t=Size_of_Block-offset;//have write
//		len-t;
		block_write(addr+t,len-t,(void *)((uint8_t *)&data+t));
	
	}

	
}
void init_cache(){
	
	int i,j;
	for(i=0;i<Num_of_Set;i++)
		for(j=0;j<Num_of_Way;j++){
		
			Cache[i][j].valid=false;
#ifdef Write_Back
			Cache[i][j].dirty=false;
#endif
		}
}
#undef Cache
#undef Cache_Block

#undef FindWay
#undef block_read
#undef load_block
#undef cache_read
#undef init_cache
#undef block_write
#undef cache_write
#undef ui_cache_read

#undef Num_of_Block
#undef Num_of_Set
#undef Size_of_Set
