#ifndef __FLOAT_H__
#define __FLOAT_H__

#include "trap.h"

typedef int FLOAT;

static inline int F2int(FLOAT a) {
	return a >> 16;
}

static inline FLOAT int2F(int a) {
	nemu_assert((a >= -(2 << 15)) && (a < (2 << 15)));
	// Assert((a >= -(2 << 15)) && (a < (2 << 15)), "\033[1;31mThis integer overflow the scope of FLOAT!\033[0m");
	return a << 16;
}

static inline FLOAT F_mul_int(FLOAT a, int b) {
	return a * b;
}

static inline FLOAT F_div_int(FLOAT a, int b) {
	nemu_assert(b != 0);
	// Assert(b != 0, "\033[1;31mThe divisor is 0!\033[0m");
	return a / b;
}

FLOAT f2F(float);
FLOAT F_mul_F(FLOAT, FLOAT);
FLOAT F_div_F(FLOAT, FLOAT);
FLOAT Fabs(FLOAT);
FLOAT sqrt(FLOAT);
FLOAT pow(FLOAT, FLOAT);

// used when calling printf/sprintf to format a FLOAT argument
#define FLOAT_ARG(f) (long long)f

void init_FLOAT_vfprintf(void);

#endif