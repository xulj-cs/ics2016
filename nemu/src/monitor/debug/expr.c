#include "nemu.h"
#include "cpu/reg.h"
#include <stdlib.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ, NUM_DEC, NUM_HEX, REG, N_EQ, AND ,OR , NOT ,NEG, DEREF

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */
	
	{" +",	NOTYPE},				// spaces
	{"\\(",'('},					//left parenthesis 
	{"\\)",')'},					//right parathesis
	{"\\*",'*'},				//multiply
	{"/",'/'},					//divide
	{"\\+", '+'},				//plus
	{"-",'-'},					// minus
	{"0x[0-9]+]",NUM_HEX}, //hex number
	{"[0-9]+",NUM_DEC},	//dec number
	{"\\$e[a-d]x",REG},    //eax ebx ecx edx
	{"\\$[a-d][xlh]",REG},  //
	{"\\$(e)?[sd]i",REG},	//edi esi
	{"\\$(e)?[bsi]p",REG},	//ebp esp eip
	{"!=",N_EQ},          //unequal
	{"==", EQ},				//equal
	{"&&",AND},				//and
	{"\\|\\|",OR},				//or
	{"!",NOT},				//not	

};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;
bool is_operator(int type);

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array `tokens'. For certain types
				 * of tokens, some extra actions should be performed.
				 */
				
			/*	switch(rules[i].token_type) {
					case '(':tokens[nr_token].type='(';break;
					case ')':tokens[nr_token].type=')';break;
					case '*':tokens[nr_token].type='*';break;
					case '/':tokens[nr_token].type='/';break;
					case '+':tokens[nr_token].type='+';break;
					case '-':tokens[nr_token].type='-';break;
					case  EQ:tokens[nr_token].type=EQ; break;
					case N_EQ:tokens[nr_token].
					case  NUM_DEC:tokens[nr_token].type=NUM_DEC;
					if(substr_len>=32)
						assert(0);
					strncpy(tokens[nr_token].str,(const char *)substr_start,substr_len);
					tokens[nr_token].str[substr_len]='\0';
					break;
					default: panic("please implement me");
				}
			*/

				if(rules[i].token_type!=NOTYPE)
				{	
					tokens[nr_token].type=rules[i].token_type;
					if(!is_operator(rules[i].token_type))
					{	if(substr_len>=32)
							assert(0);
						strncpy(tokens[nr_token].str,(const char *)substr_start,substr_len);
						tokens[nr_token].str[substr_len]='\0';	
					}
					nr_token++;
				}
				
				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}
bool is_parenthese_matched(int p,int q)
{
	int st_top=-1;
	int i;
	for(i=p;i<=q;i++)
	{
		if(tokens[i].type=='(')
			st_top++;
		if(tokens[i].type==')')
			st_top--;

		if(st_top==-2)
			return false;
	}
	if(st_top!=-1)
		return false;
	return true;
}

bool check_parenthese(int p,int q)
{
	if(tokens[p].type!='('||tokens[q].type!=')')
		return false;
	return is_parenthese_matched(p+1,q-1);
}

bool is_operator(int type)
{
	if(type==NUM_DEC||type==NUM_HEX||type==REG)
		return false;
	return true;
}


int prece_level(int type)
{
	if(type==OR)
		return 1;
	if(type==AND)
		return 2;
	if(type==EQ||type==N_EQ)
		return 3;
	if(type=='+'||type=='-')
		return 4;
	if(type=='*'||type=='/')
		return 5;
	if(type==NOT)
		return 6;
	panic("error");
	return 0;
}
bool is_in_parenthese(int p,int q)
{
/*	if(p==q-1)
		return false;
		*/
	return !is_parenthese_matched(p,q-1);
}
int dominant_operator(int p,int q)
{
	int i;
	int min_prece_level=6;
	int index=p;
	for(i=p+1;i<=q-1;i++)
	{
		if(!is_operator(tokens[i].type))
			continue;
		if(is_in_parenthese(p,i))
			continue;

		if(min_prece_level>=prece_level(tokens[i].type))
		{
			min_prece_level=prece_level(tokens[i].type);
			index=i;
		}

	}
	return index;
}
unsigned eval(int p,int q,bool *success)
{	if(p > q)
	{
		*success=false;
		return -1;
	}
	else if(p==q)
	{
		if(is_operator(tokens[p].type))
		{
			*success=false;
			return -1;
		}
		unsigned result;
		int i;
		switch(tokens[p].type)
		{
			case NUM_DEC:sscanf(tokens[p].str,"%u",&result);return result;
			case NUM_HEX:sscanf(tokens[p].str,"%x",&result);return result;
			case REG:
				
				for(i=0;i<=7;i++)
				{
					if(strcmp((const char *)&tokens[p].str[1],regsl[i])==0)
						return reg_l(i);
				}

				for(i=0;i<=7;i++)
				{
					if(strcmp((const char *)&tokens[p].str[i],regsw[i])==0)
						return reg_w(i);
				}
				for(i=0;i<=7;i++)
				{
					if(strcmp((const char *)&tokens[p].str[i],regsb[i])==0)
						return reg_b(i);
				}
				panic("error");
				default:panic("error");
		 }
	}

	else if(check_parenthese(p,q)==true)	
	{
		return eval(p+1,q-1,success);
	}
	else
	{
		if(!is_parenthese_matched(p,q))
		{
			*success=false;
			return -1;	
		}
		int op=dominant_operator(p,q);
		if(op==p)
		{
			*success=false;
			return -1;
		}
		unsigned value1=eval(p,op-1,success);
		unsigned value2=eval(op+1,q,success);
		switch(tokens[op].type)
		{
			case '+':return value1+value2; break;
			case '-':return value1-value2; break;
			case '*':return value1*value2; break;
			case '/':
			if(value2==0)
			{	*success=false;
				printf("division by zero\n");
				return -1;
			}
			return value1/value2; break;
			default: assert(0); 
		}
	}
}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
	int i;
	for(i=0;i<nr_token;i++)
	{	
		if(tokens[i].type=='*'&&(i==0||(is_operator(tokens[i-1].type)&&tokens[i-1].type!=')')))
			tokens[i].type=DEREF;
	}

	for(i=0;i<nr_token;i++)
	{	
		if(tokens[i].type=='-'&&(i==0||(is_operator(tokens[i-1].type)&&tokens[i-1].type!=')')))
			tokens[i].type=NEG;
	}
	unsigned result=eval(0,nr_token-1,success);
	if(*success == false)
	{
		printf("the expression is illegal\n");
		return 0;
	}
	return result;


	/* TODO: Insert codes to evaluate the expression. */
	panic("please implement me");
	return 0;
}

