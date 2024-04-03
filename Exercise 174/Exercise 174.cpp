#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>

typedef __int64 int64;
typedef unsigned int uint;
typedef unsigned char uint8;
struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};

void fx()
{
   const int N = 1000000;
   uint8* pi = new uint8 [N+1];
   memset(pi,0,(N+1)*sizeof(uint8));
   int i = 0, j = 0, k = -1;
   while (j+=++k, ++i)
   {
      int a = i << 2;
      int b = (j << 3) + a;
      if (a+b > N)
         break;
      int ix = b;
      while (ix += a, ix < N)
         ++ pi[ix];
   }
   int sum = 0;
   i = 0;
   int t[100] = {0};
   while (++i < N)
      ++ t[pi[i]-1];
   printf("sum=%d\n", t[0]+t[1]+t[2]+t[3]+t[4]+t[5]+t[6]+t[7]+t[8]+t[9]);
   delete [] pi;
}

int main(int ac, char** av)
{
   timer t;
   fx();
   return 0;
}