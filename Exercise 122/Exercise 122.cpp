#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>

using namespace std;

struct Node {

	Node(unsigned v, Node* p = 0) : value(v), parent(p) {}
	unsigned value;
	Node* parent;
	vector<Node*> branch;
};

struct pred {
	pred(unsigned v) : val_(v) {};
	bool operator () (Node* node) { return node->value == val_; }
	unsigned val_;
};


int main()
{
    const unsigned maxPower(200);
    unsigned powersLeft(maxPower-1);
    Node* root(new Node(1));
    queue<Node*> next;
    vector<unsigned> addChainLength(maxPower+1,~0);

    next.push(root);

    while (powersLeft) {
        Node* currentNode = next.front();
	next.pop();

	for (Node* i = currentNode; i != 0; i = i->parent) {
	    for (Node* j = i; j != 0; j = j->parent) {
	        unsigned value = i->value + j->value;
		if (value > currentNode->value && value <= maxPower &&
	            find_if (currentNode->branch.begin(),currentNode->branch.end(),
		             pred(value)) == currentNode->branch.end()) {

		    currentNode->branch.push_back(new Node(value,currentNode));
		    next.push(currentNode->branch.back());

		    unsigned len(0);
		    for (Node* k = currentNode->branch.back(); k != root; k = k->parent)
		        len++;
		    if (addChainLength[value] > len) {
		        addChainLength[value] = len;
			powersLeft--;
		    }
		}
	    }
	}
     }
     cout << accumulate (addChainLength.begin()+2, addChainLength.end(), 0);
}