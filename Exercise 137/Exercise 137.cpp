#include<iostream>
using namespace std;

long long a[101];

int main()
{
    /*int cnt = 0;
    long long u = 1;
    for(long long a = 1 ; ; a ++)
    {
        long long t = (a + 1) * (a + 1) + (2 * a) * (2 * a);
        while(u * u < t)
            u ++;
        if(u * u == t)
        {
            cout<<++cnt<<" "<<a<<endl;
            if(cnt == 15)
                break;
        }
    }*/
    a[1] = 1;
    a[2] = 2;
    for(int i = 3 ; i <= 30 ; i++)
        a[i] = a[i-1] + a[i-2];
    cout<<a[29] * a[30]<<endl;
    return 0;
}