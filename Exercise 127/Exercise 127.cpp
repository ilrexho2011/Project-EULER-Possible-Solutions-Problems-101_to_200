#include <iostream>

using namespace std;

bool prime[1000001];
long long  rad_table[110000];

void generatePrimes()
{
    memset(prime, true, 1000000);

    prime[0] = false;
    prime[1] = false;

    for (int i = 2; i <= 1000; i++)
        if (prime[i])
            for (int j = i*i; j <= 1000000; j += i)
                prime[j] = false;
}
int gcd (int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long rad (long long n, long long  start)
{
    if (n <= 1000000 && prime[n] && n >= start)
        return n;

    for (long long i = start; i <= n/2; i++)
    {
        if (prime[i] && n % i == 0)
        {
            return i * rad(n/i, i + 1);
        }
    }
    return 1;
}

void calcRad()
{
    for (int i = 1; i <= 110000; i++)
        rad_table[i] = rad(i, 2);
}

long long solve()
{
    long long sum = 0;
    for (int i = 1; i < 110000; i++)
    {
        if (!prime[i])
        {
            for (int j = 1; j <= i/2; j++)
            {
                if (j < (i - j) && gcd(rad_table[i - j], rad_table[j]) == 1)
                {
                    long long radn = rad_table[i] * rad_table[j] * rad_table[i - j];

                    if (radn < i)
                    {
                        sum += i;
                    }
                }
            }
        }
    }
    return sum;
}

int main()
{
    generatePrimes();
    calcRad();
    cout << solve() << endl;
    return 0;
}