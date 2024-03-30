#include <stdint.h>
#include <iostream>

const int N = 26;
int64_t table[N][N][2];

int64_t recm(int left,int right, int inuse, int d);
int64_t rec(int left,int right, int inuse, int d);


int64_t rec(int left,int right, int inuse, int d)
{
    if(d==0) return inuse;
    int64_t r=0;
    for(int i=0;i<right;i++)
        r+=recm(left+i,right-i-1,inuse,d-1);

    if(!inuse)
        for(int i=0;i<left;i++)
           r+=recm(i,right+left-i-1,1,d-1); 
    return r;
}


//memoisation
int64_t recm(int left,int right, int inuse, int d)
{
     if(table[left][right][inuse] < 0) 
         table[left][right][inuse] = rec(left,right, inuse,  d);

     return table[left][right][inuse]; 
}

int64_t solver(int n)
{
   //clear memoisation table
   for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
          table[i][j][0]=table[i][j][1]=-1;
   
   return rec(0,26,0,n);
}


int main()
{
     int64_t t,max = 0;
      
     for(int i=0;i<N;i++)
     {
         t = solver(i);
         if(t > max) max=t;
     }
     std::cout << max << std::endl;
    
}