#ifndef __XOR_H__
#define __XOR_H__

make_helper(xor_i2a_b);		/* 0x34 ok */
make_helper(xor_i2rm_b);	/* 0x80 /6 ok */
make_helper(xor_r2rm_b);	/* 0x30 ok */
make_helper(xor_rm2r_b);	/* 0x32 ok */

make_helper(xor_i2a_v);		/* 0x35 ok */
make_helper(xor_i2rm_v);	/* 0x81 /6 ok */
make_helper(xor_si2rm_v);	/* 0x83 /6 ok */
make_helper(xor_r2rm_v);	/* 0x31 ok */
make_helper(xor_rm2r_v);	/* 0x33 ok */

#endif
