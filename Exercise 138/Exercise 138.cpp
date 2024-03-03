#include<iostream>
#include<cmath>
using namespace std;

long long f[101] , ans = 0;

int main()
{
    f[1] = 1;
    f[2] = 1;
    for(int i = 3 ; i <= 100 ; i++)
        f[i] = f[i-1] + f[i-2];
    for(int i = 1 ; i <= 12 ; i++)
        ans += f[6 * i + 3] / 2;
    cout<<ans<<endl;
    return 0;
}