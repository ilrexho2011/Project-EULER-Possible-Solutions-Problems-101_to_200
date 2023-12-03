#include <bits/stdc++.h>
#define MAXN 1000000
#define pb push_back
#define LL long long
#define ULL unsigned long long
using namespace std;

//------------------------------------------------------------------------------------------------------


LL dp[56][8];

//dp[i][0] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2] + dp[i-1][3]
//dp[i][1] = dp[i-1][0]
//dp[i][2] = dp[i-1][1]
//dp[i][3] = dp[i-1][2]
//x_i = x_{i-1} + x_{i-2} + x_{i-3} + x_{i-4}
const int mod = 1000000007;
struct Mat
{
    LL a[4][4];
    Mat()
    {
        memset(a, 0, sizeof(a));
    }
    Mat operator* (Mat m)
    {
        Mat r;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                for (int k = 0; k < 4; ++k)
                {
                    r.a[i][j] = (r.a[i][j] + a[i][k] * m.a[k][j] % mod) % mod;
                }
            }
        }
        return r;
    }
};
ostream& operator<< (ostream& out, Mat m)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            out << m.a[i][j] << " ";
        }
        out << endl;
    }
    return out;
}
Mat qp(Mat m, LL n)
{
    Mat ret;
    for (int i = 0; i < 4; ++i)
    {
        ret.a[i][i] = 1;
    }
    while (n)
    {
        if (n & 1)
            ret = ret * m;
        m = m * m;
        n >>= 1;
    }
    return ret;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        LL n;
        cin >> n;
        if (n == 1)
        {
            cout << 1 << endl;
            continue;
        }
        else if (n == 2)
        {
            cout << 2 << endl;
            continue;
        }
        Mat m;
        m.a[0][0] = m.a[0][1] = m.a[0][2] = m.a[0][3] = m.a[1][0] = m.a[2][1] = m.a[3][2] = 1;
        Mat res = qp(m, n - 3);
        cout << (4 * res.a[0][0] + 2 * res.a[0][1] + res.a[0][2] + res.a[0][3]) % mod << endl;
    }
    return 0;
}