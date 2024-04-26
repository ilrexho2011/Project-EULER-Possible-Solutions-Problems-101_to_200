#include <stdio.h>
#include <math.h>

#define R 1053779LL

/*
Start point: (5, 8, 7)

Base conversion matrix:
[-1/3 -4/3  4/3]
[-4/3 -1/3  4/3]
[-2/3 -2/3  5/3]
 
example: (5, 8, 7) => (-3, 0, 3)


conversion matrix:
1. (x, y) => (y-x,y)  (need not to calculate recursively)
[-1 1 0]
[ 0 1 0]
[ 0 0 1]

2. (x, y) => (-x, -x+y) + base convert
[ 5/3 -4/3  4/3]
[ 5/3 -1/3  4/3]
[ 4/3 -2/3  5/3]

3. (x, y) => (-y,  x-y) + base convert
[-4/3  5/3  4/3]
[-1/3  5/3  4/3]
[-2/3  4/3  5/3]

4. (x, y) => (x-y, x) + base convert
[-5 1 4]
[-5 4 4]
[-4 2 5]

5. (x, y) => (-y, -x) + base convert
[4 1 4]
[1 4 4]
[2 2 5]

For example (5, 8, 7) =>
1. ( 3,  8,  7)
2. ( 7, 15, 13)
3. (16, 12, 19)
4. (11, 35, 31)
5. (56, 65, 61)

if they are not primitive (divisable by 3), it is not valid.

*/

int count = 0;
double r2;

int mat_base[][2][2] = {
  {{-1,  0},
   {-1,  1}},
  {{ 0, -1},
   { 1, -1}},
  {{ 1, -1},
   { 1,  0}},
  {{ 0, -1},
   {-1,  0}}
};

// divide by 3.
int base[3][3] = {
  {-1, -4, 4},
  {-4, -1, 4},
  {-2, -2, 5}
};

int mat[4][3][3];

void recur();
void update_base();

// for stack corruption
long long int *a2;
long long int *a;
long long int aa[300000][3];
int kk[300000];
int *k;

int i, j;
long long int r;

int main() {
  a = aa[0];
  a[0] = 5;
  a[1] = 8;
  a[2] = 7;
  a2 = aa[1];
  kk[0] = -1;
  k = kk+1;

  r2 = 2*R*sqrt(3);

  update_base();

  recur();

  printf ("Answer %d\n", count);
}

void recur() {

 Label_start: // recursion manually

  r = a[1]-a[0]+a[1]-a[2];
  count += r2/r;
  r = a[0]+a[1]-a[2];
  count += r2/r;
  
  if ((a[1]-a[0]>r2)&&(a[0]>r2))
    goto Label_pop;

  for (*k=0; *k<4; *k+=1) {
    for (i=0; i<3; i++) {
      a2[i] = 0;
      for (j=0; j<3; j++) 
	a2[i] += a[j]*mat[*k][i][j];
      if (*k<2) {
	if (a2[i]%3)
	  goto Label_next_k;
	a2[i] /= 3;
      }
    }

    if ((a2[0]%3)||(a2[1]%3)) {
      a2 += 3;
      a += 3;
      k++;
      goto Label_start;
    }

  Label_next_k:
    ;
  }

 Label_pop:

  a2 -= 3;
  a -= 3;
  k--;
  if (*k==-1)
    return;
  goto Label_next_k;
  
}

void update_base() {
  int i, j, k;

  for (k=0; k<4; k++) {
    for (i=0; i<3; i++)
      for (j=0; j<2; j++)
	mat[k][i][j] = base[i][0]*mat_base[k][0][j]+base[i][1]*mat_base[k][1][j];
    for (i=0; i<3; i++)
      mat[k][i][2] = base[i][2];
  }
}