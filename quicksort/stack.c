#include "qs_stack.h"
#include <stdlib.h>
#include <stdio.h>




const int sz_stack = max_sz_stack;
struct stack_recursion stack_re;

// 1 - full, 0 - available
int stack_is_full(void)
{
	return (stack_re.curr_pos < sz_stack) ? 0 : 1;
}

// 1 - empty, 0 - available
int stack_is_empty(void)
{
	return (stack_re.curr_pos < 1) ? 1 : 0;
}

int stack_push(recs_t data)
{
	if(stack_is_full()) {
		return -1;
	}

	stack_re.data[stack_re.curr_pos++] = data;

	return 0;
}

int stack_pop(recs_t *data)
{
	if(stack_is_empty()) {
		return -1;
	}

	*data = stack_re.data[--stack_re.curr_pos];

	return 0;
}

int stack_init(void)
{
	recs_t** data;
	data = &stack_re.data;

	*data = (recs_t*)malloc(sizeof(recs_t) * sz_stack);
	if(!(*data)) {
		perror("memory allocation failed");
		return -1;
	}

	stack_re.curr_pos = 0;
	
	return 0;
}

void stack_exit(void)
{
	if(stack_re.data)
		free(stack_re.data);
}

void stack_test(void)
{
	int i, j;
	recs_t data;

	stack_init();

	for(j=0; j<sz_stack; j++)
	{
		i = 0;
		do{
			data.l_limit = i;
			data.r_limit = i*-1;
		}while(i++, !stack_push(data));

		while(!stack_pop(&data))
		{
			printf("%02d, %02d\n", data.l_limit, data.r_limit);
		}
	}

	stack_exit();
}

