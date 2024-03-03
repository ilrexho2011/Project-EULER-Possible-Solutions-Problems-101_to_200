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

bool is_prime(int64 n) // for n>10 and odd
{
   int64 i=1, ii=1, j=1;
   while (i+=2, j+=2, ii+=j, ii<=n)
      if (!(n%i))
         return false;
   return true;
}
void f128()
{
   /*       d   c   b   a
   +1:   3  9  21  39  63  93
   +0:   2  8  20  38  62  92 ...
   -1:   1  7  19  37  61  91
   -2:      6  18  36  60  90
   */
   int nt=2;
   int64 a=20,b=8,c=2,d,i=12, found;
   while (i+=6, d=c, c=b, b=a, a+=i)
   {
      // For 20, check 61-20, 39-20, 37-20
      // For 37, check 37-20, 37-8, 60-37
      if (is_prime(b-c-1)) // 37-20
      {
         // 60-37 & 37-8
         if (is_prime(a-b-1) && is_prime(b-d-1))
            if (found=b-1, ++nt==2000)
               break;
         // 39-20 & 61-20
         if (is_prime(b-c+1) && is_prime(a-c-1))
            if (found=c, ++nt==2000)
               break;
      }
   }
   printf("%d -- %I64d\n",nt, found);
}

int main(int argc, char**argv)
{
   timer t;
   f128();
   return 0;
}