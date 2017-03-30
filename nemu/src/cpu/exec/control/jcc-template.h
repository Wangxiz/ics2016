#include "cpu/exec/template-start.h"

// len: defined in cpu/helper.h
extern int len;
// tested
#define if_exec() {\
	cpu.eip += op_src->val;\
	snprintf(op_src->str, OP_STR_SIZE, "$0x%x", cpu.eip + len + 1);\
}

#define else_exec() \
	snprintf(op_src->str, OP_STR_SIZE, "$0x%x", cpu.eip + op_src->val + len + 1)

#define all_exec() \
static void do_execute() { \
	if(JMPFLAG) if_exec()\
	else else_exec();\
	print_asm_template1();\
} \
make_instr_helper(si) 

#define instr je
#define JMPFLAG cpu.ZF == 1
all_exec();
#undef JMPFLAG
#undef instr

#include "cpu/exec/template-end.h"