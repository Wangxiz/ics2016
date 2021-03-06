#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);

uint32_t my_atoi(char *arg);
uint32_t my_htoi(char *arg);

void new_wp(char* exp);
void free_wp(int index);
void print_wp();

/* We use the `readline' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_si(char *args) {
	int steps = 0, i;
	if(args == NULL) steps = 1;
	else {
		for(i = 0; i < strlen(args); ++i) {
			if(args[i] < '0' || args[i] > '9') return 0;
			steps = steps * 10 + args[i] - '0';
		}
	}
	cpu_exec(steps);
	return 0;
}

static int cmd_info(char *args) {
	char *arg = strtok(NULL, " ");
	if(arg == NULL) {
		return 0;
	}
	else if(strcmp(arg, "r") == 0) {
		int i;
		for(i = 0; i < 8; i++) {
			printf("%s\t0x%08x\t%d\n", regsl[i], cpu.gpr[i]._32, cpu.gpr[i]._32);
		}
		printf("eip\t0x%08x\t%d\n", cpu.eip, cpu.eip);
	}
	else if(strcmp(arg, "w") == 0) {
		print_wp();
	}
	return 0;
}

static int cmd_p(char *args) {
//	char *arg = strtok(NULL, " ");
	if(args == NULL) {
		return 0;
	}
	else {
		bool isvalid_expr = false;
		uint32_t val = expr(args, &isvalid_expr);
		if(isvalid_expr) {
			printf("\tDEC:\t%u\n", val);
			printf("\tHEX:\t0x%08x\n", val);
		}
	}
	return 0;
}

static int cmd_x(char *args) {
	if(args == NULL) return 0;
	char *arg = strtok(NULL, " ");
	if(arg == NULL) return 0;
	int i, offset = 0;
	for(i = 0; i < strlen(arg); ++i) {
		if(arg[i] > '9' || arg[i] < '0') return 0;
		offset = offset * 10 + arg[i] - '0';
	}
	arg = strtok(NULL, " ");
	bool isvalid_expr = false;
	uint32_t addr = expr(arg, &isvalid_expr);
	if(isvalid_expr) {
		for(i = 0; i < offset; ++i) {
			printf("0x%08x:\t0x%08x\n", addr + 4 * i, swaddr_read(addr + 4 * i, 4));
		}
	}
	return 0;
}

static int cmd_w(char *args) {
	if(args == NULL) return 0;
	
	bool isvalid_expr = false;
	expr(args, &isvalid_expr);
	if(!isvalid_expr) return 0;
	
	new_wp(args);
	return 0;
}

static int cmd_d(char *args) {
	if(args == NULL) return 0;
	int index = 0, i;
	for(i = 0; i < strlen(args); ++i) {
		if(args[i] > '9' || args[i] < '0') return 0;
		index = index * 10 + args[i] - '0';
	}
	free_wp(index);
	return 0;
}

static int cmd_help(char *args);

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
	/* TODO: Add more commands */

	{ "si", "Single execution", cmd_si},
	{ "info", "Print informations about registers or watch points", cmd_info},
	{ "p", "Expression evaluation", cmd_p},
	{ "x", "Scan memory", cmd_x},
	{ "w", "Set a watch point", cmd_w},
	{ "d", "Delete a watch point", cmd_d}
};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
