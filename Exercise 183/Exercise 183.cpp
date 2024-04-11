#include<iostream>
#include<cmath>
#define e 2.7182818284590452
using namespace std;
int gcd(int a,int b)
{
	if(a == 0)return b;
	else return gcd(b%a,a);
}
int D(int n)
{
	double a = floor(n/e);
	double b = ceill(n/e);
	int result;
	double x = a * log(n/a);
	double y = b * log(n/b);

	if(x >= y) result = (int)a;
	else result = (int)b;

	result /= gcd(n,result);
	while (result % 5 == 0)
	{
		result /= 5;
	}
	while (result % 2 == 0)
	{
		result /= 2;
	}
	if(result == 1)return -n;
	else return n;

}
int main()
{
	int sum = 0;
	for (int i = 5;i <= 10000;++i)
	{
		sum += D(i);
	}
	cout << sum << endl;

	return 0;
}
