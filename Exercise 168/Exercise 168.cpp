#include <iostream>
using namespace std;
const uint64_t MASK=100000;

int main()
{
    uint64_t sum,a,b,rem,n,den,per;
    sum=(45*1233-480)%MASK;
    for(a=2;a<=9;a++)
    {
        den=10*a-1;
        for(b=a;b<=9;b++)
        {
            rem=b;
            n=0;
            per=0;
            do
            {
                rem*=10;
                n=(10*n+rem/den)%MASK;
                rem%=den;
                per++;
            } while(rem!=b);
            sum=(sum+100/per*n)%MASK;
        }
    }
    cout << sum << endl;
    return 0;
}