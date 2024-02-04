#define LIM 100000
#define CAP 9592
#define MAXPRIME 100000

unsigned prime[CAP];
unsigned radList[LIM];
unsigned EList[LIM];
unsigned primeSize;

void sortRadsTill(int limit){
    int i,j, sorted = 0;
    unsigned long aux;

    while (!sorted){
        sorted = 1;
        for (i = 0; i < limit; i++)
            for (j = LIM-1; j > i; j--)
                if (radList[i] > radList[j]){
                    aux = radList[i];
                    radList[i] = radList[j];
                    radList[j] = aux;
                    aux = EList[i];
                    EList[i] = EList[j];
                    EList[j] = aux;
                    sorted = 0;
                }else{
                    if (radList[i] == radList[j] && EList[i] > EList[j]){
                        aux = EList[i];
                        EList[i] = EList[j];
                        EList[j] = aux;
                        sorted = 0;
                    }
                }
    }
}

int isPrime(unsigned n){
    unsigned i = 0;

    if (n == 2)
        return 1;
    if (n < 2)
        return 0;
    if (n % 2 == 0)
        return 0;

    for (i = 0; i < primeSize && prime[i] <= sqrt(n); i++)
        if (n % prime[i] == 0)
            return 0;
    return 1;
}

unsigned rad(unsigned n){
    unsigned i = 0,
            aux = n,
            result = 1;

    while (aux > 1){
        if (i < primeSize && prime[i] <= aux && aux % prime[i] == 0 ){
            result *= prime[i];
            do{
                aux /= prime[i];
            }while (aux % prime[i] == 0);
        }
        i++;
    }

    if (result <=1) // this is a prime or 1
        result *= aux;

    return result;
}

int main()
{
    unsigned i = 5, j;

    memset(radList, 0, sizeof(unsigned)*LIM);

    prime[0] = 2;
    prime[1] = 3;
    primeSize = 2;
    while (i <= MAXPRIME && primeSize < LIM){
        if (isPrime(i)){
            j = i;
            while (j < LIM){
                // fill the entries where n = i**k, hence rad(n) = i
                radList[j-1] = i;
                j*=i;
            }
            prime[primeSize] = i;
            primeSize++;
        }
        i+=2;
    }
    printf("%u primes generated...\n", primeSize);

    for (i = 1; i <= LIM; i++){
        EList[i-1] = i;
        if (radList[i-1] == 0)
            radList[i-1] = rad(i);
    }
    printf("%u radicals calculated...\n", i-1);

    sortRadsTill(10000);
    printf("Results up to n=10000 sorted\n");

    printf("E(10000) = %u\n", EList[9999]);
    return 0;
}