/*
	http://terms.naver.com/entry.nhn?docId=2270444&cid=51173&categoryId=51173
	quick sort baad code
	chocokeki@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SHOW_DBG_MSG 1

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

void init_data(unsigned char *box, int boxsz)
{
#if 0
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
