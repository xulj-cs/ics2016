#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	struct watchpoint *next;
	char e[64];
	uint32_t old_result;
	/* TODO: Add more members if necessary */


} WP;
int new_wp(char *e,uint32_t result);
bool free_wp(int no);
#endif
