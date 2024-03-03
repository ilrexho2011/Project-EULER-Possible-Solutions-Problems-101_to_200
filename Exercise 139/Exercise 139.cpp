#include<iostream>
#include<cmath>
using namespace std;

long long a[101] , b[101] , c[101];
long long LIM = 100000000 , ans = 0;

int main()
{
    a[0] = 0;
    a[1] = 3;
    ans += LIM / 12;
    for(int i = 2 ; i <= 100 ; i++)
    {
        a[i] = 6 * a[i-1] - a[i-2] + 2;
        b[i] = a[i] + 1;
        c[i] = (long long) sqrt((double)(a[i] * a[i] + b[i] * b[i]));
        long long d = a[i] + b[i] + c[i];
        if(a[i] + b[i] + c[i] >= LIM)
            break;
        ans += LIM / d;
    }
    cout<<ans<<endl;
    return 0;
}