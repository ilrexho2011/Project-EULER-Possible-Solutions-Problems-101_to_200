#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>

typedef __int64 int64;
struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};

void f169()
{
   const int N=128;
   int a[N]={0}; // buffer for the bits of the binary number
   int i=N-25; // 25 zeros for 2^25
   int64 n=298023223876953125; //5^25
   while (a[--i]=n&1, n>>=1, n>0)
      ;
   int64 p=1, q=1;
   while (++i<N)
   {
      if (a[i])
         q+=p;
      else
         p+=q;
   }
   printf("p=%I64d\n", p);
}
int main(int argc, char**argv)
{
   timer t;
   f169();
   return 0;
}