#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#define ULL unsigned long long

using namespace std;

void generatePrime(vector<ULL>& li, ULL max)
{
    li.push_back(2);
    li.push_back(3);
    li.push_back(5);
    li.push_back(7);

    vector<ULL>::const_iterator it;

    for (ULL i=11; i<max; i++)
    {

        ULL sqrtNum= sqrtl(static_cast<long double>(i));
        bool flag=true;
        for (it=li.begin(); it!=li.end(); it++)
        {
            if(sqrtNum<*it)
                break;
            if (i%(*it)==0)
            {
                flag=false;
                break;
            }
        }
        if (flag==true)
        {
            li.push_back(i);
        }           
    }
}
void printULL(ULL i)
{
	static int count=1;
	cout<<i<<"\t";
	if((count)%10==9)
	{
		cout<<endl;
	}
	count++;
}
//if n is a odd number,then the reminder is 2*n*li[i] afer n>3
//else if n is a even number, then the reminder is always 2
// so the answer is easy to get
int main()
{
	ULL InNum=1000000;
	vector<ULL> li;
	vector<ULL>::size_type len;
	generatePrime(li, InNum);
	len=li.size();
	
	for (ULL i=2; i<len; i+=2)
	{
		ULL n=i+1;
		ULL reminder=2*n*li[i];
		if(reminder>1E10)
		{
			cout<<n<<endl;
			break;
		}
	}
	return 0;
}
