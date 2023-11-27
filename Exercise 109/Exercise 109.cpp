#include <iostream>

int sec[] = {

    1,  2,  3,  4,  5,  // singles
    6,  7,  8,  9,  10,
    11, 12, 13, 14, 15,
    16, 17, 18, 19, 20,

    3,   6,  9, 12, 15, // triples
    18, 21, 24, 27, 30,
    33, 36, 39, 42, 45,
    48, 51, 54, 57, 60,

    25, 50,             // bulls

     2,  4,  6,  8, 10, // doubles
    12, 14, 16, 18, 20,
    22, 24, 26, 28, 30,
    32, 34, 36, 38, 40

};



int main()
{
    int doublePos = 41;
    int size = sizeof(sec) / sizeof(*sec);
    int cnt = 0;

    for( int i = 0; i < size; i++ ) {

        for( int k = doublePos; k < size; k++ )
            if( sec[i] + sec[k] < 100 )
                cnt++;

        for( int j = i; j < size; j++ )
            for( int k = doublePos; k < size; k++ )
                if( sec[i] + sec[j] + sec[k] < 100 )
                    cnt++;
    }

    for( int k = doublePos; k < size; k++ )
            cnt++;

    std::cout << cnt << std::endl;
    return 0;
}