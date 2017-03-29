#include "cpu/exec/template-start.h"

#define instr test

static void do_execute() {
	DATA_TYPE val = op_src->val & op_dest->val;
	
	SET_EFLAGS_CF(0);
	SET_EFLAGS_OF(0);

	UPDATE_EFLAGS_PF(val);
	UPDATE_EFLAGS_ZF(val);
	UPDATE_EFLAGS_SF(val);

	print_asm_template2();
}

make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"