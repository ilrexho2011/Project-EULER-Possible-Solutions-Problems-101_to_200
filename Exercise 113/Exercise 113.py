using System;
using System.Collections.Generic;
using System.Text;

namespace Problem113
{
    class Problem113
    {
        struct Arg
        {
            public Arg(int Digits, int StartDigit)
            {
                _Digits = Digits;
                _StartDigit = StartDigit;
            }

            public int _Digits;
            public int _StartDigit;
        };

        public Problem113()
        {
            _Solution = BouncyNumbers(100);
        }

        /*
            Number of increasing numbers having NumOfDigits digits and which first digit is StartDigit
            Inc(NumOfDigits,StartDigit) = Sum Inc(NumOfDigits - 1,i) where i in[StartDigit ... 9]
         */
        private ulong Inc(Arg arg)
        {
            ulong Result = 0;

            if (arg._Digits == 1)
                /* if number of digits is 1 than there is 1 increasing number 
                 * beginning from digit _StartDigit. 
                 */
                return 1;

            if (_CacheInc.ContainsKey(arg))
                return _CacheInc[arg];

            for (int i = arg._StartDigit; i <= 9; ++i)
                Result += Inc(new Arg(arg._Digits - 1, i));

            _CacheInc.Add(arg,Result);

            return Result;
        }

        /*
            Number of increasing numbers having at most NumOfDigits digits
            IncreasingNumbers(NumOfDigits) = Sum Inc(NumOfDigits,i) where i in[1 ... 9]
        */
        private ulong IncreasingNumbers(int NumOfDigits)
        {
            ulong Result = 0;

            for (int i = 1; i <= 9; ++i)
                Result += Inc(new Arg(NumOfDigits, i));

            return Result;
        }

        /*
            Number of decreasing numbers having at most NumOfDigits digits
            DecreasingNumbers(NumOfDigits) = Sum IncreasingNumbers(i) where i in[1 ... NumOfDigits]
        */
        private ulong DecreasingNumbers(int NumOfDigits)
        {
            ulong Result = 0;

            for (int i = 1; i <= NumOfDigits; ++i)
                Result += IncreasingNumbers(i);

            return Result;
        }

        private ulong BouncyNumbers(int NumOfDigits)
        {
            ulong Result = 0;

            for (int i = 1; i <= NumOfDigits; ++i)
                Result += IncreasingNumbers(i) + DecreasingNumbers(i) - 9;

            return Result;
        }

        private Dictionary<Arg, ulong> _CacheInc = new Dictionary<Arg, ulong>();

        public ulong Solution { get { return _Solution; } }

        private ulong _Solution = 0;
    };

    class Program
    {
        static void Main(string[] args)
        {
            Problem113 p113 = new Problem113();

            Console.WriteLine(p113.Solution);
        }
    }
}