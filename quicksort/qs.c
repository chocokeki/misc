/*
	http://terms.naver.com/entry.nhn?docId=2270444&cid=51173&categoryId=51173
	quick sort baad code
	chocokeki@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	tmp = *(box + aidx);
	*(box + aidx) = *(box + bidx);
	*(box + bidx) = tmp;
}

int check_exit(int l_limit_idx, int r_limit_idx)
{
	return (l_limit_idx >= r_limit_idx) ? 1 : 0;
}


void qs(unsigned char *box, int l_limit_idx, int r_limit_idx)
{
	int i, j;
	int pivot, l_pos, r_pos;

	if(check_exit(l_limit_idx, r_limit_idx))
		return ;

	pdebug("\t\t\tstart new qs - l_idx:%02d, r_idx:%02d\n", l_limit_idx, r_limit_idx);

	pivot = box[l_limit_idx];

	for(l_pos = l_limit_idx+1, r_pos = r_limit_idx; ; l_pos = i, r_pos = j)
	{
		for(i=l_pos; i<=r_limit_idx; i++)
		{
			if(box[i] > pivot) {
				pdebug("\t\t\tl_pos - data:%02d, ith:%02d, pivot:%02d\n", box[i], i, pivot); 
				break;
			}
		}//find left to right(=>>)

		for(j=r_pos; j>=l_limit_idx; j--)
		{
			if(box[j] < pivot) {
				pdebug("\t\t\tr_pos - data:%02d, ith:%02d, pivot:%02d\n", box[j], j, pivot); 
				break;
			}
		}//find right to left(<<=)

		if(i > r_limit_idx)		//check edge - if could not find
			i = r_limit_idx;
		if(j < l_limit_idx) 		//check edge - if could not find
			j = l_limit_idx;

		if(i < j) {
			swap_data(box, i, j);
			show_data(box, ARRAY_LENGTH);
		}
		else {
			swap_data(box, j, l_limit_idx);		// j == pivot index
			show_data(box, ARRAY_LENGTH);
			break;
		}
	}

	qs(box, l_limit_idx, j-1);
	qs(box, j+1, r_limit_idx);
}

#define CASESELECT 2
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

int main()
{
	srand(time(NULL));

	init_data(stuff_box, ARRAY_LENGTH);
	show_data(stuff_box, ARRAY_LENGTH);
	
	qs(stuff_box, 0, ARRAY_LENGTH-1);
	show_data(stuff_box, ARRAY_LENGTH);

	return 0;
}
