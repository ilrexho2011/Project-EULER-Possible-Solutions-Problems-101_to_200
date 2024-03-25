#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef long long ll;
typedef long double ld;

class xcollection {
public:
  int n;
  ld* x;
  xcollection() {n=nx=0;}// nx=2; x=new ld[nx];}
  ~xcollection() {delete [] x;}
  void add(ld newx) {
    if (n==nx) {
      ld* xx=new ld[nx?nx*=2:nx=2];
      memcpy(xx,x,n*sizeof(ld));
      if (n)
	delete [] x;
      x=xx;
    }
    x[n++]=newx;
  }
private:
  int nx;
};

ld x[1000], sMin[1000];
xcollection *psa, *psb;
ll xm[1000], xm1[1000], xm2[1000], ki[1000], d[1000];
const ld eps=1e-10, goalMin=.5L-eps, goalMax=.5L+eps;

const ll mod=100003;//10007;//9999991;
//const ll mod=9999991;
ll powMod(ll b, ll e, ll mod=mod) {
  ll ans = 1;
  b%=mod;
  while (e) {
    if (e%2)
      ans=ans*b%mod;
    if (e/=2)
      b=b*b%mod;
  }
  return ans;
}

ll invMod(ll x, ll mod=mod) {
  return powMod(x, mod-2, mod);
}
#define invMod1(x) (invMod(x,mod1))
#define invMod2(x) (invMod(x,mod2))

ll invModP2(ll x, ll p) {
  ll imp=invMod(x,p);
  for (ll ans=imp; ; ans+=imp)
    if (ans*x%(p*p)==1)
      return ans;
}

ll countSumsA(ll nvx, int idx=0, ld psum=0.L, ll psm=0) {
  if (goalMin<=psum) {
    if (psm*2%mod!=1)
      return 0;
    return 1;
  }
  if (psum>=sMin[nvx])
    //printf("%lld,",psm),psa[psm].add(psum);
    psa[psm].add(psum);
  ll ans=0;
  for (int i=idx; i<nvx&&psum>=sMin[i]; i++)
    if (psum+x[i]<=goalMax)
      ans+=countSumsA(nvx,i+1,psum+x[i],(psm+xm[ki[i]])%mod);
  return ans;
}

void countSumsB(ll nvx, int idx, ld psum=0.L, ll psm=0) {
  //printf("%lld,",psm),psb[psm].add(psum);
  psb[psm].add(psum);
  for (int i=idx; i<nvx; i++)
    countSumsB(nvx,i+1,psum+x[i],(psm+xm[ki[i]])%mod);
}

ll *pMin;

int ipx2[1000], npx;
ld xpx[1000],sxpx;
ll xmpx[1000],sxmpx;
int countSol(ll n, const int p2, int idx=0, int psm=0, ld psum=0.L, ll psxm=0) {
  if (idx&&!psm) {
    //printf("Found solution modulo %d ending with %.10Lf\n", p2, xpx[idx-1]);
    sxpx=psum,sxmpx=psxm;
    return 1;
  }
  int ans=0;
  for (int i=idx; i<npx; i++)
    ans+=countSol(n,p2,i+1,(psm+ipx2[i])%p2,psum+xpx[i],(psxm+xmpx[i])%mod);
  return ans;
}

bool valid(ll n, ll k) {
  ll kk=k;
  for (ll p=pMin[kk],px; kk>1; p=pMin[kk]) {
    for (px=1; kk%p==0; kk/=p,px*=p);
    if (p==2&&px*7>n || p==3&&px*4>n || p%4==1&&px*2>n || p%4==3&&px*3>n)
      return false;
    if (k>px && (p==2&&px*9>n || p==3&&px*5>n || p%4==1&&px*3>n || p%4==3&&px*4>n))
      return false;
    if (px*p<=n&&valid(n,px*p))
      continue;
    const int p2=p*p;
    npx=0;
    for (int r=1,rpx=px; rpx<=n; r++,rpx+=px)
      if (r%p)
	xpx[npx]=1.L/(ld)(rpx*rpx),xmpx[npx]=(invMod(rpx)*invMod(rpx))%mod,ipx2[npx++]=(invModP2(r,p)*invModP2(r,p))%p2;
    if (npx>15)
      continue;
    int nsol=countSol(n,p2);
    if (nsol==0||nsol==1&&k>px)
      return false;
  }
  return true;
}

ld weight(ll n, ll k) { // assumes valid
  ll kk=k;
  for (ll p=pMin[kk],px; kk>1; p=pMin[kk]) {
    for (px=1; kk%p==0; kk/=p,px*=p);
    if (k==px) {
      if (p==2&&px*9>n) {
	xm[k]=(invMod(k)*invMod(k)%mod+invMod(3*k)*invMod(3*k)%mod+invMod(5*k)*invMod(5*k)%mod+invMod(7*k)*invMod(7*k)%mod)%mod;
	return 1.L/(ld)(k*k)+1.L/(ld)(9*k*k)+1.L/(ld)(25*k*k)+1.L/(ld)(49*k*k);
      }
      if (p==3&&px*5>n) {
	xm[k]=(invMod(k)*invMod(k)%mod+invMod(2*k)*invMod(2*k)%mod+invMod(4*k)*invMod(4*k)%mod)%mod;
	return 1.L/(ld)(k*k)+1.L/(ld)(4*k*k)+1.L/(ld)(16*k*k);
      }
      if (p%4==1&&px*3>n) {
	xm[k]=(invMod(k)*invMod(k)%mod+invMod(2*k)*invMod(2*k)%mod)%mod;
	return 1.L/(ld)(k*k)+1.L/(ld)(4*k*k);
      }
      if (p%4==3&&px*4>n) {
	xm[k]=(invMod(k)*invMod(k)%mod+invMod(2*k)*invMod(2*k)%mod+invMod(3*k)*invMod(3*k)%mod)%mod;
	return 1.L/(ld)(k*k)+1.L/(ld)(4*k*k)+1.L/(ld)(9*k*k);
      }
      if (px*p<=n&&valid(n,px*p))
	continue;
      const int p2=p*p;
      npx=0;
      for (int r=1,rpx=px; rpx<=n; r++,rpx+=px)
	if (r%p)
	  xpx[npx]=1.L/(ld)(rpx*rpx),xmpx[npx]=(invMod(rpx)*invMod(rpx))%mod,ipx2[npx++]=(invModP2(r,p)*invModP2(r,p))%p2;
      if (npx>15)
	continue;
      int nsol=countSol(n,p2);
      if (nsol==1) {
	xm[k]=sxmpx;
	return sxpx;
      }
    }
  }
  xm[k]=invMod(k)*invMod(k)%mod;
  return 1.L/(ld)(k*k);
}

int main(int argc, char* argv[]) {
  if (argc<2) {
    printf("Usage:  %s <natural number> <natural number>\n", argv[0]);
    exit(1);
  }
  ll N = strtoll(argv[1], NULL, 10);
  int shift=argc<3?3:atoi(argv[2]);

  ll nSieve=N+1;
  pMin=new ll[nSieve];
  for (ll i=0; i<nSieve; i++)
    pMin[i]=0;
  for (ll p=2; p<nSieve; p++)
    if (!pMin[p])
      for (ll kp=p; kp<nSieve; kp+=p)
	if (!pMin[kp])
	  pMin[kp]=p;

  ll nvx=0;
  for (ll i=2; i<=N; i++)
    if (valid(N,i))
      ki[nvx]=i,x[nvx++]=weight(N,i);

  ld sm=.5L;
  for (int i=nvx-1; i>=0; i--)
    sm-=x[i],sMin[i]=sm-eps;

  psa=new xcollection[mod];
  psb=new xcollection[mod];
  ll nvxa=nvx/2+shift; nvxa=(nvxa<nvx?nvxa:nvx);
  ll ans=countSumsA(nvxa);
  if (nvxa<nvx) {
    printf("psa final, processed first %lld of %lld chunks, next is %lld\nSo far: %lld solution(s)\n", nvxa, nvx, ki[nvxa], ans);
    countSumsB(nvx,nvxa);
    printf("psb final, combining partial sums...\n");
    const ll hm=mod/2+1;
    for (ll i=0; i<=hm; i++)
      if (psa[i].n&&psb[hm-i].n)
	for (int a=0; a<psa[i].n; a++)
	  for (int b=0; b<psb[hm-i].n; b++)
	    if (goalMin<=psa[i].x[a]+psb[hm-i].x[b]&&psa[i].x[a]+psb[hm-i].x[b]<=goalMax)
	      ans++;
    for (ll i=hm+1; i<mod; i++)
      if (psa[i].n&&psb[hm-i+mod].n)
	for (int a=0; a<psa[i].n; a++)
	  for (int b=0; b<psb[hm-i+mod].n; b++)
	    if (goalMin<=psa[i].x[a]+psb[hm-i+mod].x[b]&&psa[i].x[a]+psb[hm-i+mod].x[b]<=goalMax)
	      ans++;
  }
  printf("%lld\n", ans);
}