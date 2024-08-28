namespace problem123 {
	class Program {

		private int[] p;

		private void Run() { 
			int dim=40000;
			p=Zm.GeneratePrimes(dim);

			long target=(long)Math.Pow(10,10);

			long time=Environment.TickCount;

			for (long j=1;j<dim;j++) {
				if (2*(j+1)*p[j]>target) { 
					Console.WriteLine("N is {0}",(j+1));
					break;
				}
			}

			time=Environment.TickCount-time;
			Console.WriteLine("Time elapsed : {0} msecs",time);

		}

		static void Main(string[] args) {
			Program p=new Program();
			p.Run();
			Console.ReadLine();
		}
	}
}