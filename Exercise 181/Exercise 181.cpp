#include <inttypes.h>
#include <iostream>
#include <algorithm>


size_t const B=60;
size_t const W=40;


int main()
{
	uint64_t c[B+1][W+1]={1, 0};
	for(size_t n=1; n<=B+W; ++n)
	{
		for(size_t e=0; e<=n; ++e)
		{
			uint64_t d[B+1][W+1];
			for(size_t b=0; b<=B; ++b)
				for(size_t w=0; w<=W; ++w)
					d[b][w]=c[b][w];

			for(size_t i=1; i<=std::max(B, W); ++i)
			{
				size_t b=(n-e)*i;
				size_t w=e*i;
				if(b<=B && w<=W)
				{
					for(size_t cb=0; cb+b<=B; ++cb)
						for(size_t cw=0; cw+w<=W; ++cw)
							d[cb+b][cw+w]+=c[cb][cw];
				}
			}

			for(size_t b=0; b<=B; ++b)
				for(size_t w=0; w<=W; ++w)
					c[b][w]=d[b][w];
		}
	}
	uint64_t r=c[B][W];
	std::cout << "B=" << B << ", W=" << W << ", r=" << r << "\n";
	return 0;
}
