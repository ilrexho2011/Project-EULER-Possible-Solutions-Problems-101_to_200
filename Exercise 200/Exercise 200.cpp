#include <stdio.h>
#include <gmpxx.h>
#include <string.h>

#define PRIMES 100000
long primes[PRIMES];


bool stop = false;
int count = 0;

class spider {
public:
	spider(int i, int j) {
		_i = i;
		_j = j;

		mpz_class zi = primes[_i];
		mpz_class zj = primes[_j];

		sqube = zi*zi * zj*zj*zj;

		next = 0;
	}

	void bubble() {
		if (_i <= _j) {
			push(_i, _j+1);
		}
		if (_i == _j) {
			push(_i+1, _j+1);
		}
		if (_i >= _j) {
			push(_i+1, _j);
		}
	}

	void push(int i, int j) {
		if (i==PRIMES || j==PRIMES) {
			printf("*** STOP !!! ***\n");
			stop = true;
		} else {
			push(new spider(i,j));
		}
	}

	void push(spider *other) {
		if (next==0) {
			next = other;
		} else {
			if (next->sqube < other->sqube) {
				next->push(other);
			} else {
				other->next = next;
				next = other;
			}
		}
	}

	int _i;
	int _j;

	spider *next;

	mpz_class sqube;
};

bool isqub200free(spider *top) {
	bool result;
	char *text = mpz_get_str(0, 10, top->sqube.get_mpz_t());

	if (strstr(text, "200")) {
		mpz_class rez;

		result = true;	// so far

		int len = strlen(text);
		char *retext = new char[ len+1 ];
		
		int lastt = text[len-1] - '0';	// le dernier chiffre

		for (int i=0; i<len && result ; i++) {
			int t = text[i] - '0';

			for (int d=0; d<10; d++) {
				if (i==0 && d==0) {
					// il ne faut pas mettre de 0 devant
				} else {
					memcpy(retext, text, len+1);
					retext[i] = d + '0';

					mpz_set_str(rez.get_mpz_t(), retext, 10);

					if (mpz_probab_prime_p(rez.get_mpz_t(),20)) {
						result = false;
						break;
					}
				}
			}
		}

		delete[] retext;
	} else {
		result = false;
	}

	if (result) {
		count++;
		printf("%d => %s (i=%d j=%d)\n", count, text, top->_i, top->_j);
		fflush(stdout);
	}

	free(text);
	return result;
}

int main(int,char**) {
	FILE *file = fopen("../PRIMES/PRIMES.TXT", "r");
	if (file==0) {
		printf("DOO!!!");
		exit(1);
	}

	for (int p=0; p<PRIMES; p++) {
		char text[200];
		fgets(text, sizeof(text), file);
		sscanf(text, "%d", &primes[p]);
	}

	fclose(file);

	spider *top = new spider(0,0);

	while (count<200 && top && !stop) {
		if (top->_i != top->_j) {
			isqub200free(top);
		}

		top->bubble();

		spider *retop = top->next;
		delete top;
		top = retop;
	}

	// cleanup
	while (top) {
		spider *retop = top->next;
		delete top;
		top = retop;
	}

	return 0;
}
