#include<iostream>
#define M 47
#define N 43

using namespace std;

long int Sum_N(int n)
{
    long int sum=0;

    sum = n* (n+1);
    sum = sum/2;

    return sum;

}

long int norm_rect(int m,int n)
{
    long int sum=0;

    sum = Sum_N(m)*Sum_N(n);

}

long int hatch_rect(int m,int n)
{
    if(m<n)
    {
        m=m+n;
        n=m-n;
        m=m-n;
    }
    int i,j;
    long int sum = 0;
    int c1 = m-n;
    int c2 = 2*n -1;

    for(i=n; i>=2 ;i--)
    {
        for(j=i ; j>=1 ;j--)
        {
            sum += 4 * Sum_N(2*j - 2);
        }

    }

    for(i=1 ; i<= c2 ;i++)
    {
        if(i%2 == 0)
        {
            sum += (c1-1)*Sum_N(i);
        }

        if(i%2 == 1)
        {
            sum += c1*Sum_N(i);
        }

    }

return sum;
}

int main()
{
    long int sum=0;

    for(int i=1;i<=M;i++)
    {
        for(int j=1;j<=N;j++)
        {
            sum += hatch_rect(i,j) + norm_rect(i,j);
        }
    }

    cout<<sum<<endl;

    return 0;
}