#include <iostream>
#include <cmath>

using namespace std;


long double f(long double x)
{
	return (1e-9)*floor(pow(2,30.403243784-x*x));
}

int _tmain(int argc, _TCHAR* argv[])
{
	long double u[2],t;

	unsigned long long i = 1;

	u[0] = -1;

	cout.precision(10);
	
	while(true)
	{
		u[1] = f(u[0]);

		if(i%1000000 == 0)
			cout << "u[" << i << "]=" << u[1] + u[0] << endl; 
		u[0] = u[1];
		i++;
	}

	return 0;
}