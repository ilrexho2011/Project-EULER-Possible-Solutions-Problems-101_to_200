#include <stdio.h>
#include <stdlib.h>

// Let us consider x + yi,  where gcd(x,y) = g,  x = gx', y = gy'.

// This is a factor of n, some n <= MAX <=> g * norm(x'+y'i) <= MAX.
// In which case, the number of multiples of x+yi is given by 
// floor(MAX / (g*norm(x+yi))).


int gcd(int a, int b) {
   if (b==0) return a;
   return gcd(b, a%b);
}


main() {
   int n;
   int i, j, g, norm;
   long long sum = 0;
   int *norms;

   printf("Enter n: ");
   scanf("%d", &n);

   norms = (int *)malloc(sizeof(int) * (n+1));

   // Compile norms - find all (i,j) with i^2 + j^2 = n, i,j >= 0,
   // and add the i's.

   for(i=0; i<=n; i++) norms[i] = 0;

   for(i=0; i*i <= n; i++) 
      for(j=0; i*i + j*j <= n; j++) 
      if (gcd(i,j) == 1)
         if (j==0)
            norms[i*i + j*j] += i;
         else
            norms[i*i + j*j] += 2*i;


   for(i=1; i<=n; i++)
      if (norms[i] > 0) 
         for(g=1; g*i <= n; g++) 
            sum += g * norms[i] * (n / (g*i));


   printf("%lld\n", sum);
   free(norms);
}