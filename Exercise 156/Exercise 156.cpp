#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <algorithm>
using namespace std;

typedef long long ll;

ll minti[10][100]={0}; // min f(n,d)-n over n = 0-10^i-1?
ll maxti[10][100]={0}; // max f(n,d)-n over n = 0-10^i-1?
ll difti[10][100]={0}; // dif f(n,d)   over n = 0-10^i-1?  a.k.a f(10^i-1,d)
ll s(int d, ll n=0, ll f=0, int i=0, ll ti=1, int bias=0) { // works for nonzero d
#ifdef TEST
  printf("s(d=%d, n=%lld, f=%lld, i=%d, ti=%lld, bias=%d)\n", d, n, f, i, ti, bias);
#endif
  if (i>10&&f>n)
    return 0;
  ll ans=0;
  if (n==ti-1) { // ==> bias=0, synthesis mode
    ll m=minti[d][i];
    ll M=maxti[d][i];
    for (int k=1; k<10; k++)
      if (k==d) {
	if (f-n<=0&&f-n+ti+maxti[d][i]>=0)
	  ans+=s(d,n,f,i-1,ti/10,1);
	n+=ti,f+=ti+difti[d][i],M=max(M,f);
      }
      else {
	if (f-n<=0&&f-n+maxti[d][i]>=0||f-n>=0&&f-n+minti[d][i]<=0)
	  ans+=s(d,n,f,i-1,ti/10,0);
	m=min(m,f-n+minti[d][i]),M=max(M,f-n+maxti[d][i]),n+=ti,f+=difti[d][i];
      }
    minti[d][i+1]=m;
    maxti[d][i+1]=M;
    difti[d][i+1]=f;
    return ans+s(d,n,f,i+1,ti*10,0);
  }

  if (i<0) {
#ifdef TEST
    if (f==n)
      printf("Found solution f(%lld,%d)=%lld\n", n, d, f);
#endif
    return (f==n?n:0);
  }
  for (int k=0; k<10; k++)
    if (bias||k==d) {
      int b=(k==d?bias+1:bias);
      if (f-n<=0&&f-n+ti*b+maxti[d][i]>=0)
	ans+=s(d,n,f,i-1,ti/10,b);
      n+=ti,f+=ti*b+difti[d][i];
    }
    else {
      if (f-n<=0&&f-n+maxti[d][i]>=0||f-n>=0&&f-n+minti[d][i]<=0)
	ans+=s(d,n,f,i-1,ti/10,0);
      n+=ti,f+=difti[d][i];
    }
  return ans;
}

int main(int argc, char* argv[]) {
  ll ans=0;
  for (int d=1; d<=9; d++)
    ans+=s(d);
  printf("%lld\n", ans);
}