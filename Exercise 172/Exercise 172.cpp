#include <iostream>

using namespace std;

/*
	int a,b,c,d,e;
	int dc[10];

	for(a = 1;a <= 9;a++)
		for(b = 0;b <= 9;b++)
			for(c = 0;c <= 9;c++)
				for(d = 0;d <= 9;d++)
					for(e = 0;e <= 9;e++)
					{
						memset(dc,0,sizeof(dc));

						dc[a]++;
						dc[b]++;
						dc[c]++;
						dc[d]++;
						dc[e]++;

						if(dc[a] <= 3 && dc[b] <= 3 && dc[c] <= 3 &&
							dc[d] <= 3 && dc[e] <= 3)
						{
							Count++;
						}
					}

	brute force answer for 5 digit number : 89586
*/



unsigned long long Count = 0;
bool first = true;
const int limit = 18;

unsigned long long Cache[limit + 1][5][5][5][5][5][5][5][5][5][5]={0};

void CountNums(int DigitsToGo,int _0 = 0,int _1 = 0,int _2 = 0,int _3 = 0,int _4 = 0,
								int _5 = 0,int _6 = 0,int _7 = 0,int _8 = 0,int _9 = 0)
{
	if(DigitsToGo == 0)
	{
		Count++;
	}
	else
	{
		if(Cache[DigitsToGo][_0][_1][_2][_3][_4][_5][_6][_7][_8][_9] != 0)
		{
			Count += Cache[DigitsToGo][_0][_1][_2][_3][_4][_5][_6][_7][_8][_9];	//cache hit ?
		}
		else
		{
			//use 0

			unsigned long long OldCount = Count;

			if(first == true)
				first = false;
			else
			{
				if(_0 + 1 <= 3)
					CountNums(DigitsToGo - 1,_0 + 1,_1,_2,_3,_4,_5,_6,_7,_8,_9);
			}
			
			//use 1

			if(_1 + 1 <= 3)
				CountNums(DigitsToGo - 1,_0,_1 + 1,_2,_3,_4,_5,_6,_7,_8,_9);
			

			//use 2

			if(_2 + 1 <= 3)
				CountNums(DigitsToGo - 1,_0,_1,_2 + 1,_3,_4,_5,_6,_7,_8,_9);
			
			//use 3

			if(_3 + 1 <= 3)
				CountNums(DigitsToGo - 1,_0,_1,_2,_3 + 1,_4,_5,_6,_7,_8,_9);

			//use 4

			if(_4 + 1 <= 3)
				CountNums(DigitsToGo - 1,_0,_1,_2,_3,_4 + 1,_5,_6,_7,_8,_9);

			//use 5

			if(_5 + 1 <= 3)
				CountNums(DigitsToGo - 1,_0,_1,_2,_3,_4,_5 + 1,_6,_7,_8,_9);

			//use 6

			if(_6 + 1 <= 3)
				CountNums(DigitsToGo - 1,_0,_1,_2,_3,_4,_5,_6 + 1,_7,_8,_9);

			//use 7

			if(_7 + 1 <= 3)
				CountNums(DigitsToGo - 1,_0,_1,_2,_3,_4,_5,_6,_7 + 1,_8,_9);

			//use 8

			if(_8 + 1 <= 3)
				CountNums(DigitsToGo - 1,_0,_1,_2,_3,_4,_5,_6,_7,_8 + 1,_9);


			//use 9

			if(_9 + 1 <= 3)
				CountNums(DigitsToGo - 1,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9 + 1);

			Cache[DigitsToGo][_0][_1][_2][_3][_4][_5][_6][_7][_8][_9] = Count - OldCount;
		}
	}
}

int main()
{
	CountNums(limit);

	cout << Count << endl;
}