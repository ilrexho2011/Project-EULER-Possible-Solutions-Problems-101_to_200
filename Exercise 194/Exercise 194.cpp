#include <cstdio>
typedef unsigned long long ull;
typedef long long ll;

size_t const N=7;
size_t const A=25;
size_t const B=75;
size_t const C=1984;
size_t const L=1e8;

#include "congruences.h"
typedef ul_mod<L> ulm;
#include "combinatorics.h"

typedef bool adj_matrix[N][N];
adj_matrix const adj_a=
{
	{},
	{1},
	{0, 1},
	{1, 0, 1},
	{0, 1, 1, 0},
	{0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 1},
};

adj_matrix const adj_b=
{
	{},
	{1},
	{0, 1},
	{0, 0, 1},
	{0, 1, 1, 0},
	{0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 1},
};

ulm rec(adj_matrix const &adj, ulm m=1, size_t n=2, size_t u=2)
{
	static size_t colors[N]={0, 1};
	if(n<N)
	{
		ulm r=0;
		for(size_t c=0; c<u; ++c)
		{
			bool ok=true;
			for(size_t j=0; ok && j<n; ++j)
				ok=!adj[n][j] || colors[j]!=c;
			if(ok)
			{
				colors[n]=c;
				r+=rec(adj, m, n+1, u);
			}
		}
		if(u<C)
		{
			colors[n]=u;
			r+=rec(adj, m*(C-u), n+1, u+1);
		}
		return r;
	}
	else return m;
}


int main()
{
	ulm ma=rec(adj_a);
	ulm mb=rec(adj_b);
	binomials<ulm, A+B> choose;
	ulm r=ma.pow(A)*mb.pow(B)*C*(C-1)*choose(A+B, A);

	printf("A=%zu, B=%zu, C=%zu, L=%g, r=%zu\n", A, B, C, double(L), r.gieb());
	return 0;
}
