#ifndef __IRQ_H__
#define __IRQ_H__

#include "common.h"

/* TODO: The decleration order of the members in the `TrapFrame'
 * structure below is wrong. Please re-orgainize it for the C
 * code to use the trap frame correctly.
 */

typedef struct TrapFrame {
//	uint32_t esi, ebx, eax, eip, edx, error_code, eflags, ecx, cs, old_esp, edi, ebp;
//	int32_t irq;
/*	uint32_t eflags;
	uint32_t cs;
	uint32_t eip;
	uint32_t error_code;
	int32_t irq;
	uint32_t eax,ecx,edx,ebx,old_esp,ebp,esi,edi;
*/
	uint32_t edi,esi,ebp,old_esp,ebx,edx,ecx,eax;
	int32_t irq;
	uint32_t error_code;
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
} TrapFrame;

#endif
