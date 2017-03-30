#ifndef __ADD_H__
#define __ADD_H__

make_helper(add_r2rm_b);	/* 0x00 ok */
make_helper(add_rm2r_b);	/* 0x02 ok */
make_helper(add_i2a_b);		/* 0x04 ok */

make_helper(add_si2rm_v);	/* 0x83 /0 ok */
make_helper(add_r2rm_v);	/* 0x01 ok */
make_helper(add_rm2r_v);	/* 0x03 ok */
make_helper(add_i2a_v);		/* 0x05 ok */

#endif
