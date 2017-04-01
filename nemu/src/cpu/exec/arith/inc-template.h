#include "cpu/exec/template-start.h"

#define instr inc

static void do_execute () {
	DATA_TYPE val = op_src->val + 1;
	OPERAND_W(op_src, val);

	UPDATE_EFLAGS_ZF(val);
	UPDATE_EFLAGS_SF(val);
	UPDATE_EFLAGS_PF(val);

	ADD_OF(op_src->val, 1, val);

	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"
