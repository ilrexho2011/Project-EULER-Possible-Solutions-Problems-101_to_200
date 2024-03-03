#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>

typedef unsigned char uint8;
struct timer
{
   double t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", get_time()); }
   double get_time() { return (clock()-t)/CLOCKS_PER_SEC; }
};

/*
x = z+2a
y = z+a
zz-2az-3aa+n=0
dis=4(4aa-n)
dis=(2d)^2 -> z1=a+d z2=a-d (a>d)
*/
void f136()
{
   const int N=50000000, N4=N/4;
   uint8* pn = new uint8 [N];
   memset(pn, 0, N*sizeof(uint8));
   int a = 0;
   while (++a < N4)
   {
      int a2 = a << 1, d = a2, n;
      while (--d, n = (a2 - d)*(a2 + d), d > 0 && n < N)
      {
         ++ pn[n]; // z1= a+d
         pn[n] += d < a; // z2 = a-d
      }
      if (n < N && d == 0)
         ++ pn[n]; // z1 = a+0 = a
   }
   int sum = 0, i = 0;
   while (++i < N)
      sum += pn[i] == 1;
   printf("sum=%d\n", sum);
   delete [] pn;
}

int main(int ac, char** av)
{
   timer t;
   f136();
   return 0;
}