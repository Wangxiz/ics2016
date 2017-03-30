#ifndef __JCC_H__
#define __JCC_H__

make_helper(je_si_b);	/* 0x74 ok */
make_helper(jbe_si_b);	/* 0x76 ok */
make_helper(jne_si_b);	/* 0x75 ok */

make_helper(je_si_v);	/* 0x0f 0x84 ok */
make_helper(jbe_si_v);	/* 0x0f 0x86 ok */
make_helper(jne_si_v);	/* 0x0f 0x85 ok */

#endif