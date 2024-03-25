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
#include <numeric>

typedef short int16;

struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};

struct pq
{
   int16 p, q;
   pq(int p, int q=1) { this->p=p, this->q=q; }
   pq(const pq& r) { this->p=r.p, this->q=r.q; }
   const bool operator< (const pq& r) const
   { return (int)this->p*r.q<(int)this->q*r.p; }
};
struct less_by_ppq : public std::binary_function<pq*, pq*, bool> 
{
   less_by_ppq() {}
   bool operator()(const pq* p1, const pq* p2) const
   { return *p1<*p2; }
};
void f155()
{
   const int MD=18;
   std::vector<pq> av[MD];
   std::set<const pq*, less_by_ppq> ppqs;
   av[0].push_back(pq(1));
   ppqs.insert( &av[0].back() );
   int depth=1;
   while (++depth<=MD)
   {
      int nt=av[depth-2].size();
      av[depth-1].reserve(nt*3);
      const pq* ppq=&av[depth-2].front();
      int i=-1;
      while (++i<nt)
      {
         int p=ppq[i].p, q=ppq[i].q; // p>q
         av[depth-1].push_back(pq(p+q,q));
         if (ppqs.insert( &av[depth-1].back() ).second==false)
            av[depth-1].pop_back();
         av[depth-1].push_back(pq(p+q,p));
         if (ppqs.insert( &av[depth-1].back() ).second==false)
            av[depth-1].pop_back();
      }
      if (depth>4)
      {
         int i=1, j=depth-i;
         while (++i<=--j)
         {
            int nti=av[i-1].size(), ntj=av[j-1].size();
            const pq* ppqi=&av[i-1].front();
            const pq* ppqj=&av[j-1].front();
            int ii=-1;
            while (++ii<nti)
            {
               int ij=-1, ip=ppqi[ii].p, iq=ppqi[ii].q;
               while (++ij<ntj)
               {
                  int jp=ppqj[ij].p, jq=ppqj[ij].q;
                  int p=ip*jp+iq*jq, q=iq*jp;
                  av[depth-1].push_back(p>q?pq(p,q):pq(q,p));
                  if (ppqs.insert( &av[depth-1].back() ).second==false)
                     av[depth-1].pop_back();
                  q=ip*jq;
                  av[depth-1].push_back(p>q?pq(p,q):pq(q,p));
                  if (ppqs.insert( &av[depth-1].back() ).second==false)
                     av[depth-1].pop_back();
                  p=ip*jp, q=ip*jq+iq*jp;
                  av[depth-1].push_back(p>q?pq(p,q):pq(q,p));
                  if (ppqs.insert( &av[depth-1].back() ).second==false)
                     av[depth-1].pop_back();
                  p=iq*jq;
                  av[depth-1].push_back(p>q?pq(p,q):pq(q,p));
                  if (ppqs.insert( &av[depth-1].back() ).second==false)
                     av[depth-1].pop_back();
               }
            }
         }
      }
      printf("%d -- %d\n", depth, 2*ppqs.size()-1);
   }
}
int main(int argc, char**argv)
{
   timer t;
   f155();
   return 0;
}