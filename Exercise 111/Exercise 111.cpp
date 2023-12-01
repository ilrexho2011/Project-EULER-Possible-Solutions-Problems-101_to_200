#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <numeric>
#include <iomanip>

#define PRIMESIZE 100100

using namespace std;


vector<int> primes;
bitset<PRIMESIZE> sieve(0);

void buildPrimes(void)
{
    const int root_PS=sqrt(PRIMESIZE);

    int i=2;
    do
    {
        primes.push_back(i);
        int p=2*i;
        do
        {
            sieve.set(p);
            p+=i;
        }
        while(p<PRIMESIZE);

        while(sieve.test(++i));
    }
    while(i<=root_PS);

    for(; i<PRIMESIZE; i+=2)
    {
        if(!sieve.test(i))
        {
            primes.push_back(i);
        }
    }
}

bool isPrime(long long n)
{
    if(n%2==0 || n%3==0 || n%5==0 || n%7==0) return false;

    const int root_n=sqrt(n);

    for(int i=4; primes[i]<=root_n; ++i)
    {
        if(n%primes[i]==0) return false;
    }

    return true;
}


int main(void)
{
    buildPrimes();


    const long long ones=1111111111, zeros=1000000000;

    vector<int> dignum(10);
    vector<long long> sum(10);
    vector< vector<long long> > nums(10);
    long long num, rep, pow10;


    // find the primes with 8 zeros

    for(int i=1; i<10; ++i)
    {
        num=zeros*i;

        for(int j=1; j<10; ++j)
        {
            if(isPrime(num+j))
            {
                nums[0].push_back(num+j);
                dignum[0]=8;
                sum[0]+=num+j;
            }
        }
    }


    // find primes with 9 "repeated" digits

    for(int k=1; k<10; ++k)
    {
        rep=k*ones;

        pow10=1;

        // for all 10 digits...
        for(int i=0; i<10; ++i)
        {
            // ...check all possible values
            for(int j=0; j<10; ++j)
            {
                num=rep-pow10*(k-j);

                // first digit zero?
                if(num-1000000000<0) continue;

                if(isPrime(num))
                {
                    nums[k].push_back(num);
                    dignum[k]=9;
                    sum[k]+=num;
                }
            }

            // next digit
            pow10*=10;
        }
    }


    // find primes with 8 "repeated" digits

    for(int k=0; k<10; ++k)
    {
        // already found primes with more equal digits?
        if(nums[k].size()!=0) continue;

        rep=k*ones;
        pow10=10;

        // for all digits except the last (!)
        for(int j=0; j<9; ++j)
        {
            // check all values
            for(int dig1=0; dig1<10; ++dig1)
            {
                // last digit can's be even
                for(int dig2=1; dig2<10; dig2+=2)
                {
                    num=rep-pow10*(k-dig1)-k+dig2;

                    // first digit zero?
                    if(num-1000000000<0) continue;

                    if(isPrime(num))
                    {
                        nums[k].push_back(num);
                        dignum[k]=8;
                        sum[k]+=num;
                    }
                }
            }

            // next digit
            pow10*=10;
        }

    }


    // result
    cout << "sum: " << accumulate(sum.begin(), sum.end(), 0LL) << endl;

    // write table
    cout << endl << " Digit, d | M(10, d) | N(10, d) | S(10, d)" << endl;
    cout << "          |          |          |" << endl;
    for(int i=0; i<10; ++i)
    {
        cout << setw(9) << i << " | " << setw(8) << dignum[i] << " | "
            << setw(8) << nums[i].size() << " | " << sum[i] << endl;
    }

    // show primes
    for(int i=0; i<10; ++i)
    {
        cout << endl << i << ": ";

        for(int j=0; j<nums[i].size(); ++j)
        {
            cout << nums[i][j] << " ";
        }
    }

    cout << endl;


    return 0;
}