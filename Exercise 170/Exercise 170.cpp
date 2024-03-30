
#include<stdio.h>
#define n 10

int t,lt,i,j,k;
char p[n],used[n],result[n];
char d0[1000],d1[1000],d2[1000],d21[1000];

long long val,maxval=0;

int nextperm(char size, char *p, char overflow) {
  char i,j,h;
  for(i=size-1;i;i--)if(p[i-1]<p[i])break;     
  if(i) {
    overflow=1;
    for(h=p[i-1],j=size-1;;j--) 
      if(p[j]>h){p[i-1]=p[j];p[j]=h;break;}
  } 
  else if(!overflow) return 0; else overflow=0; // signal "overflow"
  for(j=size-1;i<j;i++,j--){h=p[i];p[i]=p[j];p[j]=h;}
  return overflow;
}

char add(int d0, int d1, int d2) {
  if(d2) {
    if(used[d0]||used[d1]||used[d2]||d0==d1||d1==d2||d0==d2) return 0;
    used[d0]=1; used[d1]=1; used[d2]=1;
    result[j++]=d0; result[j++]=d1; result[j++]=d2;
  }
  else if(d1) {
    if(used[d0]||used[d1]||d0==d1) return 0;
    used[d0]=1; used[d1]=1; 
    result[j++]=d0; result[j++]=d1; 
  }
  else {
    if(used[d0]) return 0;
    used[d0]=1;
    result[j++]=d0;
  }
  i++;
  return 1;
}
void del(int d0, int d1, int d2) {
  if(d2) {
    used[d0]=0; used[d1]=0; used[d2]=0;
    j-=3;
  }
  else if(d1) {
    used[d0]=0; used[d1]=0;
    j-=2;
  }
  else {
    used[d0]=0;
    j--;
  }
  i--;
}

void recurse(int c) {
  if(j>i+lt) return; 
  if(i==n-lt) {
    if(j==n && c==0) {
      for(val=0,k=10;k--;) val*=10,val+=result[k];
      if(val>maxval) {
        maxval=val;
        printf("t=%d %lld\n",t,maxval);
      }
    }
    return;
  }
  int x = c + t * p[i];
  
  if(d21[x]==0) {  // no carry
    if(add(d0[x],0,0)) {  // take care of special case: last digit was 0
      if(p[i-1]||i<n-lt) recurse(0);
      if(!p[i-1]) {
        i--;
        if(add(0,0,0)) {
          recurse(0);
          del(0,0,0);
        }
        i++;
      }
      del(d0[x],0,0);
    }
  }
  else {
    // write carry
    if(p[i] && add(d0[x],d1[x],d2[x]))
      recurse(0), del(d0[x],d1[x],d2[x]);
    // forward carry
    if(add(d0[x],0,0)) 
      recurse(d21[x]), del(d0[x],0,0);
  }
}

int main() {
  int a,b;

  for(a=0;a<1000;a++) {
    b = a;
    d0[a] = b%10; b/=10;
    d1[a] = b%10; b/=10;
    d2[a] = b%10; b/=10;
    d21[a] = 10*d2[a] + d1[a];
  }

  for(a=0;a<n;a++) p[a]=a;
  for(a=0;a<n;a++) used[a]=0;
  i=0;j=0;

  while(1) {
    if(p[n-1]) {
      t=p[n-1];lt=1;
      if(!(t%3)) recurse(0);
      t=p[n-1]*10+p[n-2];lt=2;
      if(!(t%3)) recurse(0);
    }
    if(!nextperm(n,p,1)) break;
  }
}