/*
	test only
	chocokeki@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>

const int sz_stack = 100;

typedef struct {
	int value;
}recs_t;

struct stack_recursion{
	int 	curr_pos;
	recs_t 	*data;
};

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
	if(*data == NULL) {
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
			data.value = i;
		}while(i++, !stack_push(data));

		while(!stack_pop(&data))
		{
			printf("%02d\n", data.value);
		}
	}

	stack_exit();
}


int fact_recursive(int data)
{
	return (data == 1) ? 1 : fact_recursive(data - 1)*data;
}

int fact_stack(int input)
{
	int result;
	recs_t data;

	stack_init();
	
	do{
		data.value = input;
		stack_push(data);
		input--;
	}while(input > 0);	

	result = 1;
	while(!stack_pop(&data))
	{
		result *= data.value;
	}

	stack_exit();

	return result;
}

int main(void)
{

	int i;
	const int max = 12;

	printf("recursion start\n");
	for(i=1; i<max; i++)
	{
		printf("%02d : %09d\n", i, fact_recursive(i));
	}

	printf("stack start\n");
	for(i=1; i<max; i++)
	{
		printf("%02d : %09d\n", i, fact_stack(i));
	}

	return 0;
}
