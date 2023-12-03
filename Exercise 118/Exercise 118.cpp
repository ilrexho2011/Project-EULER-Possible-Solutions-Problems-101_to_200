#include<stdio.h>

#define MAX 50000
#define LEN 512

int primelist[MAX], ps=0;
int two[9]={1,2,4,8,16,32,64,128,256};
int count[LEN], ks[LEN];

int
isprime(int a)
{
	if(a==1) return 0;
	int i = 2;
	for(; i*i<=a; i++)
		if(a%i==0)
			return 0;
	return 1;
}

int
genprime(int n, int d, int* marked)
{
	int i;

	if(d==9)
		return;

	for(i=0; i<9; i++)
		if(!marked[i]) {
			marked[i]=1;
			if(isprime(10*n+i+1))
				primelist[ps++] = 10*n+i+1;
			genprime(n*10+i+1, d+1, marked);
			marked[i]=0;
		}
}

int
digitsum(int a)
{
	int s=0;
	while(a) {
		s+=two[ a%10 - 1 ];
		a/=10;
	}
	return s;
}

void
countsamedigits()
{
	int i;
	for(i=0; i<ps; i++)
		count[ digitsum( primelist[i] ) ]++;
}

main()
{
	int i, j;
	int marked[]={0,0,0,0,0,0,0,0,0};

	genprime(0, 0, marked);

	countsamedigits();

	ks[0]=1;
	for(i=0; i<LEN; i++) {
		if(count[i]==0)
			continue;
		for(j=LEN-1; j>-1; j--) {
			if((j&i)==0){
				   ks[j+i]=ks[j+i]+ks[j]*count[i];
			}
		}
	}

	printf("%d\n", ks[LEN-1]);

	return 0;
}