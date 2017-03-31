#include "cpu/exec/template-start.h"

#define instr sub
// tested
static void do_execute () {
	DATA_TYPE val = op_dest->val - op_src->val;
	OPERAND_W(op_dest, val);

	UPDATE_EFLAGS_ZF(val);
	UPDATE_EFLAGS_SF(val);
	UPDATE_EFLAGS_PF(val);
	SUB_CF(op_dest->val, op_src->val);
	SUB_OF(op_dest->val, op_src->val, val);

	print_asm_template2();
}

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif

make_instr_helper(r2rm)
make_instr_helper(rm2r)
make_instr_helper(i2rm)
make_instr_helper(i2a)

#include "cpu/exec/template-end.h"