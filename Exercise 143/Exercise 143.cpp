#define __STDC_FORMAT_MACROS
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <math.h>
#include <vector>
#include <algorithm>

typedef unsigned int uint_t;
typedef uint32_t val_t;
typedef uint32_t idx_t;


struct Pair {
	val_t a, b;
};
typedef std::vector<Pair> Pairs;

bool operator< (const Pair &x, const Pair &y)
{
	return (x.a != y.a) ? (x.a < y.a) : (x.b < y.b);
}


bool gcd1(uint_t a, uint_t b)
{
	if (((a | b) & 1) == 0)
		return false;
	if (a == 0)
		return b == 1;
	if (b == 0)
		return a == 1;
	while ((a & 1) == 0)
		a >>= 1;
	while ((b & 1) == 0)
		b >>= 1;

	for (;;) {
		uint_t c = a - b;
		if (a < b) {
			c = -c;
			b = a;
		}
		if (c == 0)
			break;
		do { c >>= 1; }
		while ((c & 1) == 0);
		a = c;
	}
	return a == 1;
}



void fill_pairs(uint64_t m, Pairs &res)
{
	res.resize(0);
	res.reserve(m + m + (m + m) / 5);

	uint_t v_max = (uint_t) floor(0.25 + sqrt(m));
	assert (v_max > 0);
	uint64_t q = m / v_max;
	if (q < v_max)
		v_max--;
	fprintf(stderr, "m=%" PRIu64 ", v_max=%u, q=%" PRIu64 " \n",
		m, v_max, q);
	for (uint_t v = 1; v <= v_max; v++) {
		uint_t u_min = v + 1, u_max = v + v - 1;
		assert (m >= v * (uint64_t) v);
		uint64_t u_max1 = v + (m - v * v) / 2 / v;
		if (u_max > u_max1)
			u_max = u_max1;
#if 0
		fprintf(stderr, "v=%u, u_min=%u, u_max=%u \n",
			v, u_min, u_max);
#endif
		for (uint_t u = u_min; u <= u_max; u++) {
			if ((u % 3) + (v % 3) == 3)
				continue;
			if (!gcd1(u, v))
				continue;
			uint64_t p = u * (uint64_t) (v - (u - v));
			uint64_t q = (u - v) * (u + (uint64_t)v);
			uint64_t ppq = p + q;
#if 0
			fprintf(
				stderr,
				"u=%u, p=%" PRIu64 ", q=%" PRIu64 ", p+q=%" PRIu64 " \n",
				u, p, q, ppq
			);
#endif

			if (p > q) {
				uint64_t t = p; p = q; q = t;
			}

			assert (ppq <= m);
			uint64_t j = m / ppq;
			for (uint64_t i = 1; i <= j; i++) {
				Pair pa = {p * i, q * i};
				res.push_back(pa);
			}
		}

	}
}

void dump_pairs(Pairs const &pairs)
{
	size_t l = pairs.size();
	fprintf(stderr, "dump_pairs: l=%" PRIu64 " \n", (uint64_t) l);
	for (size_t i = 0; i < l; i++) {
		fprintf( stderr, "pairs[%" PRIu64 "] = (%" PRIu64 ", %" PRIu64 ") \n",
			(uint64_t) i, (uint64_t) pairs[i].a, (uint64_t) pairs[i].b);
	}
}


void fill_idxs1(size_t n, Pairs const &pairs, std::vector<idx_t> &idxs)
{
//	dump_pairs(pairs);

	idxs.resize(n + 1);
	idxs[0] = 0;
	val_t j = 0;
	size_t l = pairs.size();

	for (size_t i = 0; i < l; i++) {
		val_t a = pairs[i].a;
		assert (a < n);
		if (a == j)
			continue;
		assert (a > j);
		for (j++; j <= a; j++)
			idxs.at(j) = i;
		j--;
	}
	for (j++; j <= n; j++)
		idxs.at(j) = l;
}

void intersect(
	std::vector<Pair> const &pairs,
	size_t aidxb, size_t aidxe,
	size_t bidxb, size_t bidxe,
	std::vector<uint64_t> &res
) {
	res.resize(0);
	size_t aidx = aidxb, bidx = bidxb;
	while (aidx < aidxe && bidx < bidxe) {
		Pair const &pa = pairs[aidx];
		Pair const &pb = pairs[bidx];
		if (pa.b <= pb.b)
			aidx++;
		else
			bidx++;

		if (pa.b == pb.b) {
			bidx++;
			res.push_back(pa.b);
		}
	}
}


uint64_t use_pairs(size_t n, Pairs const &pairs)
{
	uint64_t res = 0;
	size_t l = pairs.size();

	std::vector<idx_t> idxs;
	fprintf(stderr, "filling indices \n");
	fill_idxs1(n, pairs, idxs);

	std::vector<uint64_t> cs;
	std::vector<uint64_t> abcs(0);

	uint64_t a_max = n / 3;

	fprintf(stderr, "looping pairs \n");
	for (size_t i = 0; i < l; i++) {
		Pair const &pi = pairs[i];
		uint64_t a = pi.a, b = pi.b;
		assert (a < b);

		if (a > a_max)
			break;

		uint64_t apb = a + b;
		assert (apb >= a && apb < n);
		uint64_t c_max = n - apb;

		if (b >= c_max)
			continue;

		size_t aidxb = i + 1,      aidxe = idxs.at(a + 1);
		size_t bidxb = idxs.at(b), bidxe = idxs.at(b + 1);
		intersect(pairs, aidxb, aidxe, bidxb, bidxe, cs);
		size_t cl = cs.size();
		for (size_t j = 0; j < cl; j++) {
			uint64_t c = cs[j];
#if 1
			if (c > c_max)
				break;
#endif
			uint64_t abc = a + b + c;
#if 1
			fprintf(
				stderr,
				"a=%" PRIu64 ", b=%" PRIu64 ", c=%" PRIu64 ", a+b+c=%" PRIu64 " \n",
				a, b, c, abc
			);
#endif
			abcs.push_back(abc);
		}
	}

	size_t abcl = abcs.size();
	std::sort(abcs.begin(), abcs.end());
	size_t abccnt = 0;
	uint64_t abcsum = 0;
	for (size_t i = 0; i < abcl; i++) {
		if (i > 0 && abcs[i] == abcs[i - 1])
			continue;
		abccnt++;
		abcsum += abcs[i];
	}
	fprintf(stderr, "abcl=%" PRIu64 ", abccnt=%" PRIu64 " \n",
		(uint64_t) abcl, (uint64_t) abccnt);

	res = abcsum;
	return res;
}


int main()
{
	size_t n = 1000000000;
	assert (n > 0);
	std::vector<Pair> pairs;
	fprintf(stderr, "filling pairs \n");
	fill_pairs(n - 1, pairs);
	fprintf(stderr, "n=%" PRIu64 ", npairs=%" PRIu64 " \n",
		(uint64_t) n, (uint64_t) pairs.size());
	fprintf(stderr, "sorting pairs \n");
	std::sort(pairs.begin(), pairs.end());
	fprintf(stderr, "using pairs \n");
	uint64_t res = use_pairs(n, pairs);
	fprintf(stderr, "res=%" PRIu64 " \n", res);

	return 0;
}