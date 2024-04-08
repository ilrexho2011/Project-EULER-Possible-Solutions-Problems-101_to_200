#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>

typedef __int64 int64;
struct timer
{
   double t;
   timer() { t=clock(); }
   ~timer() { printf("runtime %.3f secs\n", (clock()-t)/CLOCKS_PER_SEC); }
};

namespace p178
{
   const int MD=40, NS=40;
   int64 memo[MD+1][NS]={0};
   typedef int64 (*func)(const int, const int, const int, const int);
   int64 memocall(func f, const int a, const int b, const int c, const int d)
   {
      int s=4*b+2*c+d; //state
      if (memo[a][s]==0)
         memo[a][s]=f(a,b,c,d);
      return memo[a][s];
   }
   int64 f178(const int depth, const int digit, const int minseen, const int maxseen)
   {
      int64 n=minseen!=0 && maxseen!=0;
      if (digit<9 && depth+1<MD)
         n+=memocall(f178, depth+1, digit+1, minseen, (digit+1)==9?1:maxseen);
      if (digit>0 && depth+1<MD)
         n+=memocall(f178, depth+1, digit-1, (digit-1)==0?1:minseen, maxseen);
      return n;
   }
   void f178()
   {
      int64 nt=0;
      int i=10;
      while (--i>0)
         nt+=f178(0,i,0,i==9);
      printf("nt=%I64d\n",nt);
   }
}
int main(int argc, char**argv)
{
   timer t;
   p178::f178();
   return 0;
}