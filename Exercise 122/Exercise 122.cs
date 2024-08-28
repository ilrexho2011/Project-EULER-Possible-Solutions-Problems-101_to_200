namespace problem122 {
	class Program {

		private int[] w;
		private int[] t;
		private int dim;
		private long time;

		public Program() { 
			dim=200;
			dim++;
			w=new int[dim];
			t=new int[dim];
		}

		private void Parse(int start, int place) {

			if (place==dim) return;

			for (int i=start;i>0;i--) { 
				t[place]=t[place-1]+t[i];
				if (Check(place)) {
					Parse(start+1, place+1);
				} 
			}

		}

		private bool Check(int place) { 
			int num=t[place];
			if (num>dim-1) return false;
			if (w[num]>=place-1) { 
				w[num]=place-1;
				return true;
			}
			return false;
		}

		private void Run() { 

			for (int i=0;i<w.Length;i++) { 
				w[i]=int.MaxValue;
			}

			t[1]=1;
			w[1]=0;

			time=Environment.TickCount;
			Parse(1,2);
			time=Environment.TickCount-time;

			for (int i=0;i<w.Length;i++) { 
				Console.WriteLine("w[{0}]={1}",i,w[i]);
			}

			int sum=0;

			for (int i=1;i<dim;i++) {
				sum+=w[i];
			}



			Console.WriteLine("Sum={0}, time elapsed={1} msecs",sum, time);
		}
		
		static void Main(string[] args) {
			Program p=new Program();
			p.Run();

			Console.ReadLine();
		}
	}
}