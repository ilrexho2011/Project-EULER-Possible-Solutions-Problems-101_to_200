import java.util.*;

public class P182 {
    static long gcd(long x, long y) { return x==0?y:gcd(y%x, x); }
    static long lcm(long x, long y) { return x*y/gcd(x,y); }
    static long pow(long b, long e, long m) {
        if(e==0) return 1%m;
        else if(e%2==0) return pow((b*b)%m, e/2, m);
        else return (b*pow(b,e-1,m))%m;
    }

    static long order(long m, long p) {
        if(m==0) return 1;
        long phi = p-1;
        for(int ans=1; ans*2<=phi; ans++)
            if(phi%ans==0 && pow(m, ans, p)==1)
                return ans;
        return phi;
    }
    public static void main(String[] args) {
        long p = 1009;
        long q = 3643;
        long n = p*q;
        long phi = (p-1)*(q-1);

        long[] E = new long[(int)phi];

        for(int m=0; m<=n-1; m++) {
            long ord_p = order(m, p);
            long ord_q = order(m, q);
            long lcm = lcm(ord_p, ord_q);
            for(long i=1; i<E.length; i+=lcm)
                E[(int)i]++;
            if(m%100==0) System.out.println(m+" "+ord_p+" "+ord_q);
        }

        long best = n;
        for(int i=2; i<E.length; i++) {
            if(gcd(i,phi)==1)
                best = Math.min(best, E[i]);
        }
        System.out.println(best);

        long sum = 0;
        for(int i=2; i<E.length; i++) {
            if(gcd(i,phi)==1 && E[i]==best)
                sum += i;
        }
        System.out.println(sum);
    }
}