#include<iostream>
using namespace std;

int f(int x)
{
    if(x % 2 == 0 || x % 5 == 0)
        return 0;
    int t = 1 , cnt = 1;
    while(t != 0)
    {
        cnt ++;
        t = (t * 10 + 1) % x;
    }
    return cnt;
}

int main()
{
    for(int i = 1000000 ; ; i++)
        if(f(i) > 1000000)
        {
            cout<<i<<endl;
            break;
        }
    return 0;
}