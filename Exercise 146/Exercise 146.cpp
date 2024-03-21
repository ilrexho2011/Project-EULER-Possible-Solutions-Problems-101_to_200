#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <GMP.h>

typedef unsigned long long ul;
typedef long long ll;
typedef unsigned int ui;

char	isvl(ul n) {
	ui r,i,j;
	int t1[]={1,3,7,9,13,27};
	char prm[]={7,11,13,17,19,23,29,31,37,41,43,47,53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
	if (!(n%3)) return 0;
	for (i=0;i<22;i++) {
			r=n%prm[i];
			for (j=0;j<6;j++)
				if (!((r*r+t1[j])%prm[i])) return 0;
	}
	return 1;
}

int main()	{

	mpz_t sumt,n,n1,*cand;
	ul i,j,k,r,lim=150000000;
	ui stm;
	ui t2[]={10,80,130,200};

	stm=clock();

	cand=malloc(20*sizeof(mpz_t));
	for (i=0;i<20;i++) mpz_init_set_ui(cand[i],0);
	mpz_init_set_ui(sumt,0);
	mpz_init(n);
	mpz_init(n1);

	for (i=0,r=0;i<lim+1;i+=210) {	/* Only divisors of 10 -- Incr freq 9,27,3,13,1,7 based
       					   on observation	*/

		for (j=0;j<4;j++)	{
			k=i+t2[j];

			if (!isvl(k)) continue; 

			mpz_set_ui(n,k);
			mpz_mul_ui(n,n,k);
			mpz_add_ui(n,n,9);	/* n*n+9 */
			if (!mpz_probab_prime_p(n,5)) continue;
			mpz_add_ui(n,n,18);	/* n*n+27 */
			if (!mpz_probab_prime_p(n,5)) continue;
			mpz_sub_ui(n,n,24);	/* n*n+3 */
			if (!mpz_probab_prime_p(n,5)) continue;
			mpz_add_ui(n,n,10);	/* n*n+13 */
			if (!mpz_probab_prime_p(n,5)) continue;
			mpz_sub_ui(n,n,12);	/* n*n+1 */
			if (!mpz_probab_prime_p(n,5)) continue;
			mpz_add_ui(n,n,6);	/* n*n+7 */
			if (!mpz_probab_prime_p(n,5)) continue;
			gmp_printf("Found::\t%llu\n",k);
			mpz_add_ui(cand[r],cand[r],k);
			r++;

		}
	}
	/* Remove false positives */
	for (i=0;i<r;i++) 	{
		mpz_mul(n,cand[i],cand[i]);
		mpz_add_ui(n,n,9);
		mpz_nextprime(n1,n);
		mpz_add_ui(n,n,4);
		if (mpz_cmp(n,n1)) {
			gmp_printf("\nRejected %Zd\n",cand[i]);
			continue;
		}
		mpz_nextprime(n1,n);
		mpz_add_ui(n,n,14);
		if (mpz_cmp(n,n1)) {
			gmp_printf("\nRejected %Zd\n",cand[i]);
			continue;
		}
		mpz_add(sumt,sumt,cand[i]);
	}

	gmp_printf("\n\nSum is %Zd\n",sumt);
	gmp_printf("Time::%.4f\n",(double)((clock()-stm)/1000.0));
}