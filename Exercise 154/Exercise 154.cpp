#include<iostream>

using namespace std;

int* p2;
int* p5;

inline int count(int n, int p){
        int c = 0;
        while(n){
                c += n;
                n /= p;
        }
        return c;
}
inline int trinomCount(int n, int i, int j, int p){
        switch(p){
                case 2: return p2[n] - p2[i] - p2[j] - p2[n-i-j];
                case 5: return p5[n] - p5[i] - p5[j] - p5[n-i-j];
        }
}

const int N = 200000;

int main(){
        p2 = new int [N+1];
        p5 = new int [N+1];

        for (int i = 0; i <= N ; i++){
                p2[i] = count(i, 2);
                p5[i] = count(i, 5);
        }


        long long c = 0;
        for (int i = 0; i <= N; i++){
                for (int j = i; j >= 0; j--){
                        if (N < i + j) continue;
                        if (N - i > 2*j) break;
                        if ((trinomCount(N, i, j, 5) >= 12) and (trinomCount(N, i, j, 2) >= 12)){
                                if (i > j and 2*j > N - i) c += 6;
                                if (i == j and 3*i > N) c += 3;
                                if (i > j and 2*j == N - i) c += 3;
                        }

                                
                }
                if (i%2000 == 0)cerr << i /2000;
        }

        cerr << endl << c << endl;

}