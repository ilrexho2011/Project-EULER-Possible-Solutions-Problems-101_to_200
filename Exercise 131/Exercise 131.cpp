#include<stdio.h>
const int MAX=1000005;
bool isp[MAX]={0};
bool vail[MAX]={0};
int sum[MAX]={0};
int main()
{
    int i,j,n;
    isp[0]=isp[1]=1;
    for(i=2;i*i<MAX;i++)
        if(!isp[i])
            for(j=i*i;j<MAX;j+=i)
                isp[j]=1;
    for(i=1;i<MAX;i++)
    {
        j=(i+1)*(i+1)*(i+1)-i*i*i;
        if(j>=MAX)
            break;
        vail[j]=1;
    }
    for(i=2;i<MAX;i++)
        sum[i]=sum[i-1]+(!isp[i]&&vail[i]);
    while(scanf("%d",&n)!=EOF)
    {
        if(sum[n])
            printf("%d\n",sum[n]);
        else
            puts("No Special Prime!");
    }
    return 0;
}