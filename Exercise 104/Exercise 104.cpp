#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;
long long mod=1000000000LL;
bool f(string s)
{
        //int i,j,k;
        if(s.size()<9)
        return(false);
        bool f_9[10];
        bool l_9[10];
        int i,j,k;
        memset(f_9,false,sizeof(f_9));
        for(i=0;i<9;i++)
        {
                j=s[i]-'0';
                f_9[j]=true;
        }
        for(i=1;i<=9;i++)
        if(!f_9[i])
        return(false);
        return(true);
}
bool l(string s)
{
        if(s.size()<9)
        return(false);
        bool f_9[10];
        bool l_9[10];
        int i,j,k;
        memset(l_9,false,sizeof(l_9));
        k=s.size()-1;
        for(i=0;i<9;i++,k--)
        {
                j=s[k]-'0';
                l_9[j]=true;
        }
        for(i=1;i<=9;i++)
        if(!l_9[i])
        return(false);
        return(true);
}
main()
{
	int i,j,k;
	long double phi=1.0+sqrtl(5.0),val,r_5=sqrtl(5.0);
	long long a=1,b=1,c,d;
	phi/=2.0;
	stringstream x;
	string s,tmp,t;
	bool fg1,fg2;
	for(i=3;;i++)
	{
		a%=mod;
		b%=mod;
		c=a+b;
		c%=mod;
		a=b;
		b=c;
		val=(long double)i*(log10l(phi))-0.5*log10l(5.0);
		j=(int)val;
		val=val-j;
		d=(long long)roundl(powl(10.0,val)*mod);
		x.clear();
		x<<c<<" "<<d;
		x>>tmp>>s;
		fg1=fg2=false;
		if(l(tmp))
		{
			fg1=true;
                }
                if(f(s))
                {
			fg2=true;
                }
		if(fg1 && fg2)
		{
			cout<<"\t"<<i<<"\n";
			break;
		}
	}
	cout<<"ans"<<"\t"<<i<<"\n";
	
}		
