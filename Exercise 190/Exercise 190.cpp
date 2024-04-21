#include <cstdlib>
#include <iostream>

using namespace std;

const int NR = 10000;
const double DELTA = 0.00001;
double v[15];

int main(int argc, char *argv[])
{
    srand(time(0));    
    int sum=0;
    int n;
    for(int n=2;n<=15;n++){
      for(int i=0;i<n;i++) v[i]=1.0;
      double prod=1.0;    
      int nr=0;
      while(nr<NR){
        nr++;
        int i0=rand()%n;
        int i1=rand()%(n-1);
        if (i1>=i0) i1++;
  //cout<<i0<<","<<i1<<":";
        if  (v[i0]>DELTA) {
          double p=1.0;
          for(int i=0;i<n;i++) {
            if (i==i0) {
              for(int j=0;j<=i;j++) p*=(v[i0]-DELTA);
            } else if (i==i1) {
              for(int j=0;j<=i;j++) p*=(v[i1]+DELTA);
            } else {
              for(int j=0;j<=i;j++) p*=v[i];
            }
          }
  //cout<<p;
          if (p>prod) {
            v[i0]-=DELTA;
            v[i1]+=DELTA;
            prod=p;
            nr=0;                  
          }
        }
  //cout<<endl;
      }
      cout<<n<<":"<<prod<<":"<<endl;
      for(int i=0;i<n;i++) cout<<v[i]<<" ";
      cout<<endl;
      sum+=(int)prod;
    }
    cout<<"Res.:"<<sum<<endl;    
}