#include <iostream>
#include <cassert>

using namespace std;

const int maxNum = 31;

int counts[maxNum];

static inline int initcounts()
{
    memset(counts, 0, maxNum*sizeof(int));
    counts[0] = 1;
    counts[1] = 2;
    counts[2] = 4;
    counts[3] = 7; // first occurence of AAA
    for (int i=4; i<maxNum; i++) {
            counts[i]=counts[i-1]*2-counts[i-4]; // ...O + ...A - ...OAAA
    }
}

static long long getsum(int x)
{
    assert(x<maxNum);
    long long sum = 0;
    sum += counts[x];
    for (int i=0; i<x; i++) {
        sum += counts[x-1-i] * counts[i]; // split string by L
    }
    return sum;
}

int main()
{
    initcounts();
    cout << getsum(30) << endl;
}