#include "cpu/exec/template-start.h"

#define instr cmp

#if DATA_BYTE == 2 || DATA_BYTE == 4
static void do_execute () {
	DATA_TYPE val = op_dest->val - op_src->val;
	ZF(val);
	SF(val);
	SUB_CF(op_dest->val,op_src->val);
	SUB_OF(op_dest->val,op_src->val,val);
	PF(val);
	print_asm_template2();
}

make_instr_helper(si2rm)
#endif

#include "cpu/exec/template-end.h"
