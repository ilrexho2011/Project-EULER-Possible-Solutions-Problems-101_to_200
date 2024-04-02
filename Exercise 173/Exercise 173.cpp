#include <stdio.h>
#include <string.h>
#include <math.h>

#define true				1
#define false				0

#define LIMIT				1000000

typedef long long unsigned int	number;


int main(int argc, char *argv[])
{
	number n,m,num=0;

	for (n=3; 4 * n - 4 <= LIMIT; n+=2)
	{
		for (m=1; m <=n-2; m+=2)
		{
			if (n*n-m*m <= LIMIT)	num++;
		}
	}

	for (n=4; 4 * n - 4 <= LIMIT; n+=2)
	{
		for (m=2; m <=n-2; m+=2)
		{
			if (n*n-m*m <= LIMIT)	num++;
		}
	}

	printf("Num hollow square lamina is %llu\n", num);
	return 0;
}