#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute() {
	
}

make_instr_helper(n)

#include "cpu/exec/template-end.h"