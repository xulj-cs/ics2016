#include "cpu/exec/template-start.h"

int concat(CF_,SUFFIX)(DATA_TYPE x,DATA_TYPE y,char op)
{
	if(op == '+')
	{
		DATA_TYPE result = x+y;
		if(result<x)
			return 1;
		else
			return 0;
	}
	else
	{
		DATA_TYPE result = x-y;
		if(result>x)
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
		result = x+y;
	else
		result = x-y;
	
	if( MSB(x)==MSB(y) && MSB(x)!=MSB(result) )
		return 1;
	else
		return 0;

}

#include "cpu/exec/template-end.h"
