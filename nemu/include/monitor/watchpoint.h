#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	struct watchpoint *next;
	
	/* TODO: Add more members if necessary */
	uint32_t last_value;
	char exp[128];
} WP;

#endif
