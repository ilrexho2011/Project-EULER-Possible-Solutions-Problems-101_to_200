#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
typedef long long ll;
ll _pow(ll a,ll b,ll c)
	{
		ll ret=1;
		while(b)
		{
			if(b&1) ret=(ret*a)%c;
			a=(a*a)%c;
			b/=2;
		}
		return ret%c;
	}

ll geosum(ll a,ll n,ll c)
	{
		if(n==1LL) return 1LL;
		if(n==2LL) return (1LL+a)%c;
		int ret;
		ret=((geosum(a,n/2LL,c)%c)*((1LL+_pow(a,n/2LL,c))%c))%c; 
		if(n&1LL) ret=(ret+_pow(a,n-1LL,c))%c;

		return ret;
	}


bool isprime(ll n)
	{
		
		if(n==2LL) return 1;
		if(n<=1LL || n%2LL==0LL) return 0;
		for(ll i=3LL;i*i<=n;i+=2LL) if(n%i==0LL) return 0;
		return 1;
	}


int main()
	{

		long long sum=0;
		ll cnt=0LL;
		for(ll i=3LL;;i+=2LL)
		{
			if(isprime(i) && !geosum(10LL,(ll)pow(10,9),i)) 
			{
				cnt++;
				cout<<cnt<<" "<<i<<" divides it "<<endl;
				sum+=(long long) i;
				if(cnt==40LL) break;
			}
		}
		cout<<sum<<endl;
	}