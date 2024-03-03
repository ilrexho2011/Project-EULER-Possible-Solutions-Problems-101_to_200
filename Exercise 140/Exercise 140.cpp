#include <Windows.h>
#include <iostream>

int64_t solutions[6][2] = {
	{ 2, 7 },
	{ 5, 14 },
	{ 21, 50 },
	{ 42, 97 },
	{ 152, 343 },
	{ 296, 665 }
};

int64_t find_solutions(int limit)
{
	int64_t sum = 0;

	int n_sum = 0;
	int i = 0;

	int64_t n, s;
	while (n_sum < limit)
	{
		n = solutions[i][0];
		s = solutions[i][1];

		sum += n;
		n_sum++;

		solutions[i][0] = 161 * n + 72 * s + 224;
		solutions[i][1] = 360 * n + 161 * s + 504;

		i++;
		if (i > 5) { i = 0; }
	}

	return sum;
}

int main()
{
	LARGE_INTEGER ctime;
	LARGE_INTEGER ltime;
	LARGE_INTEGER clockFreq;

	int64_t result = 0;

	QueryPerformanceFrequency(&clockFreq);
	QueryPerformanceCounter(<ime);

	result = find_solutions(30);

	QueryPerformanceCounter(&ctime);
	int64_t time_us = (ctime.QuadPart - ltime.QuadPart) * 1000000 / clockFreq.QuadPart;

	std::cout << "result: " << result << std::endl;
	std::cout << "completed in " << time_us << " microseconds" << std::endl;
}