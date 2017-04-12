/*
	quick sort sample code using stack
	chocokeki@gmail.com
	for test 

*/
#include <stdio.h>
#include <time.h>
#include "qs_stack.h"


#define SHOW_DBG_MSG 0

#if SHOW_DBG_MSG
#define pdebug(...) printf(__VA_ARGS__)
#else
#define pdebug(...)
#endif

#define ARRAY_LENGTH 20


unsigned char stuff_box[ARRAY_LENGTH] = { 0, };


void show_data(unsigned char *box, int boxsz)
{
	int i;

	for(i=0; i<boxsz; i++)
	{
		printf("%02u ", box[i]);
	}
	
	printf("\n");
}

void swap_data(unsigned char *box, int aidx, int bidx)
{
	unsigned char tmp;

	if(aidx == bidx)
		return ;
	tmp = *(box + aidx);
	*(box + aidx) = *(box + bidx);
	*(box + bidx) = tmp;
}

#define CASESELECT 3 
void init_data(unsigned char *box, int boxsz)
{
#if CASESELECT == 0
	box[0] = 1;
	box[1] = 2;
	box[2] = 3;
	box[3] = 4;
	box[4] = 5;
	box[5] = 6;
	box[6] = 7;
	box[7] = 8;
	box[8] = 9;
	box[9] = 10;
	box[10] = 11;
	box[11] = 12;
	box[12] = 13;
	box[13] = 14;
	box[14] = 15;
	box[15] = 16;
	box[16] = 17;
	box[17] = 18;
	box[18] = 19;
	box[19] = 20;
#elif CASESELECT == 1
	box[0] = 20;
	box[1] = 19;
	box[2] = 18;
	box[3] = 17;
	box[4] = 16;
	box[5] = 15;
	box[6] = 14;
	box[7] = 13;
	box[8] = 12;
	box[9] = 11;
	box[10] = 10;
	box[11] = 9;
	box[12] = 8;
	box[13] = 7;
	box[14] = 6;
	box[15] = 5;
	box[16] = 4;
	box[17] = 3;
	box[18] = 2;
	box[19] = 1;
#elif CASESELECT == 2
	box[0] = 5;
	box[1] = 46;
	box[2] = 37;
	box[3] = 48;
	box[4] = 63;
	box[5] = 47;
	box[6] = 49;
	box[7] = 25;
	box[8] = 53;
	box[9] = 6;
	box[10] = 33;
	box[11] = 71;
	box[12] = 28;
	box[13] = 27;
	box[14] = 44;
	box[15] = 67;
	box[16] = 23;
	box[17] = 54;
	box[18] = 20;
	box[19] = 65;
#else
	int i, data;
	int j, flag;

	for(i=0; i<boxsz; i++)
	{
		data = rand()%80;
		flag = 0;
		
		for(j=0; j<=i; j++)
		{
			if(data == box[j]) {
				flag = 1;
				break;
			}
		}
		
		if(flag) {
			i--;
			continue;
		}

		box[i] = data;
	}
#endif
}


void qs_algo(unsigned char *box, int l_limit, int r_limit, int *new_pivot_idx)
{
	int pivot, l_pos, r_pos;

	if(l_limit >= r_limit) {
		*new_pivot_idx = r_limit;
		return ;	
	}

	pivot = box[l_limit];
	l_pos = l_limit + 1;
	r_pos = r_limit;

	pdebug("\t\t\tli:%d, ri:%d\n", box[l_limit], box[r_limit]);

	do {
		while(l_pos < r_limit)
		{
			if(box[l_pos] > pivot)
				break;
			
			l_pos++;
		}

		while(r_pos > l_limit)
		{
			if(box[r_pos] < pivot)
				break;

			r_pos--;
		}

		if(r_pos > l_pos) {
			swap_data(box, l_pos, r_pos);
			show_data(box, ARRAY_LENGTH);
		}
		else {
			swap_data(box, l_limit, r_pos);
			show_data(box, ARRAY_LENGTH);
			break;
		}
	}while(1);

	*new_pivot_idx = r_pos;
}

void qs_stack(unsigned char *box, int size)
{
	extern struct stack_recursion stack_re;
	extern const int sz_stack;
	recs_t 	stage;
	int pivot, l_limit_idx, r_limit_idx;
	
	stack_init();

	stage.l_limit = 0;
	stage.r_limit = size -1;
	
	do {
		l_limit_idx = stage.l_limit;
		r_limit_idx = stage.r_limit;
		qs_algo(box, l_limit_idx, r_limit_idx, &pivot);

		pdebug("l%d, r%d, p%d\n", l_limit_idx, r_limit_idx, pivot);
		
		if(r_limit_idx > (pivot +1)) {
			pdebug("R: pv%d, %d, %d\n", box[pivot], box[(pivot +1)], box[r_limit_idx]);
			stage.l_limit = pivot +1;
			stack_push(stage);
		}

		if(l_limit_idx < (pivot -1)) {
			stage.l_limit = l_limit_idx;
			stage.r_limit = pivot -1;
			pdebug("L: pv%d, %d, %d\n", box[pivot], box[l_limit_idx], box[(pivot -1)]);
			stack_push(stage);
		}
	}while(!stack_pop(&stage));

	stack_exit();
}


int main()
{
	srand(time(NULL));

	init_data(stuff_box, ARRAY_LENGTH);
	printf("start\n");
	show_data(stuff_box, ARRAY_LENGTH);
	
	printf("\nprogress\n"); int j;
#if 0
	qs_algo(stuff_box, 0, 19, &j);
#else
	qs_stack(stuff_box, ARRAY_LENGTH);	
#endif
	printf("\nend\n");
	show_data(stuff_box, ARRAY_LENGTH);

	return 0;
}
