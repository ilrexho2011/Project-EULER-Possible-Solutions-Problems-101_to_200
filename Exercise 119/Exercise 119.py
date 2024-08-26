namespace problem119 {
	class Program {


		private bool Check(int n, int exp) { 
			long t=(long)Math.Pow(n,exp);
			long sum=0;
			while (t>0) { 
				sum+=(int)(t%10);
				t/=10;
			}

			return (sum==n);
		}


		private void Run() {
			List<MagicNum> l=new List<MagicNum>();
			long[] res;

			for (int i=2;i<100;i++) {
				for (int e=2;e<(int)Math.Log(long.MaxValue, i);e++) {
					if (Check(i, e)) { 
						MagicNum mn=new MagicNum();
						mn.basen=i;
						mn.exp=e;
						mn.n=(long)Math.Pow(i,e);
						l.Add(mn);
					}
				}
			}

			res=new long[l.Count];

			for (int i=0;i<l.Count;i++) { 
				res[i]=l[i].n;
				//Console.WriteLine(l[i]);
			}

			Array.Sort(res);

			for (int i=0;i<l.Count;i++) {
				Console.WriteLine((i+1)+" -> "+res[i]);
			}
		}


		static void Main(string[] args) {
			Program p=new Program();
			p.Run();

			Console.WriteLine("Done");
			Console.ReadLine();
		}
				
	}

	class MagicNum { 
		public long n;
		public int exp;
		public int basen;

		public override string ToString() {
			return basen+"^"+exp+" = "+n;
		}
	}
}