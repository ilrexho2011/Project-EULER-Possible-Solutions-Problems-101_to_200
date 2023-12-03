#include <iostream>
#include <iomanip>
using namespace std;

int L = 50;
int B = L/4;
int G = L/3;
int R = L/2;

double choose (int n, int p)
{
	double rval=1;
	if (n==p || p==0) return 1;
	else
	{
		if (p > n-p)
		{
			for (int i=n; i>p; i--) {rval*=i;}
			for (int i=n-p; i>0; i--) {rval/=i;}
		}
		else
		{
			for (int i=n; i>n-p; i--) {rval*=i;}
			for (int i=p; i>0; i--) {rval/=i;}
		}
		if (rval<=0) {cout<<n<<" "<<p<<" "<<rval<<endl;}
		return rval;
	}
}

void main ()
{
	int n,p; double sum=0;
	for (int b=1; b<=B; b++)
	{
		n = (L - 4*b) + b;
		p = b;
		sum+=choose(n,p);
		cout<<b<<"\t"<<sum<<endl;
	} 
	for (int g=1; g<=G; g++)
	{
		n = (L - 3*g) + g;
		p = g;
		sum+=choose(n,p);
		cout<<g<<"\t"<<sum<<endl;
	}
	for (int r=1; r<=R; r++)
	{
		n = (L - 2*r) + r;
		p = r;
		sum+=choose(n,p);
		cout<<r<<"\t"<<sum<<endl;
	}
	cout<<setiosflags(ios::fixed)<<sum<<endl; cin.get();
}