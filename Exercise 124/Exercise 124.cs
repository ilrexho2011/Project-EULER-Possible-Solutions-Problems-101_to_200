namespace problem124 {
	class Program {

		private long Rad(int n) {
			if (n==1) return 1L;
			Zm.Factorize(n);
			long rad=1;
			for (int i=0;i<Zm.Count;i++) { 
				rad*=Zm.Fact[i];
			}
			return rad;
		}

		private void Run() {
			int dim=100000;
			int target=10000;

			long[] rad=new long[dim];

			for (int i=1;i<dim;i++) { 
				rad[i]=Rad(i);
			}

			long[] tmp=new long[dim];
			Array.Copy(rad,tmp,rad.Length);

			Array.Sort(tmp);
			long t=tmp[target-1];

			List<long> num=new List<long>();

			for (int i=1;i<dim;i++) {
				if (rad[i]==t) { 
					num.Add(i);
				}
			}

			int index=Array.IndexOf(tmp, t);
			int gap=target-index-1;

			tmp=num.ToArray();
			Array.Sort(tmp);

			Console.WriteLine("Number is: {0}", tmp[gap]);


		}


		static void Main(string[] args) {
			Program p=new Program();
			p.Run();
			Console.ReadLine();
		}
	}
}