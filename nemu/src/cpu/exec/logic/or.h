#ifndef __OR_H__
#define __OR_H__

make_helper(or_i2a_b);		/* 0x0c ok */
make_helper(or_i2rm_b);		/* 0x80 /1 ok */
make_helper(or_r2rm_b);		/* 0x08 ok */
make_helper(or_rm2r_b);		/* 0x0a ok */

make_helper(or_i2a_v);		/* 0x0d ok */
make_helper(or_i2rm_v);		/* 0x81 /1 ok */
make_helper(or_si2rm_v);	/* 0x83 /1 ok */
make_helper(or_r2rm_v);		/* 0x09 ok */
make_helper(or_rm2r_v);		/* 0x0b ok */

#endif
