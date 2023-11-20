#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int score(const vector<int>&);
bool required(const int&, const int&);
int main(){
	const int n = 12;
	int comp_step = 0;

	int p2[] = {0,0,1,1,2,2,2,2,2,2,2,2};
	vector<int> shuffle(p2, p2+n);
	int top_score = count(shuffle.begin(), shuffle.end(), 0);
	do{
		bool status = required(score(shuffle), top_score);
		if (status) ++comp_step;
	}while (next_permutation(shuffle.begin(), shuffle.end()));
	cout << "p2 = " << comp_step << "\n";

	int p3[] = {0,0,0,1,1,1,2,2,2,2,2,2};
	shuffle.assign(p3, p3+n);
	top_score = count(shuffle.begin(), shuffle.end(), 0);
	do{
		bool status = required(score(shuffle), top_score);
		if (status) ++comp_step;
	}while (next_permutation(shuffle.begin(), shuffle.end()));
	cout << "p3 = " << comp_step << "\n";

	int p4[] = {0,0,0,0,1,1,1,1,2,2,2,2};
	shuffle.assign(p4, p4+n);
	top_score = count(shuffle.begin(), shuffle.end(), 0);
	do{
		bool status = required(score(shuffle), top_score);
		if (status) ++comp_step;
	}while (next_permutation(shuffle.begin(), shuffle.end()));
	cout << "p4 = " << comp_step << "\n";

	int p5[] = {0,0,0,0,0,1,1,1,1,1,2,2};
	shuffle.assign(p5, p5+n);
	top_score = count(shuffle.begin(), shuffle.end(), 0);
	do{
		bool status = required(score(shuffle), top_score);
		if (status) ++comp_step;
	}while (next_permutation(shuffle.begin(), shuffle.end()));
	cout << "p5 = " << comp_step << "\n";

	int p6[] = {0,0,0,0,0,0,1,1,1,1,1,1};
	shuffle.assign(p6, p6+n);
	top_score = count(shuffle.begin(), shuffle.end(), 0);
	do{
		bool status = required(score(shuffle), top_score);
		if (status) ++comp_step;
	}while (next_permutation(shuffle.begin(), shuffle.end()));
	cout << "p6 = " << comp_step << "\n";

	cout << "total == " << comp_step/2 << "\n";
	return 0;
}
int score(const vector<int>& vec){
	vector<int> left_zero, right_one;
	for (int ii = 0; ii < vec.size(); ++ii){
		if (0 == vec[ii]) left_zero.push_back(ii);
		if (1 == vec[ii]) right_one.push_back(ii);
	}//vec.size()
	
	int record = 0;
	for (int ii = 0; ii < left_zero.size(); ++ii){
		if (left_zero[ii] > right_one[ii]) ++record;
		else --record;
	}//left_zero.size()
	return record;
}//score()

bool required(const int& record, const int& max_score){//if the comparison is necessary
	if (max_score == record || -max_score == record) return false;
	else return true;
}//requred()