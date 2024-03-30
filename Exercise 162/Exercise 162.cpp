#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
typedef __int64 int64;
struct timer
{
   double t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", get_time()); }
   double get_time() { return (clock()-t)/CLOCKS_PER_SEC; }
};
const int MAXDEPTH=16;
int m[MAXDEPTH] = {0};
int digits = MAXDEPTH;
int64 nt = 0;
int maxDepth;
void f162a(int64 tot, int depth=0)
{
   if (depth < maxDepth)
   {
      if (m[0x0] == 0 && depth < maxDepth-1) // 0
      {
         m[0x0] = 1;
         --digits;
         f162a(tot, depth+1);
         m[0x0] = 0;
         ++digits;
      }
      if (m[0x1] == 0) // 1
      {
         m[0x1] = 1;
         --digits;
         f162a(tot, depth+1);
         m[0x1] = 0;
         ++digits;
      }
      if (m[0xa] == 0) // A
      {
         m[0xa] = 1;
         --digits;
         f162a(tot, depth+1);
         m[0xa] = 0;
         ++digits;
      }
      int64 ntot = tot*digits;
      f162a(ntot, depth+1);
   }
   else if (digits == 13) // 0,1,A all used once
   {
      nt += tot;
   }
}
void f162()
{
   maxDepth = 2;
   while (++maxDepth <= MAXDEPTH)
      f162a(1);
   printf("nt=%I64X\n", nt);
}
int main(int ac, char** av)
{
   timer t;
   f162();
   return 0;
}