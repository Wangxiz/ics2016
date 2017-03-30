#include "cpu/exec/template-start.h"

#define instr jmp

/* len: defined in cpu/helper.h */
extern int len;

static void do_execute () {
	if(op_src->type == OP_TYPE_IMM) {
		cpu.eip += op_src->val;
		snprintf(op_src->str, OP_STR_SIZE, "$0x%x", cpu.eip + len + 1);
	}
	else {
		Log("op_src->val: %d, len: %d\n", op_src->val, len);
		cpu.eip = op_src->val;
	}
	print_asm_template1();
}

make_instr_helper(si)
make_instr_helper(rm)

#include "cpu/exec/template-end.h"