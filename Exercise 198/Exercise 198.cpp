#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

long long int G,x,wort,GETAL,L1[250],L2[250],TOTAAL=49999950;			
int i,n1,n2,k,m;

int main(){
L2[1]=1;
n2=1;
for(G=100;G<=500000;G++){
	GETAL=50*(2*G-1);
	n1=n2;
	for(k=1;k<=n1;k++)L1[k]=L2[k];
	n2=0;
	wort=(long long int)sqrt((double)G);
	for(x=1;x<=wort;x++){
		if(!(G%x)){
			L2[++n2]=x;
			L2[++n2]=(G/x);
		}
	}
	if(wort*wort==G)n2--;
	for(m=1;m<=n1;m++){
		for(k=1;k<=n2;k++){
			if(L1[m]*L2[k]>GETAL){
				if(L1[m]*L2[k]<=50000000){
					TOTAAL++;
				}
			}
		}
	}
}

cout<<"TOTAAL is "<<TOTAAL<<"\n";
return 0;
}