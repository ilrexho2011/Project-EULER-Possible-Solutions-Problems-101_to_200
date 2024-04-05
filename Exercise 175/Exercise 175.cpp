#include <iostream>
#include <cstdlib>
#include <time.h> 
using namespace std;

int B=13717421,A=109739369;
int sb[10],n=0,i;
bool Q1;
double start;

int main(){
start=clock();
for(i=0;i<=9;i++)sb[i]=0;
if(A>B){
	A-=B;
	Q1=1;
	sb[++n]++;
}
else{
	B-=A;
	Q1=0;
	sb[++n]++;
}
while(A!=B){
	if(A>B){
		A-=B;
		if(!Q1){
			Q1=1;
			sb[++n]++;
		}
		else sb[n]++;
	}
	else{
		B-=A;
		if(Q1){
			Q1=0;
			sb[++n]++;
		}
		else sb[n]++;
	}
}
if(Q1)sb[n]++;
else sb[++n]++;

cout<<sb[n];
for(i=n-1;i>=1;i--)cout<<","<<sb[i];
cout<<"\n"<<clock()-start;
return 0;
}