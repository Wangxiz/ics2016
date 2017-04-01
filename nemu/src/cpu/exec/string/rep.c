#include "cpu/exec/helper.h"

make_helper(exec);

make_helper(rep) {
	int len;
	int count = 0;
	int op = instr_fetch(eip, 1);
	if(instr_fetch(eip + 1, 1) == 0xc3) {
		/* repz ret */
		exec(eip + 1);
		len = 0;
	}
	else {
		while(cpu.ecx) {
			// Log("EIP: 0x%08x\n", eip);
			exec(eip + 1);
			count ++;
			cpu.ecx --;
			assert(ops_decoded.opcode == 0xa4	// movsb
				|| ops_decoded.opcode == 0xa5	// movsw
				|| ops_decoded.opcode == 0xaa	// stosb
				|| ops_decoded.opcode == 0xab	// stosw
				|| ops_decoded.opcode == 0xa6	// cmpsb
				|| ops_decoded.opcode == 0xa7	// cmpsw
				|| ops_decoded.opcode == 0xae	// scasb
				|| ops_decoded.opcode == 0xaf	// scasw
				);

			/* TODO: Jump out of the while loop if necessary. */
			// if((ops_decoded.opcode == 0xa6
			//  || ops_decoded.opcode == 0xa7
			//  || ops_decoded.opcode == 0xae
			//  || ops_decoded.opcode == 0xaf) && cpu.ZF == 0)
			// 	break;
			// Log("EIP: 0x%08x\n", eip);

		    if (   ops_decoded.opcode == 0xa6	    // cmpsb
				|| ops_decoded.opcode == 0xa7	    // cmpsw
				|| ops_decoded.opcode == 0xae	    // scasb
				|| ops_decoded.opcode == 0xaf) {	// scasw
                if (op == 0xf3) { // rep, repe
    			    if (cpu.ZF == 0) break;
                } else if (op == 0xf2) { // repne
                    if (cpu.ZF == 1) break;
                } else {
                    panic("invalid rep op %02X", op);
                }
			}

		}
		len = 1;
	}

#ifdef DEBUG
	char temp[80];
	sprintf(temp, "rep %s", assembly);
	sprintf(assembly, "%s[cnt = %d]", temp, count);
#endif
	
	return len + 1;
}

make_helper(repnz) {
	int count = 0;
	int op = instr_fetch(eip, 1);
	while(cpu.ecx) {
		exec(eip + 1);
		count ++;
		cpu.ecx --;
		assert(ops_decoded.opcode == 0xa6	// cmpsb
				|| ops_decoded.opcode == 0xa7	// cmpsw
				|| ops_decoded.opcode == 0xae	// scasb
				|| ops_decoded.opcode == 0xaf	// scasw
			  );

		/* TODO: Jump out of the while loop if necessary. */
		// if((ops_decoded.opcode == 0xa6
		//  || ops_decoded.opcode == 0xa7
		//  || ops_decoded.opcode == 0xae
		//  || ops_decoded.opcode == 0xaf) && cpu.ZF == 0)
		// 	break;

		    if (   ops_decoded.opcode == 0xa6	    // cmpsb
				|| ops_decoded.opcode == 0xa7	    // cmpsw
				|| ops_decoded.opcode == 0xae	    // scasb
				|| ops_decoded.opcode == 0xaf) {	// scasw
                if (op == 0xf3) { // rep, repe
    			    if (cpu.ZF == 0) break;
                } else if (op == 0xf2) { // repne
                    if (cpu.ZF == 1) break;
                } else {
                    panic("invalid rep op %02X", op);
                }
			}
	}

#ifdef DEBUG
	char temp[80];
	sprintf(temp, "repnz %s", assembly);
	sprintf(assembly, "%s[cnt = %d]", temp, count);
#endif

	return 1 + 1;
}
