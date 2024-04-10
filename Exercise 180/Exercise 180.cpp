#include <iostream>
#include <set>
#include <map>
using namespace std;

uint64_t gcd(uint64_t a,uint64_t b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}

class Fraction
{
    public:
    uint64_t num,den;

    Fraction(){}

    Fraction(uint64_t a)
    {
        num=a;
        den=1;
    }

    Fraction(uint64_t a,uint64_t b)
    {
        num=a;
        den=b;
    }

    void reduce()
    {
        uint64_t g=gcd(num,den);
        num/=g;
        den/=g;
    }

    Fraction operator+(Fraction b)
    {
        uint64_t g=gcd(den,b.den);
        Fraction result(num*(b.den/g)+b.num*(den/g),den/g*b.den);
        result.reduce();
        return result;
    }

    Fraction operator*(Fraction b)
    {
        Fraction result(num*b.num,den*b.den);
        result.reduce();
        return result;
    }

    friend ostream& operator<<(ostream& os,Fraction f)
    {
        os << f.num << '/' << f.den;
        return os;
    }
};

bool compFractions(Fraction a,Fraction b)
{
    return a.num*b.den<b.num*a.den;
}

Fraction mediant(Fraction a,Fraction b)
{
    return Fraction(a.num+b.num,a.den+b.den);
}

Fraction pow(Fraction base,int64_t exp)
{
    uint64_t temp;
    Fraction f;
    if(exp<0)
    {
        temp=base.num;
        base.num=base.den;
        base.den=temp;
        return pow(base,-exp);
    }
    if(exp==1) return base;
    f=pow(base,exp/2);
    if(exp%2==0) return f*f;
    return f*f*base;
}

bool (*fn_pt)(Fraction,Fraction)=compFractions;
set<Fraction,bool (*)(Fraction,Fraction)> allFracs(fn_pt),sxyz(fn_pt);
const uint64_t ORDER=35;
//const uint64_t ORDER=10;

void findMediants(Fraction a,Fraction b)
{
    Fraction f=mediant(a,b);
    if(f.den<=ORDER)
    {
        allFracs.insert(f);
        findMediants(a,f);
        findMediants(f,b);
    }
    return;
}

int main()
{
    set<Fraction,bool (*)(Fraction,Fraction)>::iterator it,xit,yit;
    Fraction t(0),zmin(2,ORDER),sum,x,y,z;
    map<uint64_t,uint64_t> squares;
    map<uint64_t,uint64_t>::iterator mit;
    uint64_t i;
    long double s1,s2;
    for(i=1;i<=ORDER;i++) squares[i*i]=i;
    findMediants(Fraction(0),Fraction(1));
    // n=1 case
    zmin.reduce();
    it=allFracs.find(zmin);
    while(it!=allFracs.end())
    {
        z=*it;
        sxyz.insert(z+z); // s(x,y,z) = 2z
        it++;
    }
    // n=2 case
    for(xit=allFracs.begin();xit!=allFracs.end();xit++) for(yit=xit;yit!=allFracs.end();yit++)
    {
        sum=pow(*xit,2)+pow(*yit,2);
        if(sum.num<sum.den)
        {
            mit=squares.find(sum.num);
            if(mit!=squares.end())
            {
                z.num=mit->second;
                mit=squares.find(sum.den);
                if(mit!=squares.end())
                {
                    z.den=mit->second;
                    x=*xit;
                    y=*yit;
                    sxyz.insert(x+y+z);
                }
            }
        }
    }
    // n=-2 case
    for(xit=allFracs.begin();xit!=allFracs.end();xit++) for(yit=xit;yit!=allFracs.end();yit++)
    {
        sum=pow(*xit,-2)+pow(*yit,-2);
        if(sum.num>sum.den)
        {
            mit=squares.find(sum.num);
            if(mit!=squares.end())
            {
                z.den=mit->second;
                mit=squares.find(sum.den);
                if(mit!=squares.end())
                {
                    z.num=mit->second;
                    x=*xit;
                    y=*yit;
                    sxyz.insert(x+y+z);
                }
            }
        }
    }
    // n=-1 case
    for(xit=allFracs.begin();xit!=allFracs.end();xit++) for(yit=xit;yit!=allFracs.end();yit++)
    {
        sum=pow(*xit,-1)+pow(*yit,-1);
        z=pow(sum,-1);
        if(z.num<z.den) if(z.den<=ORDER)
        {
            x=*xit;
            y=*yit;
            sxyz.insert(x+y+z);
        }
    }
    // Find t
    s1=0;
    for(it=sxyz.begin();it!=sxyz.end();it++)
    {
        t=t+*it;
 //       s1+=(long double) it->num/(long double) it->den;
    }
    cout << t.num+t.den << endl;
 /*   cout << t << endl;
    s2=(long double)t.num/(long double)t.den;
    cout << s1 << ' ' << s2 << endl; */
    cout << sxyz.size() << endl;
    return 0;
}