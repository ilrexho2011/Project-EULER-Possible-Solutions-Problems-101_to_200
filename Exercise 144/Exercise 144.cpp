#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct timer
{
   double t;
   timer() { t=clock(); }
   ~timer() { printf("runtime %.3f secs\n", (clock()-t)/CLOCKS_PER_SEC); }
};

namespace p144
{
   /*
   if a=slope of tangent line and
   b,c=slopes of incident and reflected lines:
   tan(x)=tan(180-x) -> (a-b)/(1+ab)=-(a-c)/(1+ac)
   c=(b*(a*a-1)+2*a)/(1+2*a*b-a*a)
   */
   double next_slope(double a, double b)
   {
      double aa=a*a;
      return (b*(aa-1)+2*a)/(1+2*a*b-aa);
   }
   struct xy
   {
      double x,y;
      xy(double x, double y){this->x=x, this->y=y;}
   };
   /*
   if y=mx+n line crosses 4x^2+y^2=100 at 2 points (a,b) and (c,d)
   4*a*a+b*b=100               b=m*a+n
   4*c*c+d*d=100               d=m*c+n
   ---------------------       ---------------
   4*(a*a-c*c)+b*b-d*d=0 (1)   b-d=m*(a-c) -> d=b-m*(a-c) (2)
   combine (1) and (2) and eliminate d, find c
   (m^2+4)*c^2 + (2*b*m-2*a*m)*c +a*a*m*m-2*a*b*m-4*a*a=0
   dis=(8a+2bm)^2
   c_1=a
   c_2=((m^2-4)*a-2*b*m)/(m^2+4) -> d=(-8*m*a+b*(4-m^2))/(m^2+4)
   */
   xy next_point(const xy& p, double m)
   {
      double mm=m*m;
      double x=((mm-4)*p.x-2*m*p.y) / (mm+4);
      double y=(-8*m*p.x+(4-mm)*p.y) / (mm+4);
      return xy(x,y);
   }
   void f144()
   {
      int i=1;
      xy a(0,10.1), b(1.4,-9.6);
      while (1)
      {
         double m=next_slope(b.y/(4*b.x), (b.y-a.y)/(b.x-a.x));
         a=b, b=next_point(b,m);
         if (b.x>=-0.01 && b.x<=0.01 && b.y>0)
            break;
         ++i;
      }
      printf("%d\n",i);
   }
}

int main(int argc, char**argv)
{
   timer t;
   p144::f144();
   return 0;
}