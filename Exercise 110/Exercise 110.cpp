#include <iostream>
#include <cmath>
#include <ctime>

#define N 4000000
#define Ull unsigned long long

using namespace std;

Ull primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71};

Ull minimum = (unsigned long long)0 - 1; //cause underflow to get max value

void partition(Ull index, Ull maxfact, Ull num, Ull factors){
	if(num >= minimum) return;
	
	if(factors >= N*2){
		minimum = num;
		return;
	}
	Ull factor_multiplier = 3;
	
	for(Ull i=1; i<=maxfact; ++i){
		num *= primes[index];
		partition(index+1, i, num, factors*factor_multiplier);
		factor_multiplier += 2;
	}
}

int main(){
	time_t start, end;
	
	start = clock();
	partition(0,(Ull)ceil(log(N)/log(2))+1,1,1);
	end = clock();
	
	cout << "min: " << minimum << '\n';
	cout << "time: " << (end-start)*1000/(double)CLOCKS_PER_SEC << " ms\n";
	
	system("PAUSE");
	return 0;
}