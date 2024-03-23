#include <stdio.h>
#include <stdlib.h>
#define max(A,B) (A)>(B)?(A):(B)

long long rowmax(int row, long long *S) {
	int col;
	long long temp = 0LL, max_sum = 0LL;
	for (col = 0; col < 2000; col++) {
		temp += S[2000*row + col];
		if (temp > max_sum) max_sum = temp;
		if (temp <= 0) temp = 0;
	}
	return max_sum;
}

long long colmax(int col, long long *S) {
	int row;
	long long temp = 0LL, max_sum = 0LL;
	for (row = 0; row < 2000; row++) {
		temp += S[2000*row + col];
		if (temp > max_sum) max_sum = temp;
		if (temp <= 0) temp = 0;
	}
	return max_sum;
}

long long SEdiagmax(int diag, long long *S) {
	int row, col;
	long long temp = 0LL, max_sum = 0LL;

	if (diag >= 0) {
		for (row = 0, col = diag; col < 2000; row++, col++) {
			temp += S[2000*row + col];
			if (temp > max_sum)	max_sum = temp;
			if (temp <= 0) temp = 0;
		}
	} else {
		for (row = -diag, col = 0; row < 2000; row++, col++) {
			temp += S[2000*row + col];
			if (temp > max_sum) max_sum = temp;
			if (temp <= 0) temp = 0;
		}
	}
	return max_sum;
}

long long NEdiagmax(int diag, long long *S) {
	int row, col;
	long long temp = 0LL, max_sum = 0LL;

	if (diag < 2000) {
		for (row = diag, col = 0; row >= 0; row--, col++) {
			temp += S[2000*row + col];
			if (temp > max_sum) max_sum = temp;
			if (temp <= 0) temp = 0;
		}
	} else {
		for (row = 1999, col = diag - 1999; col < 2000; row--, col++) {
			temp += S[2000*row + col];
			if (temp > max_sum) max_sum = temp;
			if (temp <= 0) temp = 0;
		}
	}
	return max_sum;
}

int main (void) {
	long long *S = (long long*)calloc(4000001, sizeof(long long));
	S[0] = 0LL;
	long long k = 0;
	for (k = 1LL; k <= 55LL; k++)
		S[k] = ((100003 - 200003*k + 300007*k*k*k) % 1000000) - 500000;
	for (k = 56LL; k <= 4000000LL; k++)
		S[k] = ((S[k-24] + S[k-55] + 1000000) % 1000000) - 500000;
	
	long long row_max = 0, col_max = 0, SE_diag_max = 0, NE_diag_max = 0;
	int temp, n;
	
	for (n = 0; n < 2000; n++)
		if ((temp = rowmax(n, S)) > row_max) row_max = temp;
	for (n = 0; n < 2000; n++)
		if ((temp = colmax(n, S)) > col_max) col_max = temp;
	for (n = -1999; n < 2000; n++)
		if ((temp = SEdiagmax(n, S)) > SE_diag_max) SE_diag_max = temp;
	for (n = 0; n <= 2*(2000-1); n++)
		if ((temp = NEdiagmax(n, S)) > NE_diag_max) NE_diag_max = temp;
	
	printf("%lld\n", max(max(row_max,col_max),max(SE_diag_max,NE_diag_max)));
	
	free(S);
	return 0;
}