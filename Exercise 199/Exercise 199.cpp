#include <cmath>
#include <iostream>
#include <vector>

struct TTriple {
	double a, b, c;
};

double calc(double a, double b, double c)
{
	double OT_2;
	if (a < 0.9) {
		OT_2 = 2 * b * b * (1 - (b * b + a * b + b * c - a * c) / ((a + b) * (b + c)));
	} else {
		OT_2 = 2 * b * b * (1 - (b * b + b * c + a * c - a * b) / ((b - a) * (b + c)));
	}
	const double gipo_2 = 1 / OT_2;
	const double katet1 = 1 / (2 * b);
	const double katet2 = sqrt (gipo_2 - katet1 * katet1);
	const double r_inv = (b + c) / (4 * b * c);
	const double y_center = 2 * r_inv + katet2;
	const double OK_2 = 1 / (katet1 * katet1 + y_center * y_center);
	const double r = (b * (b + c) * OK_2) / (4 * b * b * c - (b + c) * OK_2);
	return r;
}

double iterate(std::vector<TTriple>& triples)
{
	double sum = 0;
	std::vector<TTriple> next;
    next.reserve(triples.size() * 3);
	for (size_t i = 0; i < triples.size(); i++) {
		const TTriple& triple = triples[i];
		const double r = calc(triple.a, triple.b, triple.c);
		sum += r * r;
		const TTriple t1 = {triple.a, triple.b, r};
		const TTriple t2 = {triple.a, triple.c, r};
		const TTriple t3 = {triple.b, triple.c, r};
		next.push_back(t1);
		next.push_back(t2);
		next.push_back(t3);
	}
	swap(next, triples);
	return sum;
}

int main()
{
	const int iterations = 10;
	std::vector<TTriple> triples;
	const double r = 1 / (2 / sqrt(3.0) + 1);
	const TTriple t1 = {1, r, r};
	const TTriple t2 = {r, r, r};
	triples.push_back(t1);
	triples.push_back(t1);
	triples.push_back(t1);
	triples.push_back(t2);
	double sum = r * r * 3;
	for (int i = 0; i < iterations; i++) {
		sum += iterate(triples);
		std::cout.precision(20);
		std::cout << i << ' ' << 1 - sum << std::endl;
	}
	return 0;
}