#include "monitor/watchpoint.h"
#include "monitor/expr.h"
#include "monitor/monitor.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_pool[i].NO = i;
		wp_pool[i].next = &wp_pool[i + 1];
		wp_pool[i].last_value = 0;
		memset(wp_pool[i].exp, 0, sizeof(wp_pool[i].exp));
	}
	wp_pool[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

void new_wp(char *exp) {
	if(free_ == NULL) {
		printf("There is no free watch point in pool.\n");
		assert(0);
	}
	WP* wp = free_;
	free_ = free_->next;
	if(head == NULL) {
		head = wp;
		wp->next = NULL;
		wp->NO = 1;
	}
	else {
		WP* tail = head;
		while(tail->next != NULL) {
			tail = tail->next;
		}
		tail->next = wp;
		wp->next =NULL;
		wp->NO = tail->NO + 1;
	}

	strcpy(wp->exp, exp);
	wp->exp[strlen(exp)] = '\0';

	bool isvalid_expr = false;
	wp->last_value = expr(wp->exp, &isvalid_expr);
}

void free_wp(int index) {
	WP* wp = head;
//	if(wp == NULL) {
//		printf("There is no watchpoint with index = %d.\n", index);
//		assert(0);
//	}
	while(wp != NULL && wp->NO != index) wp = wp->next;
	if(wp == NULL) {
		printf("There is no watchpoint with index = %d.\n", index);
		assert(0);
	}
	
	if(wp == head) head = head->next;
	else {
		WP* q = head;
		while(q->next != wp) q = q->next;
		q->next = wp->next;
	}
	if(free_ == NULL) {
		free_ = wp;
		wp->next = NULL;
	}
	else {
		wp->next = free_;
		free_ = wp;
	}
}

void check_wp(int *state) {
	WP* wp = head;
	uint32_t cur_value = 0;
	bool isvalid_expr = false;
	while(wp != NULL) {
		cur_value = expr(wp->exp, &isvalid_expr);
		if(cur_value != wp->last_value) {
			printf("The value is changed!\n");
			wp->last_value = cur_value;
			*state = STOP;
		}
		wp = wp->next;
	}
}

void print_wp() {
	if(head == NULL) {
		printf("There is no watchpoint.\n");
		return;
	}
	else {
		WP* wp = head;
		while(wp != NULL) {
			printf("#%d:\t%s = 0x%08x\n = %d\n", wp->NO, wp->exp, wp->last_value, wp->last_value);
			wp = wp->next;
		}
	}
}
