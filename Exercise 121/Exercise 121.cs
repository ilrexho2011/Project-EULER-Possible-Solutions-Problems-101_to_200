namespace problem121 {
	class Program {

		int[] n;
		int[] d;

		private long Scan(int dim) { 
			
			int t;
			int index;
			long prob;
			int ones;
			long p=0;

			for (int i=0;i<Math.Pow(2,dim);i++) { 
				t=i;
				ones=0;
				index=dim-1;
				prob=1;

				while (index>=0) {
					if ((t&0x01)==1) {
						ones++;
					} else { 
						prob*=n[index];
					}
					index--;
					t>>=1;
				}

				if (ones>dim/2) { 
					p+=prob;
				}
			} 

			return p;

		}

		private void Run() { 
			long time=Environment.TickCount;

			int dim=15;
			n=new int[dim];
			d=new int[dim];

			for (int i=0;i<n.Length;i++) { 
				n[i]=1+i;
				d[i]=2+i;
			}

			long den=1;
			for (int i=0;i<d.Length;i++) { 
				den*=(long)d[i];
			}
			
			long num=Scan(dim);
			
			Console.WriteLine(den/num);

			Console.WriteLine("Time elapsed : {0} msecs", (Environment.TickCount-time));

			
		}

		static void Main(string[] args) {
			Program p=new Program();
			p.Run();
			Console.WriteLine("Done");
			Console.ReadLine();
		}
	}
}