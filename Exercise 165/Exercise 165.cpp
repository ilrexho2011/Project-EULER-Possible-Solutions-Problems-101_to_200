#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)

typedef long long LL;

// Powered By TimoAI 2.2

LL cache[32][16][16][16];

LL calc(int pos,int a,int b,int c)
{
	if(a+b+c > 9) return 0;
	LL &ret = cache[pos][a][b][c];
	if(ret>=0) return ret;
	if(pos==20) return 1;
	ret = 0;
	FOR(d,0,9) ret += calc(pos+1,b,c,d);
	return ret;
}

int main()
{
	memset( cache, -1, sizeof(cache) );
	LL ans = 0;
	FOR(a,1,9) FOR(b,0,9) FOR(c,0,9) ans += calc(3,a,b,c);
	printf("%I64d",ans);
	return 0;
}