#include "FLOAT.h"
#include <stdint.h>

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	//nemu_assert(0);
	FLOAT result=((int64_t)a*b)>>16;
	return result;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	/* Dividing two 64-bit integers needs the support of another library
	 * `libgcc', other than newlib. It is a dirty work to port `libgcc'
	 * to NEMU. In fact, it is unnecessary to perform a "64/64" division
	 * here. A "64/32" division is enough.
	 *
	 * To perform a "64/32" division, you can use the x86 instruction
	 * `div' or `idiv' by inline assembly. We provide a template for you
	 * to prevent you from uncessary details.
	 *
	 *     asm volatile ("??? %2" : "=a"(???), "=d"(???) : "r"(???), "a"(???), "d"(???));
	 *
	 * If you want to use the template above, you should fill the "???"
	 * correctly. For more information, please read the i386 manual for
	 * division instructions, and search the Internet about "inline assembly".
	 * It is OK not to use the template above, but you should figure
	 * out another way to perform the division.
	 */
	FLOAT quo ;
	uint32_t rem;
	uint32_t high=(*(int *)&a)>>16;
	uint32_t low =(*(int *)&a)<<16;
	
	asm volatile ("idiv %2" : "=a"(quo),"=d"(rem) : "r"(b),"a"(low),"d"(high)	);
	//nemu_assert(0);
	return quo;
}

FLOAT f2F(float a) {
	/* You should figure out how to convert `a' into FLOAT without
	 * introducing x87 floating point instructions. Else you can
	 * not run this code in NEMU before implementing x87 floating
	 * point instructions, which is contrary to our expectation.
	 *
	 * Hint: The bit representation of `a' is already on the
	 * stack. How do you retrieve it to another variable without
	 * performing arithmetic operations on it directly?
	 */

	//nemu_assert(0);
	int32_t int_a=*(int *)&a;
	/*asm volatile("pushl %%eax\n\t
				  movl 8(%%esp),%0\n\t
				  popl %%eax":"=a"(int_a));*/
	uint8_t e=int_a>>23;
	int32_t n=e-127;
	uint32_t result=((int_a)&0x7fffff)|(1<<23);
	//result = result<<(n-7);
	if(n>7)
		result <<=(n-7);
	else if (n<7);
		result >>=(7-n);
	if(int_a<0)
		result = -result;
	return result;
	return 0;
}

FLOAT Fabs(FLOAT a) {
	//nemu_assert(0);
	int32_t int_a=*(int *)&a;
	//int32_t int_a;
	//asm volatile("movl 8(%%esp),%0":"=r"(int_a));
	/*asm volatile("pushl %%eax\n\t
				  movl 8(%%esp),%0\n\t
				  popl %%eax":"=a"(int_a));
	*/
	if(int_a>=0)
		return int_a&(((uint32_t)1<<31)-1);
	else
		return (-int_a)&(((uint32_t)1<<31)-1);
}

/* Functions below are already implemented */

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

