#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <malloc.h>

void heapdump(void);


char* itoa(int val, int base) {
	static char buf[32] = { 0 };
	int i = 30;
	for (; val && i; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i + 1];

}

char gaps_and_order(int arr[], int n, char* range, char** comment) { //n-размер массива, char* range - диапазон ([0-9], [a-z], [A-Z])
	printf("[%s] Range symbol codes Analysis.\n", range);
	int bk_counter = 0; //backward counter
	int fd_counter = 0; //forward counter
	int i = 1;
	for (i = 1; i < n; ++i) { //выясняем, как упорядочены коды символов между собой
		switch (arr[i - 1] - arr[i]) {
		case 1:
			printf("Codes of '%c' and '%c' symbols have reverse order.\n", arr[i - 1], arr[i]);
			bk_counter++;
			break;
		case -1:
			printf("Codes of '%c' and '%c' symbols have straight order.\n", arr[i - 1], arr[i]);
			fd_counter++;
			break;
		default:
			printf("No order here.\n");
		}
	}

	if (fd_counter == n - 1 || bk_counter == n - 1) {
		printf("Range from [%s] symbol codes have no gaps.\n We could compare this range as an indivisible piece.\n\n", range);
		char* p = *comment;
		if (n == 1) {
			strcpy(*comment, " ");comment[0]++;
			strcpy(*comment, itoa(arr[0], 10));
		}
		else {
			strcpy(*comment, "s ");
			comment[0]++;comment[0]++;
			strcpy(*comment, itoa(arr[0], 10));
			*comment = strcat(*comment, "-");
			char* tmp;
			tmp = malloc(4 * sizeof(char*));
			strcpy(tmp, itoa(arr[i - 1], 10));
			*comment = strcat(*comment, tmp);
			free(tmp);
		}

		*comment = p;
		return arr[i - 1];
	}
	else {
		return -1; printf("No order here.\n");
	}

	return -1; printf("\n");


}

int main()
{
	int arr_space[1] = { ' ' };
	int arr09[10] = { '0','1','2','3','4','5','6','7','8','9' };
	int arraz[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	int arrAZ[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

	char** str_val;
	str_val = malloc(8 * sizeof(char*));
	int i = 8; while(i) str_val[--i] = malloc(9);

	strcpy(str_val[0],"a-z");
	strcpy(str_val[1],"A-Z");
	strcpy(str_val[2],"0-9");
	strcpy(str_val[3],"Space");


	int sort_arr[4];

	sort_arr[0] = gaps_and_order(arraz, 26, str_val[0], &str_val[0 + 4]);
	sort_arr[1] = gaps_and_order(arrAZ, 26, str_val[1], &str_val[1 + 4]);
	sort_arr[2] = gaps_and_order(arr09, 10, str_val[2], &str_val[2 + 4]);
	sort_arr[3] = gaps_and_order(arr_space, 1, str_val[3], &str_val[3 + 4]);

	for (int j = 1; j < 4; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (sort_arr[i] != -1)
			{
				if (sort_arr[i] > sort_arr[i + 1]) {
					int x = sort_arr[i]; char* y = str_val[i]; char* z = str_val[i + 4];
					sort_arr[i] = sort_arr[i + 1]; str_val[i] = str_val[i + 1]; str_val[i + 4] = str_val[i + 5];
					sort_arr[i + 1] = x; str_val[i + 1] = y; str_val[i + 5] = z;
				}
			}
			else {
				printf("Ranges are not comparable!\n");
				return -1;
			}
		}
	}

	// each range + space to its place in order
	printf("Each range and Space to its place in order:\n");

	for (int i = 0; i < 4; ++i) {
		printf("[%s] have code%s\n", str_val[i], str_val[i + 4]);
	}


	heapdump();printf("\n");
	for (int i = 0; i < 8; i++)
		free(str_val[i]); 
	
	free(str_val);
	heapdump();printf("\n");

	return 0;

}



// crt_heapwalk.c

// This program "walks" the heap, starting
// at the beginning (_pentry = NULL). It prints out each
// heap entry's use, location, and size. It also prints
// out information about the overall state of the heap as
// soon as _heapwalk returns a value other than _HEAPOK
// or if the loop has iterated 100 times.
void heapdump(void)
{
	_HEAPINFO hinfo;
	int heapstatus;
	int numLoops;
	hinfo._pentry = NULL;
	numLoops = 0;
	while ((heapstatus = _heapwalk(&hinfo)) == _HEAPOK ) //&&
	//	numLoops < 10000)
	{
		printf("%8s block at %4.4X of size %4.4X\n",
			(hinfo._useflag == _USEDENTRY ? "USED" : "FREE"),
			hinfo._pentry, hinfo._size);
		numLoops++;
	}

	switch (heapstatus)
	{
	case _HEAPEMPTY:
		printf("OK - empty heap\n");
		break;
	case _HEAPEND:
		printf("OK - end of heap\n");
		break;
	case _HEAPBADPTR:
		printf("ERROR - bad pointer to heap\n");
		break;
	case _HEAPBADBEGIN:
		printf("ERROR - bad start of heap\n");
		break;
	case _HEAPBADNODE:
		printf("ERROR - bad node in heap\n");
		break;
	}
}