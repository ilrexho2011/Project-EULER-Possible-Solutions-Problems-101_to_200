#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int findNextPrime(int p);
bool isPrime(int p);
vector<int> multiply(vector<int> v1,vector<int> v2);
vector<int> eval(int pc,int prime); 
vector<int> power(int p,int k);
void evalPrimes(int n);
stack<int> primeComps(int n);
vector<int> primes(1,2);
vector<int> solution(int i, vector<int> res,stack<int> &pc);

int main() {
	evalPrimes(100000);
	stack<int> pc=primeComps(2*47547+1);
	vector<int> sol=solution(0,{1},pc);
	for(auto e:sol) {
		cout << e;
	}
	cout << endl;
}
vector<int> solution(int i, vector<int> res,stack<int> &pc) {
	if(pc.empty()) {
		return res;
	}
	vector<int> result=multiply(res,eval(pc.top(),primes[i]));
	pc.pop();
	return solution(i+1,result,pc);
}

stack<int> primeComps(int n) {
	stack<int> res;
	for(int i=0;primes[i]<=n;i++) {
		int p=primes[i];
		int pm=p;
		while(n%pm==0) {
			pm*=pm;
			res.push(p);
		}
	}
	return res;
}

void evalPrimes(int n) {
	bool prime;
	for(int k=3;k<n;k+=2) {	
		prime=true;
		for(auto p:primes) {
			if(k%p==0) {
				prime=false;
			}
		}
		if(prime) {
			primes.push_back(k);
		}
	}
}

vector<int> multiply(vector<int> v1,vector<int> v2) {
	vector<int> res(v1.size()+v2.size(),0);
	for(int i=0;i!=v1.size();i++) {
		for(int j=0;j!=v2.size();j++) {
			int prod=v1[i]*v2[j];
			int k=i+j;
			res[k]+=prod;
			int r=res[k];
			while(r>9) {
				res[k]=res[k]%10;
				res[k+1]+=r/10;
				r=res[++k];
			}
		}
	}
	return res;
}

vector<int> eval(int pc,int prime) {
	if(prime==2) {
		int k=(pc+1)/2; 
		return power(prime,k);
	}
	else {
		int k=(pc-1)/2;
		return power(prime,k);
	}
}

vector<int> power(int p,int k) {
	vector<int> pvec;
	while(p!=0) {
		pvec.push_back(p%10);
		p/=10;
	}
	vector<int> res=pvec;
	while((--k)!=0) {
		res=multiply(res,pvec);
	}
	return res;
}