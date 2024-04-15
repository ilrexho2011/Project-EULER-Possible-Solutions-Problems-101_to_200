#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define RELAX 5000
#define NCOOL 5000
#define TRIALS 22
#define LENGTH 16
#define T0 12.0

const int trials[TRIALS][LENGTH+1] =
    {{5,6,1,6,1,8,5,6,5,0,5,1,8,2,9,3,2},
     {3,8,4,7,4,3,9,6,4,7,2,9,3,0,4,7,1},
     {5,8,5,5,4,6,2,9,4,0,8,1,0,5,8,7,3},
     {9,7,4,2,8,5,5,5,0,7,0,6,8,3,5,3,3},
     {4,2,9,6,8,4,9,6,4,3,6,0,7,5,4,3,3},
     {3,1,7,4,2,4,8,4,3,9,4,6,5,8,5,8,1},
     {4,5,1,3,5,5,9,0,9,4,1,4,6,1,1,7,2},
     {7,8,9,0,9,7,1,5,4,8,9,0,8,0,6,7,3},
     {8,1,5,7,3,5,6,3,4,4,1,1,8,4,8,3,1},
     {2,6,1,5,2,5,0,7,4,4,3,8,6,8,9,9,2},
     {8,6,9,0,0,9,5,8,5,1,5,2,6,2,5,4,3},
     {6,3,7,5,7,1,1,9,1,5,0,7,7,0,5,0,1},
     {6,9,1,3,8,5,9,1,7,3,1,2,1,3,6,0,1},
     {6,4,4,2,8,8,9,0,5,5,0,4,2,7,6,8,2},
     {2,3,2,1,3,8,6,1,0,4,3,0,3,8,4,5,0},
     {2,3,2,6,5,0,9,4,7,1,2,7,1,4,4,8,2},
     {5,2,5,1,5,8,3,3,7,9,6,4,4,3,2,2,2},
     {1,7,4,8,2,7,0,4,7,6,7,5,8,2,7,6,3},
     {4,8,9,5,7,2,2,6,5,2,1,9,0,3,0,6,1},
     {3,0,4,1,6,3,1,1,1,7,2,2,4,6,3,5,3},
     {1,8,4,1,2,3,6,4,5,4,3,2,4,5,8,9,3},
     {2,6,5,9,8,6,2,6,3,7,3,1,6,8,6,7,2}};

typedef struct
{
    int nums[LENGTH];
    double energy;
} iter;

double drand ()
{
    return (double)rand()/((double)RAND_MAX+1.0);
}

double energy (iter * a)
{
    int c, Nc;
    int e = 0;
    for (int i=0; i<TRIALS; ++i)
    {
        c = 0;
        Nc = trials[i][LENGTH];
        for (int j=0; j<LENGTH; ++j)
            if (a->nums[j] == trials[i][j]) ++c;
        e += ( c > Nc ? c-Nc : Nc-c );
    }
    return 2*(double)e;
}

void step (iter * a, double T)
{
    int r = rand()%LENGTH;
    int temp = a->nums[r];
    a->nums[r] = rand()%10;
    double etemp = energy(a);
    double de = etemp - a->energy;
    if (de < 0) { a->energy = etemp; } // accept
    else
    {
        if (drand() < exp(-de/T)) { a->energy = etemp; } // accept
        else {a->nums[r] = temp; } // reject
    }
    return;
}

int main (void)
{
    srand(time(NULL));
    double T = T0;
    iter a;
    a.energy = energy(&a);
    for (int i=0; i<NCOOL; ++i)
    {
        for (int j=0; j<RELAX; ++j)
        {
            step (&a, T);
            if (a.energy < 1.0)
                break;
        }
        if (a.energy < 1.0)
            break;
        T -= T0/NCOOL;
    }
    if (a.energy < 1.0)
        printf("Success!\n");
    else
        printf("Fail... E = %d, Run again\n", (int) a.energy);
    for (int i=0; i<LENGTH; ++i)
        printf ("%d", a.nums[i]);
    printf("\n");
}