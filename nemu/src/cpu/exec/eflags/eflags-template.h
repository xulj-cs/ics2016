#include "cpu/exec/template-start.h"

int concat(CF_,SUFFIX)(DATA_TYPE x,DATA_TYPE y,char op)
{
	if(op == '+')
	{
		DATA_TYPE result = x+y;
		if(result<x)		//result=x+y-2^n <==> result < x <==> x+y>=2^n
			return 1;
		else
			return 0;
	}
	else
	{
	//	DATA_TYPE result = x-y;
		if( x < y )			//result=x-y+2^n <==> result > x <==> x < y
			return 1;
		else
			return 0;
	}
}

int concat(PF_,SUFFIX)(DATA_TYPE n)
{
	int count=0;
	int i=8;
	while(i--)
	{
		count += n&1;
		n >>=1;
	}
	if(count%2==0)
		return 1;
	else
		return 0;		
}

int concat(OF_,SUFFIX)(DATA_TYPE_S x,DATA_TYPE_S y,char op)
{
	DATA_TYPE_S result;
	if(op == '+')
	{	
		result = x+y;
		if ( MSB(x)==MSB(y) && MSB(x)!=MSB(result) )
			return 1;
		else
			return 0;
	}
	else
	{	
		result = x-y;
		if( MSB(x)!=MSB(y) && MSB(x)!=MSB(result) )
			return 1;
		else
			return 0;
	}
}

#include "cpu/exec/template-end.h"
