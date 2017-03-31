#ifndef __SBB_H__
#define __SBB_H__

make_helper(sbb_i2a_b);		/* 0x1c ok */
make_helper(sbb_i2rm_b);	/* 0x80 /3 ok */
make_helper(sbb_r2rm_b);	/* 0x18 ok */
make_helper(sbb_rm2r_b);	/* 0x1a ok */

make_helper(sbb_i2a_v);		/* 0x1d ok */
make_helper(sbb_i2rm_v);	/* 0x81 /3 ok */
make_helper(sbb_si2rm_v);	/* 0x83 /3 ok */
make_helper(sbb_r2rm_v);	/* 0x19 ok */
make_helper(sbb_rm2r_v);	/* 0x1b ok */

#endif
