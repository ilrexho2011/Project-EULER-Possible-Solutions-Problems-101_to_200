#include <iostream>
#include <cstdlib>
using namespace std;

long long int N,teller,i,aantal,periode,cycles,antwoord,nummer,TOTAAL=0;
bool T[5000001];

int main(){
for(N=5;N<=21;N+=2){
	for(i=0;i<=N;i++)T[i]=1;
	i=N;
	teller=0;
	aantal=0;
	while(teller<=N){
		if((T[i]||T[i-N])&&!(T[i]&&T[i-N])){
			T[++i]=1;
			teller++;
			aantal++;
		}
		else {
			T[++i]=0;
			teller=0;
		}
	}
	periode=2*(i-N);
	antwoord=3*N;
	nummer=N+3;
	cycles=100000000000/aantal;
	nummer+=(cycles*aantal);
	antwoord+=cycles*periode;
	if(nummer>100000000000){
		nummer-=aantal;
		antwoord-=periode;
	}
	i=N+1;
	while(nummer<100000000000){
		antwoord+=2;
		if(T[i])nummer++;
		i++;
	}
	cout<<"nummer is "<<nummer<<" antwoord is "<<antwoord<<"\n";
	TOTAAL+=antwoord;
}
cout<<"\nTOTAAL is "<<TOTAAL<<"\n";

return 0;
}