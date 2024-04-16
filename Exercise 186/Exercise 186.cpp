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

struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};

typedef std::vector<int> friends;
typedef std::vector<friends*> group_of_friends;
#define N(i) a[(i)&63]
void f186t(friends** ppf, int caller, int called)
{
   if (ppf[caller]==0)
   {
      if (ppf[called]==0)
      {
         ppf[called]=ppf[caller]=new friends;
         ppf[caller]->push_back(caller);
         ppf[called]->push_back(called);
      }
      else
      {
         ppf[caller]=ppf[called];
         ppf[caller]->push_back(caller);
      }
   }
   else
   {
      if (ppf[called]==0)
      {
         ppf[called]=ppf[caller];
         ppf[called]->push_back(called);
      }
      else if (ppf[caller]!=ppf[called])
      {
         int caller_size=ppf[caller]->size();
         int called_size=ppf[called]->size();
         if (caller_size>called_size)
         {
            friends* pf=ppf[called];
            friends::iterator called_it=pf->begin();
            while (called_it!=pf->end())
            {
               int called=*called_it++;
               ppf[called]=ppf[caller];
               ppf[called]->push_back(called);
            }
            delete pf;
         }
         else
         {
            friends* pf=ppf[caller];
            friends::iterator caller_it=pf->begin();
            while (caller_it!=pf->end())
            {
               int caller=*caller_it++;
               ppf[caller]=ppf[called];
               ppf[caller]->push_back(caller);
            }
            delete pf;
         }
      }
   }
}

void f186()
{
   const int USERS=1000000;
   const int PM=524287;
   const int TARGET=990000;
   int a[64];
   group_of_friends group_of_friends_obj;
   group_of_friends_obj.resize(USERS,0);
   friends** ppf=&group_of_friends_obj.front();
   int k=0;
   int calls=0;
   while (++k<=55)
   {
      int64 t=100003+k*((int64)300007*k*k-200003);
      a[k]=t%USERS;
      if (!(k&1))
      {
         int caller=a[k-1];
         int called=a[k];
         ppf[called]=ppf[caller]=new friends;
         ppf[caller]->push_back(caller);
         ppf[called]->push_back(called);
         ++calls;
      }
   }
   {
      int caller=a[55];
      int called=N(k)=(N(k-24)+N(k-55))%USERS;
      ++k;
      if (caller!=called)
      {
         ++calls;
         f186t(ppf,caller,called);
      }
   }
   while (1)
   {
      int caller=N(k)=(N(k-24)+N(k-55))%USERS;
      ++k;
      int called=N(k)=(N(k-24)+N(k-55))%USERS;
      ++k;
      if (caller==called)
         continue;
      f186t(ppf,caller,called);
      ++calls;
      if (ppf[PM]!=0 && ppf[PM]->size()==TARGET)
         break;
   }
   printf("calls=%d\n",calls);
   std::sort(group_of_friends_obj.begin(), group_of_friends_obj.end());
   group_of_friends_obj.erase(
      std::unique(group_of_friends_obj.begin(), group_of_friends_obj.end()),
      group_of_friends_obj.end()
   );
   int i=-1;
   int nt=group_of_friends_obj.size();
   while (++i<nt)
      delete ppf[i];
}
int main(int argc, char**argv)
{
   timer t;
   f186();
   return 0;
}