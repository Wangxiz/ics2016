#include "cpu/exec/template-start.h"

#define instr add

static void do_execute () {
	DATA_TYPE val = op_dest->val + op_src->val;
	OPERAND_W(op_dest, val);

	UPDATE_EFLAGS_ZF(val);
	UPDATE_EFLAGS_SF(val);
	UPDATE_EFLAGS_PF(val);
	ADD_CF(op_dest->val, op_src->val, val);
	ADD_OF(op_dest->val, op_src->val, val);

//	print_asm_template2();
}

make_instr_helper(r2rm)

#if DATA_BYTE == 2|| DATA_BYTE == 4
make_instr_helper(si2rm)
#endif

#include "cpu/exec/template-end.h"