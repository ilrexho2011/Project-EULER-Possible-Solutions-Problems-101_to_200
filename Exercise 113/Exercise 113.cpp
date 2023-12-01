#include <stdio.h>

__int64 incCache[10][100];
__int64 decCache[10][100];

__int64 inc(int f, int len)
{
	if (len == 1)
		return 9 - f + 1;

	if (incCache[f][len] != -1)
		return incCache[f][len];

	__int64 num = 0;
	for (int i = f; i <= 9; i++)
		num += inc(i, len - 1);

	return incCache[f][len] = num;
	return num;		
}

__int64 inc(int len)
{
	__int64 num = 0;
	for (int i = 1; i <= 9; i++)
		num += inc(i, len - 1);
	return num;
}

__int64 dec(int f, int len)
{
	if (len == 1)
		return f + 1;

	if (decCache[f][len] != -1)
		return decCache[f][len];

	__int64 num = 0;
	for (int i = f; i >= 0; i--)
		num += dec(i, len - 1);

	return decCache[f][len] = num;
	return num;
}

__int64 dec(int len)
{
	__int64 num = 0;
	for (int i = 9; i >= 1; i--)
		num += dec(i, len - 1);
	return num;
}

__int64 notB(int len)
{
	if (len == 1)
		return 9;

	return inc(len) + dec(len) - 9;
}

int main()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			incCache[x][y] = -1;
			decCache[x][y] = -1;
		}
	}

	__int64 sum = 0;
	for (int i = 1; i <= 100; i++)
	{
		sum += notB(i);
		printf("%d %I64d\n", i, sum);
	}	
}