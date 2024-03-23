#include "stdafx.h"
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	const unsigned int limit = 1000000000;
	unsigned int i;
	unsigned __int64 count = 0;

	unsigned __int64 a = 0;	//1
	unsigned __int64 b = 1;	//7
	unsigned __int64 c = 1;	//49
	unsigned __int64 d = 1; //343
	unsigned __int64 e = 1; //2401
	unsigned __int64 f = 1;	//16807
	unsigned __int64 g = 1;	//117649
	unsigned __int64 w = 1; //823543
	unsigned __int64 x = 1;	//5764801
	unsigned __int64 y = 1;	//40353607
	unsigned __int64 z = 1; //282475249

	char buff[100];

	for(i = 1;i <= limit;i++)
	{
		count+=(a+b);

		if(i%49 == 0)
		{
			if(i%343 == 0)
			{
				if(i%2401 == 0)
				{
					if(i%16807 == 0)
					{
						if(i%117649 == 0)
						{
							if(i%823543 == 0)
							{
								if(i%5764801 == 0)
								{
									if(i%40353607 == 0)
									{
										if(i%282475249 == 0)
										{
											z++;
											b = c = d = e = f = g = w = x = y = z;
											a = 0;
										}
										else
										{
											y+=z;
											b = c = d = e = f = g = w = x = y;
											a = 0;
										}
									}
									else
									{
										//40353607
										x+=y;
										b = c = d = e = f = g = w = x;
										a = 0;
									}
								}
								else
								{
									//5764801
									w+=x;
									b = c = d = e = f = g = w;
									a = 0;
								}

							}
							else
							{
								//823543
								g+=w;
								b = c = d = e = f = g;
								a = 0;
							}
						}
						else
						{
							//117649

							f+=g;
							b = c = d = e = f;
							a = 0;
						}
					}
					else
					{
						//16807
						e+=f;
						b = c = d = e;
						a = 0;
					}

				}
				else
				{
					//2401
					d+=e;
					b = c = d;
					a = 0;
				}
			}
			else
			{
				//343
				c +=d;
				b = c;
				a = 0;
			}
		}
		else
		{
			//49
			if (i%7 == 0)
			{
				b +=c;
				a = 0;
			}
			else
			{
				//normal progress
				a+=b;
			}
		}
	}

	cout << "answer=" << _ui64toa(count,buff,10) << endl;


	return 0;
}
