#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <set>
typedef __int64 myint;
enum{N=100000000};
int is_pal(int n)
{
   char a[16];
   itoa(n,a,10);
   int ix=0, ixx=strlen(a)-1-ix;
   while (ix<ixx && a[ix]==a[ixx])
      ++ix, --ixx;
   return ix>=ixx;
}
int main(int argc, char**argv)
{
   myint sum=0;
   std::set<int> objNums;
   int i=0;
   while (++i)
   {
      int ii=i*i;
      if ( ii >= N )
         break;
      int j=i;
      while (++j, (ii+=j*j) < N)
         if ( is_pal(ii) && objNums.insert(ii).second)
               sum+=ii;
   }
   printf("sum=%I64d\n", sum);
   return 0;
}