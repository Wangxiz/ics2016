#ifndef __JCC_H__
#define __JCC_H__

make_helper(jo_si_b);	/* 0x70 ok */
make_helper(jno_si_b);	/* 0x71 ok */
make_helper(jb_si_b);	/* 0x72 ok */
make_helper(jae_si_b);	/* 0x73 ok */
make_helper(je_si_b);	/* 0x74 ok */
make_helper(jne_si_b);	/* 0x75 ok */
make_helper(jbe_si_b);	/* 0x76 ok */
make_helper(ja_si_b);	/* 0x77 ok */
make_helper(js_si_b);	/* 0x78 ok */
make_helper(jns_si_b);	/* 0x79 ok */
make_helper(jl_si_b);	/* 0x7c ok */
make_helper(jge_si_b);	/* 0x7d ok */
make_helper(jle_si_b);	/* 0x7e ok */
make_helper(jg_si_b);	/* 0x7f ok */

make_helper(jo_si_v);	/* 0x0f 0x80 ok */
make_helper(jno_si_v);	/* 0x0f 0x81 ok */
make_helper(jb_si_v);	/* 0x0f 0x82 ok */
make_helper(jae_si_v);	/* 0x0f 0x83 ok */
make_helper(je_si_v);	/* 0x0f 0x84 ok */
make_helper(jne_si_v);	/* 0x0f 0x85 ok */
make_helper(jbe_si_v);	/* 0x0f 0x86 ok */
make_helper(ja_si_v);	/* 0x0f 0x87 ok */
make_helper(js_si_v);	/* 0x0f 0x88 ok */
make_helper(jns_si_v);	/* 0x0f 0x89 ok */
make_helper(jl_si_v);	/* 0x0f 0x8c ok */
make_helper(jge_si_v);	/* 0x0f 0x8d ok */
make_helper(jle_si_v);	/* 0x0f 0x8e ok */
make_helper(jg_si_v);	/* 0x0f 0x8f ok */

#endif