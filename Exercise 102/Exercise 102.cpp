#include <stdio.h>

char s[100];
int x[4],y[4];

int area(int i,int j,int k)
{
   return abs(x[i]*y[j]-x[j]*y[i]+
              x[j]*y[k]-x[k]*y[j]+
              x[k]*y[i]-x[i]*y[k]);
}

int main()
{
   FILE *f=fopen("triangles.txt","r");
   int ans=0,taken=0;

   x[3]=y[3]=0;
   while(fscanf(f,"%d,%d,%d,%d,%d,%d",&x[0], &y[0],&x[1],&y[1],&x[2],&y[2])==6) {
      printf("%d - %d %d %d : %d\n",area(0,1,2),area(0,1,3),area(0,2,3),area(1,2,3),
         area(0,1,3)+area(0,2,3)+area(1,2,3));
      taken++;
      if(area(0,1,2)==area(0,1,3)+area(0,2,3)+area(1,2,3)) ans++;
   }
   fclose(f);
   printf("%d of %d\n",ans,taken);
}