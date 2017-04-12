#ifndef _qs_stack_h_
#define _qs_stack_h_

#define max_sz_stack 100


typedef struct {
	int l_limit;
	int r_limit;
}recs_t;

struct stack_recursion{
	int 	curr_pos;
	recs_t 	*data;
};


int stack_is_full(void);
int stack_is_empty(void);
int stack_push(recs_t data);
int stack_pop(recs_t *data);
int stack_init(void);
void stack_exit(void);
void stack_test(void);

#endif
