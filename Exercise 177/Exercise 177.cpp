#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define EPS 1e-8
typedef long long ll;
double d2r,r2d;
int equal(double a,double b) {
  return fabs(a-b)<EPS;
}
/*  only check infinite lines, not segments */
/* 0: lines don't intersect, 1:lines intersect, 2:lines are collinear */
int linesintersect(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,
  double *x,double *y) {
  double a1,a2,b1,b2,c1,c2,denom,num;
  a1=y2-y1; b1=x1-x2; c1=x2*y1-x1*y2;
  a2=y4-y3; b2=x3-x4; c2=x4*y3-x3*y4;
  denom=a1*b2-a2*b1;
  if(equal(denom,0)) return 2;
  num=b1*c2-b2*c1;
  *x=num/denom;
  num=a2*c1-a1*c2;
  *y=num/denom;
  return 1;
}
int isinteger(double v) {
  return fabs(round(v)-v)<EPS;
}
double adjust(double a) {
  while(a<0) a+=360;
  while(a>=360) a-=360;
  return a;
}
/*  symmetry classes*/
ll res0=0;    /*  no operation (all) */
ll res1=0;    /*  rot 90, 270 */
ll res2=0;    /*  rot 180 */
ll res3=0;    /*  flip along vertical axis */
ll res4=0;    /*  flip along horizontal axis */
ll res5=0;    /*  flip AC diag */
ll res6=0;    /*  flip BD diag */

/*  parameters: angles A,B,C as well as the angle BAC, giving the direction of the diagonal
    AC. these will uniquely determine the polygon */
void solve(int A,int B,int C,int upperA) {
  double x[4],y[4],xx,yy,tABD;
  int res,DAC=A-upperA,BAC=upperA,ABD,CBD,BCA,DCA,CDB,ADB,D=360-A-B-C;
  /*  A=(0,0) B=(1,0), polygon is ABCD clockwise */
  x[0]=0; y[0]=0;
  x[1]=1; y[1]=0;
  /*  - find another point on the line AC (use angle upperA)
      - find another point on the line BC (use angle C)
      - find the intersection of the lines: this is point C
  */
  res=linesintersect(x[0],y[0],x[0]+cos(upperA*d2r),y[0]+sin(upperA*d2r),
    x[1],y[1],x[1]+cos((180-B)*d2r),y[1]+sin((180-B)*d2r),&xx,&yy);
  if(res!=1) return;
  x[2]=xx; y[2]=yy;
  /*  - find another point on the line AD (use angle A)
      - find another point on the line CD (use angle B+C)
      - find the intersection of the lines: this is point D
  */
  res=linesintersect(x[0],y[0],x[0]+cos(A*d2r),y[0]+sin(A*d2r),
    x[2],y[2],x[2]+cos((180-B-C)*d2r),y[2]+sin((180-B-C)*d2r),&xx,&yy);
  if(res!=1) return;
  x[3]=xx; y[3]=yy;
  /*  it suffices to check if any integral rotation of ABD is integral */
  tABD=adjust(180-atan2(y[3]-y[1],x[3]-x[1])*r2d);
  if(!isinteger(tABD)) return;
  if(tABD>179) return;
  /*  we know A, ABD: calculate ADB */
  ABD=(int)(tABD+EPS);
  ADB=180-A-ABD;
  CDB=D-ADB;
  DCA=180-DAC-D;
  BCA=C-DCA;
  CBD=180-CDB-C;
  /*  res0: all */
  res0++;
  /*  res1: rot90 and rot270 */
  if(A==B && B==C && C==D && BAC==CBD && CBD==DCA && DCA==ADB) res1++;
  /*  res2: rot180 */
  if(A==C && B==D && BAC==DCA && CBD==ADB) res2++;
  /*  res3: flip ver */
  if(A==B && D==C && BAC==ABD && ADB==BCA) res3++;
  /*  res4: flip hor */
  if(A==D && B==C && BAC==CDB && ABD==DCA) res4++;
  /*  res5: flip diag AC */
  if(D==B && BAC==DAC && BCA==DCA && CDB==CBD) res5++;
  /*  res6: flip diag BD */
  if(A==C && DAC==DCA && BAC==BCA && CDB==ADB && ABD==CBD) res6++;
  return;
}
int main() {
  int A,B,C,D,upperA;
  ll ans=0;
  d2r=2*acos(0)/180;
  r2d=180/(2*acos(0));
  for(A=1;A<180;A++) for(B=1;B<180;B++) for(C=1;C<180;C++) {
    D=360-A-B-C;
    /*  enforce last angle 0<D<180 */
    if(D<1) continue;
    if(D>179) continue;
    for(upperA=1;upperA<A;upperA++) {
      /*  make sure triangle ABC is legal: A+B<180 */
      if(upperA+B>179) break;
      /*  also, C-BCA must be >0 */
      if(180-upperA-B>=C) continue;
      solve(A,B,C,upperA);
    }
  }
  printf("%I64d %I64d %I64d %I64d %I64d %I64d %I64d\n",res0,res1,res2,res3,res4,res5,res6);
  ans=(res0+2*res1+res2+res3+res4+res5+res6)/8;
  printf("ans = %I64d\n",ans);
  return 0;
}
