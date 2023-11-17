#include<stdio.h>
#include<math.h>

double i,j,k,sum,total,data[15][15];

void main(){
  for(i=1;i<=13;i++){
    for(j=0;j<11;j++){
      if(fmod(j,2)) data[1][i]-=pow(i,j);
      else data[1][i]+=pow(i,j);
      }
    }
  for(i=2;data[i-1][1];i++){
    for(j=2;data[i-1][j];j++) data[i][j-1]=data[i-1][j]-data[i-1][j-1];
    }
  for(i=2;i<12;i++){
    for(j=i,k=sum=0;j;j--,k++) sum+=data[j][k];
    total+=sum;
    }
  printf("%.0lf\n",total);
  }