#include<stdio.h>
#define M 100000
#define N 1000000000
int p[M]={0};
void prime()
 {
  long i,j;
  p[0]=1; p[1]=1;
  for(i=2;i*i<=M;i++)
   if(p[i]==0)
   for(j=2;i*j<M;j++)
   p[i*j]=1;
   }

int main()
 {
  long s=0;
  long n,k,r=0;
  prime();
  for(n=3;n<=M;)
  {
    if(p[n]==0)
     {
      r=0;
      for(k=1;k<N;k++)
       {
	r=(r*10+1)%n;
	if(r==0)
	break;
	}
      for(;k%5==0 && k!=0;)
       k/=5;

      for(;k%2==0 && k!=0;)
       k/=2;

      if(k==1 || k==0)
      {
      printf("\n%ld",n);
      p[n]=1;
      }
      }



    if(n%10==1 || n%10==7 || n%10==9)
    n+=2;
    else
    n+=4;
    }
   for(n=2;n<M;n++)
   if(p[n]==0)
   s+=n;

   printf("Sum is : %ld",s);
   getchar();
   return 0;
   }