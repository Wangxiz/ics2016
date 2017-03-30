#ifndef __AND_H__
#define __AND_H__

make_helper(and_i2a_b);		// ok
make_helper(and_i2rm_b);	// ok
make_helper(and_r2rm_b);	// ok
make_helper(and_rm2r_b);	// ok

make_helper(and_i2a_v);		// ok
make_helper(and_i2rm_v);	// ok
make_helper(and_si2rm_v);	// ok
make_helper(and_r2rm_v);	// ok
make_helper(and_rm2r_v);	// ok

#endif
