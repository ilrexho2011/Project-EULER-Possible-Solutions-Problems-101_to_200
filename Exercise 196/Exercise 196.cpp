#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//---------------------------------------------------------------------------------------------------------------------
// returns the number of primes, and the sieve containing a bit array filled with primes (bit=0) or composites(bit=1)
//---------------------------------------------------------------------------------------------------------------------
static int ErratSieve(int * &sieve, const int limit)
{
    int prmcount = 0;

    int arraylim = (limit + 31) >> 5;
    int sqrlim = (int)floor(sqrt(limit));

    sieve = new int[arraylim];

    int i,j;

    for(i = 0;i < arraylim;++i)
        sieve[i] = 0x55555555;//0101 0101 0101 0101 0101 0101 0101 0101 binary (sets all even numbers as composite)

    sieve[0] = 0x55555553;//(fist 2 is not a prime)

    ++prmcount;//hardoce the 2 as a prime number

    for(i = 3;i < limit;i += 2)
    {
        if(0 != (sieve[i >> 5] & (1 << (i & 31))))
            continue;

        ++prmcount;
        if(i > sqrlim)//no more multiples of this prime in the range
            continue;

        for(j = i*i;j < limit;j += (i+i))
        {
            sieve[j >> 5] |= (1 << (j & 31));
        }
    }

    return prmcount;
}

//---------------------------------------------------------------------------------------------------------------------
// returns the number of primes, and the sieve containing a bit array filled with primes (bit=0) or composites(bit=1)
// where the first bit coresponds to start
//---------------------------------------------------------------------------------------------------------------------
static int OffsetEratostenes(__int64 start, int len, int * &sieve)
{
    if(start <= 5)
        return -1;//too small start may as well use normal eratostenes

    if(len > 100000000)
        return -2;//too large to actually compute it this way

    if(len <= 0)
        return 0;

    __int64 limitBase = (__int64)sqrt((double)(start+len))+1;

    if(limitBase > 10100000)
    {//the square root of the maximum number is too large
        return -3;
    }

    int primeNumBase;

    primeNumBase = ErratSieve(sieve, (int)limitBase);

    int * primesB = new int[primeNumBase];
    int i;
    primeNumBase = 0;
    for(i = 3;i < limitBase;++i)
    {
        if(0 != (sieve[i >> 5] & (1 << (i & 31))))
            continue;

        primesB[primeNumBase] = i;
        ++primeNumBase;
    }

    delete[] sieve;

    int arraylim = (len + 31) >> 5;
    sieve = new int[arraylim];

    if(0 == (start & 1))
    {//start from even
        for(i = 0;i < arraylim;++i)
            sieve[i] = 0x55555555;//0101 0101 0101 0101 0101 0101 0101 0101 binary (sets all even numbers as composite)
    }
    else
    {//start from odd
        for(i = 0;i < arraylim;++i)
            sieve[i] = 0xAAAAAAAA;//0101 0101 0101 0101 0101 0101 0101 0101 binary (sets all even numbers as composite)
    }

    for(i = 0;i < primeNumBase;++i)
    {
        int j;
        int k = primesB[i];

        j = (int)(start % k);
        if(0 != j)
        {
            j = k - j;
        }

        for(;j < len;j += k)
        {
            sieve[j >> 5] |= (1 << (j & 31));
        }
    }

    delete[] primesB;

    int primesCnt = 0;
    for(i = 0;i < len;++i)
    {
        if(0 == (sieve[i >> 5] & (1 << (i & 31))))
            ++primesCnt;
    }

    return primesCnt;
}

static void FillHas2Primes(int * &has2primes, const int len, const int * const sieve, const int offset)
{
    int arraylimit = (len + 31) >> 5;

    has2primes = new int[arraylimit];

    int i,j,k, cnt;

    for(i = 0;i < arraylimit;++i)
        has2primes[i] = 0;

    for(i = 0,j = offset;i < len;++i,++j)
    {
        if(0 != (sieve[j >> 5] & (1 << (j & 31))))
            continue;

        cnt = 0;//count the adjacent primes
        if(i > 0)
        {
            k = j - len;
            if(0 == (sieve[k >> 5] & (1 << (k & 31))))
                ++cnt;
            k = j - 1;
            if(0 == (sieve[k >> 5] & (1 << (k & 31))))
                ++cnt;
            k = j + len - 1;
            if(0 == (sieve[k >> 5] & (1 << (k & 31))))
                ++cnt;
        }

        if((i + 1) < len)
        {
            k = j - len + 1;
            if(0 == (sieve[k >> 5] & (1 << (k & 31))))
                ++cnt;
            k = j + 1;
            if(0 == (sieve[k >> 5] & (1 << (k & 31))))
                ++cnt;
        }

        if((i + 2) < len)
        {
            k = j - len + 2;
            if(0 == (sieve[k >> 5] & (1 << (k & 31))))
                ++cnt;
        }

        k = j + len;
        if(0 == (sieve[k >> 5] & (1 << (k & 31))))
            ++cnt;
        k = j + len + 1;
        if(0 == (sieve[k >> 5] & (1 << (k & 31))))
            ++cnt;

        if(cnt > 1)
        {
            has2primes[i >> 5] |= (1 << (i & 31));
        }
    }
}

static __int64 FirstElementAt(int N)
{
    __int64 res;

    res = N-1;
    res *= N;
    res /= 2;
    ++res;

    return res;
}

static __int64 S(int N)
{
    if(N <= 2)
        return -1;

    __int64 start = FirstElementAt(N-2);
    __int64 result = 0;

    int * sieve;
    int prmcnt;

    prmcnt = OffsetEratostenes(start, 5*N, sieve);

    if(prmcnt < 0)
        return -2;

    int *has2prms1;
    int *has2prms2;
    int *has2prms3;

    FillHas2Primes(has2prms1, N-1, sieve, N-2);
    FillHas2Primes(has2prms2, N, sieve, 2*N-3);
    FillHas2Primes(has2prms3, N+1, sieve, 3*N-3);

    int i,j,k, cnt;

    for(i = 0,j = 2*N-3;i < N;++i,++j)
    {
        if(0 != (sieve[j >> 5] & (1 << (j & 31))))
            continue;
        cnt = 0;//count the adjacent primes

        if(i > 0)
        {
            k = i - 1;
            if(0 != (has2prms1[k >> 5] & (1 << (k & 31))))
                ++cnt;
            if(0 != (has2prms2[k >> 5] & (1 << (k & 31))))
                ++cnt;
            if(0 != (has2prms3[k >> 5] & (1 << (k & 31))))
                ++cnt;
        }

        if((i + 1) < N)
        {
            k = i;
            if(0 != (has2prms1[k >> 5] & (1 << (k & 31))))
                ++cnt;
            k = i + 1;
            if(0 != (has2prms2[k >> 5] & (1 << (k & 31))))
                ++cnt;
        }

        if((i + 2) < N)
        {
            k = i+1;
            if(0 != (has2prms1[k >> 5] & (1 << (k & 31))))
                ++cnt;
        }

        k = i;
        if(0 != (has2prms2[k >> 5] & (1 << (k & 31))))
            ++cnt;
        if(0 != (has2prms3[k >> 5] & (1 << (k & 31))))
            ++cnt;
        k = i + 1;
        if(0 != (has2prms3[k >> 5] & (1 << (k & 31))))
            ++cnt;

        if(cnt > 0)
        {//it is a part of a prime triplet
            result += start;
            result += j;
        }
    }

    delete[] has2prms3;
    delete[] has2prms2;
    delete[] has2prms1;
    delete[] sieve;

    return result;
}

int main(int argc, char ** argv)
{
    clock_t timeElapsed = clock();
//---------------------------------------------------------------------------------------------------------------------
    __int64 a = S(5678027);
    __int64 b = S(7208785);
    printf("Answer: %I64d\n", a+b);
//---------------------------------------------------------------------------------------------------------------------
    timeElapsed = clock() - timeElapsed;
    double timeElapsedInSec = timeElapsed;
    timeElapsedInSec /= CLOCKS_PER_SEC;
    printf("Total Time Elapsed: %.3lf seconds\n", timeElapsedInSec);

    return 0;
}