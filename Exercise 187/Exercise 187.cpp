#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <time.h>
#define MAX 100000000

int *make_sieve(int max)
{
	int *res;
	int i, j;
	int limit;

	res = malloc(sizeof(int) * max);
	limit = sqrt(max);

	for (i = 2; i < max; i++)
		res[i] = 0;
	
	for (i = 2; i < limit; i++) {
		if (!res[i]) {
			for (j = i; j < max / i + 1; j++)
				res[j*i] = 1;
		}
	}

	return res;	
}

int main()
{
        time_t start,end;
	int i, j;
	int cnt = 0;
	int res;
	int *sieve = (int *) malloc(sizeof(int) * (MAX+1));

	time (&start);
	sieve = make_sieve(MAX);

	for (i = 2; i < MAX; i++)
		if (!sieve[i])
			for (j = i; j < MAX / i + 1; j++) {
				if (!sieve[j]) {
					res = j*i;
				
					if (res < MAX)
						cnt++;
				}
			}	
	time (&end);		
	printf("%d in %.4f secs\n", cnt, difftime (end,start));

	return 0;
}
