class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Enter Limit:");
            int l = Int32.Parse(Console.ReadLine());

            while (l > 0)
            {
                var sw = Stopwatch.StartNew();
                Console.WriteLine("Solution is {0}",solve(l));
                sw.Stop();

                Console.WriteLine(sw.Elapsed);

                Console.WriteLine("Enter Limit:");
                l = Int32.Parse(Console.ReadLine());
            }

            Console.ReadLine();
        }

        static long solve(int limit)
        {          
            return  Enumerable.Range(3, limit - 2).Select(i => maxR(i)).Sum();
        }
       
        static long maxR(int a)
        {
            if (a % 2 == 1)
                return a * a - a;
            else
                return a * a - 2 * a;
        }
    }