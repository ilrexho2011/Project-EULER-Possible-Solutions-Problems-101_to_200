class Program {
		private int min;
		private int length;
		private long[,] mem;
		private int max;

		public Program() {
			min=2;
			max=4;
			length=50;
			mem=new long[length,max-min+1];
			for (int i=0;i<mem.GetLength(0);i++) {
				for (int j=0;j<mem.GetLength(1);j++) {
					mem[i,j]=-1;
				}					
			}
		}

		private long Solve(int start, int dim) {			
			if (length-start<dim) {
				return 0;
			}
			long solutions=0; // empty solution
			if (mem[length-start-1, dim-min]!=-1) return mem[length-start-1, dim-min];
			for (int pos=start;pos+dim<=length;pos++) {
				solutions+=1+Solve(pos+dim,dim); 
			}

			
			if (mem[length-start-1, dim-min]==-1) {
				mem[length-start-1, dim-min]=solutions;
			}
			
			return solutions;
		}

		private void Seek() {
			long sol=0;
			for (int i=min; i<=max; i++) {
				sol+=Solve(0,i);				
			}
			Console.WriteLine(sol);
			
		}

		static void Main(string[] args) {
			Program p=new Program();
			p.Seek();


			Console.ReadLine();
		}
	}