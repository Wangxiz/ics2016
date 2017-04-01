#ifndef __TEST_H__
#define __TEST_H__

make_helper(test_r2rm_b);	/* 0x84 ok */
make_helper(test_i2rm_b);	/* 0xF6 /0 ok */
make_helper(test_i2a_b);	/* 0xA8 ok */

make_helper(test_r2rm_v);	/* 0x85 ok */
make_helper(test_i2rm_v);	/* 0xF7 /0 ok */
make_helper(test_i2a_v);	/* 0xA9 ok */

#endif