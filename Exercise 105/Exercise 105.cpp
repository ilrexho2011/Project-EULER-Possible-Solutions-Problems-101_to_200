#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <set>

using namespace std;

bool checkProperties (const pair<vector<unsigned>,unsigned>&,
		      const pair<vector<unsigned>,unsigned>&);

int main() {
	ifstream sets("sets.txt");
	string line;
	unsigned sumSetsAcc(0);

	while (getline(sets,line)) {
		replace(line.begin(), line.end(),',',' ');

		istringstream is(line);
		vector<unsigned> sSet ((istream_iterator<unsigned>(is)),
				               istream_iterator<unsigned>());
		const unsigned subsetsNo(1 << sSet.size());
		vector<pair<vector<unsigned>,unsigned> > subsets;
		set<unsigned> sumsCache;
		bool isSpecialSumSet(true);

		// generate subsets using binary masks
		for (unsigned i = 1; i < subsetsNo && isSpecialSumSet; ++i) {
			vector<unsigned> subset;
			unsigned sum(0), k(0);
			for (unsigned j = i; j != 0; j >>= 1) {
				if (j & 1) {
					subset.push_back(sSet[k]);
					sum += sSet[k];
				}
				k++;
			}
			set<unsigned>::iterator it = sumsCache.find(sum);
			if (it != sumsCache.end())
				isSpecialSumSet = false;
			sumsCache.insert(sum);
			subsets.push_back(make_pair(subset,sum));
		}


		for (unsigned i = 1; i < subsets.size() && isSpecialSumSet; ++i)
			for (unsigned j = 0; j < i && isSpecialSumSet; ++j)
				if (!((i+1)&(j+1)))
					if (!checkProperties(subsets[i],subsets[j]))
						isSpecialSumSet = false;
		if (isSpecialSumSet)
			sumSetsAcc += subsets.back().second; //the last subset is the set itself
	}
	cout << sumSetsAcc;
}

bool checkProperties (const pair<vector<unsigned>,unsigned>& set1,
		      const pair<vector<unsigned>,unsigned>& set2) {
	if (set1.first.size() < set2.first.size())
		return set1.second < set2.second;
	else if (set1.first.size() > set2.first.size())
		return set1.second > set2.second;;
	return set1.second != set2.second;
}