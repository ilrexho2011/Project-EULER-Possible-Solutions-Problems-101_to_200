static long SumOfSquares(long n){
            return (n*(n+1)*(2*n+1)/6);
        }

        static bool isPalindromic(long n)
        {
            var s = n.ToString().ToCharArray();
            int l = s.Length;
            for (int i = 0; i < l / 2; i++)
            {
                if (s[i] != s[l - i - 1]) return false;
            }
            return true;         
        }

        static int findLimit(int limit)
        {
            int current = 1;
            int prev = 1;
            int x = 1;
            long sum = current + prev;
            while (sum <= limit)
            {
                x++;
                prev = current;
                current = x * x;
                sum = current + prev;
            }

            return (int)Math.Sqrt(current);
        }

        static long solve(int limit)
        {

            int lm = findLimit(limit);
            
            long sum = 0;
            var palindromeSquares = new HashSet<long>();
            
            var lockobj = new object();            
            Parallel.For(2,lm+1,
                n =>
                {
                    long sn = SumOfSquares(n);
                    for (int i = 0; i <= n - 2; i++)
                    {
                        long s = sn - SumOfSquares(i);
                        if (s >= limit) 
                            continue;
                        if (isPalindromic(s))
                        {
                            lock (lockobj)
                            {
                                palindromeSquares.Add(s);
                            }
                        }
                    }
                });

            return palindromeSquares.Sum();
        }