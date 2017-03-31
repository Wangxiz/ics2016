#ifndef __SUB_H__
#define __SUB_H__

make_helper(sub_r2rm_b);	/* 0x28 ok */
make_helper(sub_rm2r_b);	/* 0x2a ok */
make_helper(sub_i2rm_b);	/* 0x80 /5 */
make_helper(sub_i2a_b);		/* 0x2c ok */

make_helper(sub_si2rm_v);	/* 0x83 /5 ok */
make_helper(sub_r2rm_v);	/* 0x29 ok */
make_helper(sub_rm2r_v);	/* 0x2b ok */
make_helper(sub_i2rm_v);	/* 0x81 /5 */
make_helper(sub_i2a_v);		/* 0x2d ok */

#endif
