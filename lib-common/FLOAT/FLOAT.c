#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	// int s1 = (a >> 31);
	// int s2 = (b >> 31);
	
	// if(s1 == 1) a = -a;
	// if(s2 == 1) b = -b;

	// unsigned int a1 = (a >> 16);
	// unsigned int b1 = (b >> 16);

	// unsigned int a0 = a & 0xFFFF;
	// unsigned int b0 = b & 0xFFFF;

	// unsigned int c0, c1, c2, c3;

	// c0 = a0 * b0;
	// c1 = 

	return (a * b) >> 16;
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
	long long bcs = a << 16;
	int low_32 = bcs & 0xFFFFFFFF;
	int high_32 = (bcs >> 32) & 0xFFFFFFFF;
	FLOAT result;
	int yushu;
	asm volatile ("idiv %2" : "=a"(result), "=d"(yushu) : "r"(b), "a"(low_32), "d"(high_32));
	return result;
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

	// nemu_assert(0);
	int int_float = *(int*)&a;
	int frac = int_float &((1 << 23) - 1);
	int exp = (int_float >> 23) & ((1 << 8) - 1) -127;
	int sign = int_float >> 31;

	int result = 1, i;
	for(i = 1; i < exp + 16; ++ i) {
		result = (result << 1) + ((frac & (1 << 22)) >> 22);
		if(result < 0) {
			return 0x80000000u;
		}
		frac <<= 1;
    }
    if(sign == 1) {
        result = (~result) + 1;
    }
    return result;
}

FLOAT Fabs(FLOAT a) {
	return (a > 0) ? a : -a;
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

