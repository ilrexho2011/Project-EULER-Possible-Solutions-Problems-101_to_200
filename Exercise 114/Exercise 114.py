class Program {

		private int min;
		private int length;
		private long[] mem;
		
		public Program() {
			min=3;
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

		


		static void Main(string[] args) {
			Program p=new Program();
			long sol=p.Solve(0);
			Console.WriteLine(sol);
			Console.ReadLine();
		}
		

	}