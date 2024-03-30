#include <iostream>
using namespace std;

const int MOD=1e5;
long long ansM;
#define int long long

void calc()
{
  ansM=1;
  int del2=MOD/5;
  for(int i=1;i<=MOD;++i)
    if(i%5==0) continue;
    else
      {
	int cp=i;
	while(cp%2==0 and del2!=0)
	  {cp/=2; del2--;}
	ansM*=cp;
	ansM%=MOD;
      }
}

int ans(long long n)
{
  if(n<=10)
    {
      long long ans=1;
      for(int i=1;i<=n;++i)
	ans*=i;
      while(ans%10==0)
	ans/=10;
      return ans%MOD;
    }
  long long ret=ans(n/5);
  for(int i=1;i<=n/MOD;i++)
    {ret*=ansM; ret%=MOD;}
  long long start=(n/MOD)*MOD+1;
  long long rem2=(n-start+1)/5;
  for(long long i=start;i<=n;++i)
    if(i%5==0) continue;
    else
      {
	int cp=i;
	while(cp%2==0 and rem2!=0)
	  {cp/=2; rem2--;}
	ret*=cp;
	ret%=MOD;
      }
  return ret;
}

main()
{
  calc();
  long long n;
  cin>>n;
  cout<<ans(n)<<endl;
  return 0;
}