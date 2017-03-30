#include "cpu/exec/template-start.h"

#define if_exec() { OPERAND_W(op_src, 1); }

#define else_exec() { OPERAND_W(op_src, 0); }

#define all_exec() \
static void do_execute() { \
	if(SETFLAG) if_exec()\
	else else_exec();\
	print_asm_template1();\
} \
make_instr_helper(rm) 

#define instr setne
#define SETFLAG cpu.ZF == 0
all_exec();
#undef SETFLAG
#undef instr

#include "cpu/exec/template-end.h"
