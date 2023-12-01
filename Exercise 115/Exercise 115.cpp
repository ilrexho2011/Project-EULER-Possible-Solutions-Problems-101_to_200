#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>

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
int a[]={2,3,5,7,11,13,17};
enum { T=17*17+1, NP=7 };
struct p : std::pair< std::vector<int>, std::vector<int> >
{
   p()
   {
      this->first.reserve(T+1);
      memset(this->first.begin(),0,sizeof(int)*(T+1));
      this->second.reserve(T+1);
      memset(this->second.begin(),0,sizeof(int)*(T+1));
   }
   p(int first, int second)
   {
      this->first.reserve(T+1);
      memset(this->first.begin(),0,sizeof(int)*(T+1));
      this->second.reserve(T+1);
      memset(this->second.begin(),0,sizeof(int)*(T+1));
      add_pair(first, second);
   }
   void add_pair(int first, int second)
   {
      int i = -1;
      while (first > 1 && ++i < NP)
      {
         while (!(first % a[i]))
            ++ this->first[a[i]], first /= a[i];
      }
      ++ this->first[first];
      i = -1;
      while (second > 1 && ++i < NP)
      {
         while (!(second % a[i]))
            ++ this->second[a[i]], second /= a[i];
      }
      ++ this->second[second];
   }
   operator int64 ()
   {
      int* p1 = this->first.begin();
      int* p2 = this->second.begin();
      int i = 1;
      while (++i <= T)
      {
         if (p1[i] > p2[i])
            p1[i] -= p2[i], p2[i] = 0;
         else if (p1[i] < p2[i])
            p2[i] -= p1[i], p1[i] = 0;
         else
            p1[i] = 0, p2[i] = 0;
      }
      i = 1;
      int64 n1 = 1, n2 = 1;
      double d = 1;
      while (++i <= T)
      {
         int j = p1[i];
         while (j-- > 0)
            n1 *= i;
         j = p2[i];
         while (j-- > 0)
            n2 *= i;
      }
      return n1 / n2;
   }
};


int64 fz(int x, int y) //x>=y
{
   p px;
   int i = y;
   while (++i <= x)
      px.add_pair(i,0);
   i = 0;
   x -= y;
   while (++i <= x)
      px.add_pair(0,i);
   return px;
}
int64 fy(int x, int y)
{
   int64 xy = (x+1) / (y+1);
   int64 ways = 0, a = -1, t = x+y+1;
   while (t -= y, ++a <= xy)
      ways += fz(t+a, t-a);
   return ways;
}
void fx()
{
   int i = 49;
   while (++i)
   {
      if ( fy(i,50) > 1000000)
         break;
   }
   printf("i=%d\n", i);
}

int main(int ac, char** av)
{
   timer t;
   fx();
   return 0;
}