#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Line {
	public:
		constexpr static double MAXSLOPE=100;
		Line(int s, int e, pair<double,double> coeff):start(s), end(e), coeff(coeff) {}
		int getStart() {
			return start;
		}
		int getEnd() {
			return end;
		}
		pair<double,double> getCoeff() {
			return coeff;
		}
		pair<bool,pair<double,double>> intersectWith(Line l,int n) {
			if(coeff.first-l.getCoeff().first!=0) {
				double x=0;
				double y=0;
				if(coeff.first!=MAXSLOPE && l.getCoeff().first!=MAXSLOPE) {
					x=(l.getCoeff().second-coeff.second)/(coeff.first-l.getCoeff().first);
					y=coeff.first*x+coeff.second;
				}
				else if(coeff.first==MAXSLOPE) {
					x=coeff.second;
					y=l.getCoeff().first*x+l.getCoeff().second;
				}
				else {
					x=l.getCoeff().second;
					y=coeff.first*x+coeff.second;
				}
				if((x+0.01>=0 && x<=2*n && y+0.01>=0 && y-0.01<=x) || (x>=2*n && x<=4*n && y+0.01>=0 && y-0.01<=4*n-x)) {
					return {true,{x,y}};
				}
			}
			return {false,{pair<double,double>()}};
		}	
		
	private:
		int start;
		int end;
		pair<double,double> coeff;
};

long long T(int n);
int getPos(int k,int rand);
void createLines(vector<Line> &lines, int n);
pair<double,double> getCoeff(int k1, int k2,int n);
pair<int,int> getCoords(int k,int n);
bool separatePoints(pair<double,double> p1, pair<double,double> p2, pair<double,double> p3);


int main() {
	cout << T(1) << endl;
	cout << T(2) << endl;
	cout << T(36) << endl;
}

pair<double,double> getCoeff(int k1, int k2,int n) {
	pair<int,int> c1=getCoords(k1,n);
	pair<int,int> c2=getCoords(k2,n);
	double a=0;
	double b=0;
	if(c1.first-c2.first==0) {
		b=c1.first;
		a=Line::MAXSLOPE;
	}
	else {
		a=(double)(c1.second-c2.second)/(c1.first-c2.first);
		b=(double)(c1.second-a*c1.first);
	}	
	return {a,b};
}

pair<int,int> getCoords(int k,int n) {
	int s=1;
	int x=4*n;
	int y=0;
	while(s!=k) {
		if(s<2*n+1) {
			x-=2;
		}
		else {
			x+=1;
			if(s<4*n+1) {
				y+=1;
			}
			else {
				y-=1;
			}
		}
		s++;
	}
	return {x,y};
}



int getPos(int k,int rand) {
	if(k>0 && k<rand+1) {
		return k;
	}
	while(k<=0) {
		k+=rand;
	}
	while(k>rand) {
		k-=rand;
	}
	return k;
}

void createLines(vector<Line> &lines, int n) {
	int rand=6+6*(n-1);
	for(int k=2;k!=1+2*n;k++) {
		int k1=getPos(k,rand);
		int k2=getPos(rand+3-2*k,rand);
		Line l1(k1,k2,getCoeff(k1,k2,n));
		lines.push_back(l1);
		k1=getPos(k+2*n,rand);
		k2=getPos(3+2*n-2*k,rand);
		Line l2(k1,k2,getCoeff(k1,k2,n));
		lines.push_back(l2);
		k1=getPos(k+4*n,rand);
		k2=getPos(3+4*n-2*k,rand);
		Line l3(k1,k2,getCoeff(k1,k2,n));
		lines.push_back(l3);
	}
	for(int k=1;k!=1+2*n;k+=2) {
		int k1=getPos(k,rand);
		int k2=getPos(2+4*n-k,rand);
		Line l1(k1,k2,getCoeff(k1,k2,n));
		lines.push_back(l1);
		k1=getPos(2+2*n-k,rand);
		k2=getPos(4*n+k,rand);
		Line l2(k1,k2,getCoeff(k1,k2,n));
		lines.push_back(l2);
		k1=getPos(2-k,rand);
		k2=getPos(2*n+k,rand);
		Line l3(k1,k2,getCoeff(k1,k2,n));
		lines.push_back(l3);
	}
}

bool separatePoints(pair<double,double> p1, pair<double,double> p2, pair<double,double> p3) {
	if(!((floor(p1.first*10)==floor(p2.first*10)) && (floor(p1.second*10)==floor(p2.second*10)))) {
		if(!((floor(p2.first*10)==floor(p3.first*10)) && (floor(p2.second*10)==floor(p3.second*10)))) {
			if(!((floor(p3.first*10)==floor(p1.first*10)) && (floor(p3.second*10)==floor(p1.second*10)))) {
				return true;
			}
		}
	}
	return false;
}
		

long long T(int n) {
	vector<Line> lines;
	createLines(lines,n);
	long long sum=0;
	for(int i=0;i!=lines.size()-2;i++) {
		for(int j=i+1;j!=lines.size()-1;j++) {
			pair<bool,pair<double,double>> p1=lines[i].intersectWith(lines[j],n);
			for(int k=j+1;k!=lines.size();k++) {
				pair<bool,pair<double,double>> p2=lines[j].intersectWith(lines[k],n);
				pair<bool,pair<double,double>> p3=lines[k].intersectWith(lines[i],n);
				if(p1.first && p2.first && p3.first) {
					if(separatePoints(p1.second,p2.second,p3.second)) {
						sum++;
					}
				}
			}
		}
	}
	return sum;
}