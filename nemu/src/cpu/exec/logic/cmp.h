#ifndef __CMP_H__
#define __CMP_H__

make_helper(cmp_r2rm_b);	/* 0x38 ok */
make_helper(cmp_rm2r_b);	/* 0x3A ok */
make_helper(cmp_i2a_b);		/* 0x3C ok */
make_helper(cmp_i2rm_b);	/* 0x80 /7 ok */

make_helper(cmp_si2rm_v);	/* 0x83 /7 ok */
make_helper(cmp_r2rm_v);	/* 0x39 ok */
make_helper(cmp_rm2r_v);	/* 0x3B ok */
make_helper(cmp_i2a_v);		/* 0x3D ok */
make_helper(cmp_i2rm_v);	/* 0x81 /7 ok */

#endif
