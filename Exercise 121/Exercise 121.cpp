#include <iostream>
using namespace std;
#include <math.h>

void main ()
{
	bool wins[15];
	int counter=0;
	double xWin=1, pWin=0;
	long temp;

	for (long x=0; x<32768; x++)
	{
		temp = x;
		counter = 0; xWin = 1;
		for (int i=14; i>=0; i--)
		{
			if (x>=pow(2.0,i)) {x-=pow(2.0,i); wins[i]=true; counter++;}
			else {wins[i]=false;}
		}
		if (counter>=8)
		{
			for (int i=0; i<15; i++)
			{
				if (wins[i]) {xWin*=1.0/(i+2.0);}
				else {xWin*=(i+1.0)/(i+2.0);}
			}
			pWin+=xWin;
		}
		x = temp;
	}

	int prize=1;
	while (pWin*prize < 1) prize++;
	prize--;
	cout<<prize<<endl; cin.get();
}