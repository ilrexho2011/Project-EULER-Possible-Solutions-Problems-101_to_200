#include <iostream>
#include <math.h>

using namespace std;

void createTriangle();
void sumRows();
long long findLeastSum();
const int N=1000;
long long MAX=(long long)pow(10.0,18);
long long minSum(int r,int c);
int triangle[N][N];

int main(int argc, char *argv[])
{
    createTriangle();
    sumRows();
    printf ("Least sum: %ld\n", findLeastSum());
    system("PAUSE");
}

void createTriangle()
{
    int t=0;
    int r=0;
    int c=0;
    for(int k=0;k<500500;k++)
    {
        t=(615949*t + 797807)%1048576;
        triangle[r][c++]=t-524288;
        if(c>r)
        {
            c=0;
            r++;
        }
    }
}

void sumRows()
{
    for(int r=0;r<N;r++)
    {
        for(int c=1;c<=r;c++)
        {
            triangle[r][c]=triangle[r][c]+triangle[r][c-1];
        }
    }
}

long long findLeastSum()
{
    long long least=MAX;
    for(int r=0;r<N;r++)
    {
        for(int c=0;c<=r;c++)
        {
            long long min=minSum(r,c);
            if(min<least)
            {
                least=min;
            }
        }
    }
    return least;
}
long long minSum(int r, int c)
{
    long long min=triangle[r][c];
    if(c!=0)
    {
        min=min-triangle[r][c-1];
    }
    long long sum=min;
    for(int k=1;k<N-r;k++)
    {
        sum=sum+triangle[r+k][c+k];
        if(c!=0)
        {
            sum=sum-triangle[r+k][c-1];
        }
        if(sum<min)
        {
            min=sum;
        }
    }
    return min;
}