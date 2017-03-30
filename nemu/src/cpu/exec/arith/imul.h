#ifndef __IMUL_H__
#define __IMUL_H__

make_helper(imul_rm2a_b);	/* 0xF6 /5 ok */

make_helper(imul_rm2a_v);	/* 0xF7 /5 ok */
make_helper(imul_rm2r_v);	/* 0x0F 0xAF ok */
make_helper(imul_si_rm2r_v);	/* 0x6B */
make_helper(imul_i_rm2r_v);		/* 0x69 */

#endif
