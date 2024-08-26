class Program {

		private int min;
		private int length;
		private long[] mem;

		public Program() {
			min=50;
			length=50;
			mem=new long[length];
			for (int i=0;i<mem.Length;i++) {
				mem[i]=-1;
			}
		}

		private long Solve(int start) {
			long solutions=1; // empty solution
			if (length-start<min) {
				return solutions;
			}
			if (mem[length-start-1]!=-1) return mem[length-start-1];
			for (int dim=min;dim<=length-start;dim++) {
				for (int pos=start;pos+dim<=length;pos++) {
					solutions+=Solve(pos+dim+1);
				}
			}

			if (mem[length-start-1]==-1) {
				mem[length-start-1]=solutions;
			}
			return solutions;
		}

		private void Seek() {
			for (int k=51;k<200;k++) {
				length=k;
				mem=new long[length];
				for (int i=0;i<mem.Length;i++) {
					mem[i]=-1;
				}
				long sol=Solve(0);
				if (sol>1000000) {
					Console.WriteLine(k);
					break;
				}
			}
		}

		static void Main(string[] args) {
			Program p=new Program();
			p.Seek();
			
			
			Console.ReadLine();
		}
	}