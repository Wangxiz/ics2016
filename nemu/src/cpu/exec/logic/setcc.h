#ifndef __SETCC_H__
#define __SETCC_H__

make_helper(setne_rm_b);	/* 0x95 ok */
make_helper(setnbe_rm_b);	/* 0x97 ok */
make_helper(setae_rm_b);	/* 0x93 ok */
make_helper(setb_rm_b);		/* 0x92 ok */
make_helper(setbe_rm_b);	/* 0x96 ok */
make_helper(sete_rm_b);		/* 0x94 ok */
make_helper(setg_rm_b);		/* 0x9F ok */
make_helper(setge_rm_b);	/* 0x9D ok */
make_helper(setl_rm_b);		/* 0x9C ok */
make_helper(setle_rm_b);	/* 0x9E ok */
make_helper(setno_rm_b);	/* 0x91 ok */
make_helper(setnp_rm_b);	/* 0x9B ok */
make_helper(setns_rm_b);	/* 0x99 ok */
make_helper(seto_rm_b);		/* 0x90 ok */
make_helper(setp_rm_b);		/* 0x9A ok */
make_helper(sets_rm_b);		/* 0x98 ok */

#endif
