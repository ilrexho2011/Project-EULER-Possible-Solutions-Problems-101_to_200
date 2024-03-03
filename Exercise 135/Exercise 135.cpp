#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>
 
typedef __int64 int64;
typedef unsigned char uint8;
struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};
 
//enum{N=100};
//enum{N=50000000};
enum{N=1000000};
enum{N4=N/4};
/*
x = z+2a
y = z+a
zz-2az-3aa+n=0
dis=4(4aa-n)
dis=d^2
z1,2 = a +/- d
*/
void fx()
{
   uint8* pn = new uint8 [N];
   memset(pn, 0, N*sizeof(uint8));
   int a = 0;
   while (++a < N4)
   {
      int a2 = a << 1, d = a2, n;
      while (--d, n = (a2 - d)*(a2 + d), d > 0 && n < N)
      {
         ++ pn[n]; // z1= a+d
         if (d < a)
            ++ pn[n]; // z2 = a-d
      }
      if (n < N && d == 0)
         ++ pn[n]; // z1 = a+0 = a
   }
   int sum = 0, i = 0;
   while (++i < N)
      sum += pn[i] == 10;
   printf("sum=%d\n", sum);
   delete [] pn;
}
 
int main(int ac, char** av)
{
   timer t;
   fx();
   return 0;
}