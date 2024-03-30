#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <vector>
#include <math.h>
typedef unsigned int uint_t;

static uint_t dr(uint_t n) { return (n - 1) % 9 + 1; }

uint64_t solve(uint64_t n)
{
	std::vector<uint8_t> mdrs;
	mdrs.resize(n);
	for (uint64_t i = 2; i < n; i++)
		mdrs[i] = dr(i);
	std::vector<uint_t> gens;

	for (uint64_t i = 2; i < n; i++) {
		uint64_t ndi = (n - 1) / i;
		uint_t j_max = i <= ndi ? i : ndi;

		uint_t dri = mdrs[i]; // it is optimal
		if (i <= ndi && dri == dr(i))
			gens.push_back(i);

		uint_t l = gens.size();
		for (uint_t k = 0; k < l; k++) {
			uint_t j = gens[k];
			if (j > j_max)
				break;

			uint8_t drij = dri + mdrs[j];
			uint64_t ij = i * j;
			if (mdrs[ij] < drij)
				mdrs[ij] = drij;
		}
	}

	fprintf(stderr, "gens.size=%u \n", (uint_t) gens.size());

	uint64_t res = 0;

	for (uint64_t i = 2; i < n; i++) {
		uint_t dri = mdrs[i];
		res += dri;
		assert (res >= dri);
	}

	return res;
}

int main(int ac, char **av)
{
	uint64_t n = 1000000;
	if (ac >= 2) {
		char tmpc;
		int r = sscanf(av[1], "%" PRIi64 "%c", &n, &tmpc);
		if (r != 1) {
			fprintf(stderr, "Illegal argument n='%s' \n", av[1]);
		}
	}

	uint64_t res = solve(n);
	fprintf(stderr, "n=%" PRIu64 ", res=%" PRIu64 " \n", n, res);
	return 0;
}