#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
long compteur,flag,y;
double x;

long solutions(double n)
{
     x=n+1;
     compteur=0;
     while (x<=2*n)
     {
           if ((x*n)/(x-n)-floor((x*n)/(x-n))==0)
           {
                 compteur=compteur+1;
           }
     x++;
     }
return compteur;
}

int main(int argc, char *argv[])
{
    flag=0;
    y=0;
    while (flag==0)
    {
        y++;
        if (y%10000==0)
        printf(\"%ld\\n\",y);
        if (solutions(y)>=1000)
        flag=1;
    }  
    printf(\"%ld\\n\",y);
    system(\"PAUSE\");
}