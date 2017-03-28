#include "cpu/exec/template-start.h"

#define instr call

static void do_execute() {
	
}

//#if DATA_BYPE == 1 || DATA_BYPE == 4
make_instr_helper(si)
//#endif

#include "cpu/exec/template-end.h"
