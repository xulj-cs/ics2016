#ifndef __EXPR_H__
#define __EXPR_H__

#include "common.h"
enum {
	NOTYPE = 256,EQ,NUM_DEC,NUM_HEX	,REG,N_EQ,AND,OR,NOT,NEG,DEREF
};
uint32_t expr(char *, bool *);
typedef struct token{
	int type;
	char str[32];
} Token;
extern Token tokens[32];
extern int nr_token;
#endif
