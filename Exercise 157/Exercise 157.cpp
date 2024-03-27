#include<stdio.h>
#include<math.h>

long long int factors(long long int j)
{
long long int s = 1;
long long int r;
r = 1;
while (j%2 == 0)
{
r++;
j = j/2;
}
s = s*r;
long long int l;
for (l=3;l<=sqrt(j);l+=2)
{
r = 1;
while (j%l == 0)
{
r++;
j = j/l;
}
s = s*r;
}
if (j>1)
{
s = 2*s;
}
return s;
}

long long int power(long long int i, long long int j)
{
long long int k;
long long int s = 1;
for (k=0;k<j;k++)
{
s = s*i;
}
return s;
}

long long int numsols(long long int j)
{
long long int y, x;
long long int s = 0;
long long int l;
s = s+factors(2*power(10,j));
for (y=1;y<=j;y++)
{
l = (power(2,y)+1)*(power(10,j)/(power(2,y)));
s = s+factors(l);
l = (power(5,y)+1)*(power(10,j)/(power(5,y)));
s = s+factors(l);
}
for (y=1;y<=j;y++)
{
for (x=1;x<=j;x++)
{
l = (power(2,y)+power(5,x))*(power(10,j)/((power(2,y)*power(5,x))));
s = s+factors(l);
l = (power(2,y)*power(5,x)+1)*(power(10,j)/((power(2,y)*power(5,x))));
s = s+factors(l);
}
}
return s;
}

int main()
{
long long int k, r;
scanf("%lld",&k);
long long int i;
long long int s = 0;
for (i=1;i<=k;i++)
{
r = numsols(i);
s = s+r;
printf("%lld \n",r);
}
printf("%lld \n",s);
}