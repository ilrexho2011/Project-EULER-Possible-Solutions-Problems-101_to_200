#include <stdio.h>

#define	true				1
#define false				0

typedef unsigned long int number;

#define LIMIT				10000000
#define MAX_DIGITS			20

char buf[MAX_DIGITS+1];

int bouncy(number n)
{
	register char *p=buf,last=0;
	int increasing=true,decreasing=true;

	if (n < 100)	return false;

	sprintf(buf,"%lu",n);
	while (*p)
	{
		if (last)
			if (*p > last)			decreasing=false;
			else if (*p < last)		increasing=false;
		last=*p++;
	}

	if (!increasing && !decreasing)	return true;
	return false;
}

int main(int argc, char *argv[])
{
	register number i;
	number	count=0;
	int f50=false,f90=false,f99=false;

	for (i = 100; !f99 && i < LIMIT; i++)
	{
		if (bouncy(i))	count++;

		if (i==100)	continue;

		if (i == 999)
			printf("%lu bouncy below 1000.\n", count);

		if (!f50 && 100 * count / i >= 50) 
		{
			printf("50%c at %lu\n", '%',i);
			f50=true;
		}
		if (!f90 && 100 * count / i >= 90) 
		{
			printf("90%c at %lu\n", '%',i);
			f90=true;
		}
		if (!f99 && 100 * count / i >= 99)
		{
			printf("99%c at %lu\n", '%',i);
			f99=true;
			break;
		}
	}
	return 0;
}