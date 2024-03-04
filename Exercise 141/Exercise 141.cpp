#include <iostream>
#include <cmath>
#include <set>
using namespace std;

const uint64_t LIM=1000000000000;
//const uint64_t LIM=100000;

int main()
{
    uint64_t a,b,c,num,sum,root;
    set<uint64_t> solutions;
    set<uint64_t>::iterator it;
    for(a=1;a*(8*a+1)<LIM;a++)
    {
        for(b=2;a*(a*b*b*b+1)<LIM;b++)
        {
            for(c=1;c<b;c++)
            {
                num=a*c*(a*b*b*b+c);
                if(num>=LIM) break;
                root=floor(sqrt(num)+0.5);
                if(root*root==num) solutions.insert(num);
            }
        }
    }
    sum=0;
    for(it=solutions.begin();it!=solutions.end();it++) sum+= *it;
    cout << sum << endl;
    return 0;
}