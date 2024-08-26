using System;
using System.Collections;

namespace Problem117
{
	class Task
	{
		public Task(int L,int dx)
		{
			_Length = L;
			_dxFromLeft = dx;
		}

		public override int GetHashCode()
		{
			return 9*_Length + _dxFromLeft;
		}

		public override bool Equals(Object O)
		{
			if(this.GetType() != O.GetType())
				return false;

			Task T = (Task)O;

			return (this._dxFromLeft == T._dxFromLeft)
				&&
				(this._Length == T._Length)
				;
		}

		private int _Length = 0;
		private int _NumOfChuncks = 0;
		private int _dxFromLeft = 0;
	};

	class Problem117
	{
		public Problem117()
		{
			_Solution += NumberOfWays(0);
		}

		protected long NumberOfWays(int dxFromLeft)
		{
			if(dxFromLeft == _Length)
				return 1;

			if(_Length < dxFromLeft)
				return 0;

			Task isSolved1 = new Task(1,dxFromLeft);
			Task isSolved2 = new Task(2,dxFromLeft);
			Task isSolved3 = new Task(3,dxFromLeft);
			Task isSolved4 = new Task(4,dxFromLeft);

			long Result = 0;

			if(m_Cache.ContainsKey(isSolved1))
				Result +=(long)m_Cache[isSolved1];
			else
			{
				long tmp = NumberOfWays(dxFromLeft + 1);;
				Result += tmp;

				m_Cache.Add(isSolved1,tmp);
			}

			if(m_Cache.ContainsKey(isSolved2))
				Result +=(long)m_Cache[isSolved2];
			else
			{
				long tmp = NumberOfWays(dxFromLeft + 2);;
				Result += tmp;

				m_Cache.Add(isSolved2,tmp);
			}

			if(m_Cache.ContainsKey(isSolved3))
				Result +=(long)m_Cache[isSolved3];
			else
			{
				long tmp = NumberOfWays(dxFromLeft + 3);;
				Result += tmp;

				m_Cache.Add(isSolved3,tmp);
			}

			if(m_Cache.ContainsKey(isSolved4))
				Result +=(long)m_Cache[isSolved4];
			else
			{
				long tmp = NumberOfWays(dxFromLeft + 4);;
				Result += tmp;

				m_Cache.Add(isSolved4,tmp);
			}

			return Result;
		}

		public long Solution
		{
			get{return _Solution;}
		}

		private Hashtable m_Cache = new Hashtable();

		private long _Length = 50;

		private long _Solution = 0;
	};

	class Class1
	{

		[STAThread]
		static void Main(string[] args)
		{
			Problem117 p117 = new Problem117();

			Console.WriteLine(p117.Solution);
		}
	}
}