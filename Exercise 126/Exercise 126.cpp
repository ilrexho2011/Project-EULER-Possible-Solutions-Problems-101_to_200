#include <stdio.h>
#include <cmath>

#define N 30000
#define K 1000

int main() {
  int count[N] = {0};
  for (int a = 1; a <= sqrt(N/6); a++) {
    for (int b = a; b <= (sqrt(4*a*a + 2*N)-a)/4; b++) {
      for (int c = b; 2*(a*b +a*c + b*c) < N; c++) {
        int n = 0;
        int v = 2*(a*b + b*c + a*c);
        while (v < N) {
          count[v]++;
          v += 4*(a+b+c + 2*n);
          n++;
        }
      }
    }
  }
  for (int n = 2; n < N; n+=2) {
    if (count[n] == K) {
      printf("%d\n", n);
      break;
    }
  }
  return 0;
}