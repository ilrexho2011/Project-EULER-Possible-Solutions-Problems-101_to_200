#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>

enum{PHI10=4,PHI10_2=40,PHI10_8=40000000};
typedef unsigned int uint;
typedef __int64 bigint;
void fx(uint n, uint hypex)
{
   int ix = 1;
   bigint next = n;
   while (ix < hypex)
   {
      bigint nn = 1;
      int ixx = 0;
      while (ixx < next)
      {
         nn = nn * n;
         nn = nn % PHI10_8;
         ++ixx;
      }
      next = nn; // you get the same value always after a few runs
      ++ix;
   }
   printf("next=%I64d\n", next);
   bigint res = 1;
   ix = 0;
   while (ix < next)
   {
      res = res * n;
      res = res % 100000000;
      ++ix;
   }
   printf("res=%I64d\n", res);
}

int main(int argc, char**argv)
{
   fx(1777,1855);
   return 0;
}