namespace problem103
{
	class Class1
	{
		private static bool Share(int n, int m, int dim) {
			for (int i=0; i<dim; i++) {
				if ((n&1)==1 && (m&1)==1) return true;
				n>>=1;
				m>>=1;
			}
			return false;
		}

		private static int HasMoreElements(int n, int m, int dim) {
			int nn=0;
			int nm=0;
			for (int i=0; i<dim; i++) {
				if ((n&1)==1) nn++;
				if ((m&1)==1) nm++;
				n>>=1;
				m>>=1;
			}
			if (nn>nm) return 1;
			else if (nn==nm) return 0;
			else return -1;			
		}

		private static int BinSum(int[] a, int m) {
			int sum=0;
			for (int i=0; i<a.Length; i++) {
				if ((m&1)==1) {
					sum+=a[i];
				}
				m>>=1;
			}
			return sum;
		}

		private static int TotSum(int[] a) {
			int sum=0;
			for (int i=0; i<a.Length; i++) {
				sum+=a[i];
			}
			return sum;
		}

		private static string PrintVect(int[] a) {
			string s="";
			for (int i=0; i<a.Length; i++) {
				s+=a[i];
			}		
			return s;
		}

		private static int[] MakeSum(int[] a) {
			int[] b=new int[(int)Math.Pow(2,a.Length)];
			for (int i=0; i<b.Length; i++) {
				b[i]=BinSum(a,i);
			}
			return b;
		}

		private static int[] UpdateGap(int[] a, int min, int max) {
			for (int i=a.Length-1; i>=0; i--) {
				if (a[i]==max) continue;
				else {
					for (int j=i+1; j<a.Length; j++) {
						a[j]=min;
					}
					a[i]++;
					return a;
				}
			}
			return a;
		}

		private static bool Verify(int[] a, int dim) {
			for (int i=0; i<a.Length; i++) {
				if (Array.IndexOf(a,a[i],i+1)!=-1) return false;
			}
			for (int i=0; i<a.Length; i++) {
				for (int j=i+1; j<a.Length; j++) {
					if (Share(i,j,dim)==false) {						
						if (a[i]==a[j]) return false;
						if (a[i]<a[j] && HasMoreElements(i,j,dim)==1) return false;
						if (a[j]<a[i] && HasMoreElements(i,j,dim)==-1) return false;
					}
				}
			}
			return true;
		}



		[STAThread]
		static void Main(string[] args)
		{
			
			// base vector
			int x=20;
			int[] a=new int[]{x,x+11,x+18,x+19,x+20,x+22,x+25};
			int[] t=new int[a.Length];
			int dim=a.Length;

			int[] s=new int[1]; // sum vector

			int[] c=new int[7]; // gap vector
			int min=-3; 
			int max=3;
			for (int i=0; i<c.Length; i++) {
				c[i]=min;
			}

			int tsum=0;
			int tmin=int.MaxValue;

			for (int i=0; i<(int)Math.Pow(max-min+1,dim); i++) {				
				for (int j=0; j<a.Length; j++) {
					t[j]=a[j]+c[j];					
				}
				tsum=TotSum(t);

				if (tsum<=tmin) {
					Array.Sort(t);
					s=MakeSum(t);
				

					if (Verify(s,dim)) {
						tmin=tsum;
						Console.WriteLine("Vector "+i);
						for (int j=0; j<a.Length; j++) {						
							Console.Write(t[j]+" ");
						}
						Console.WriteLine("\nVerification: true");
						Console.WriteLine("Sum="+tsum);
						Console.WriteLine("Solution="+PrintVect(t));

					}
				}			
					
				c=UpdateGap(c,min,max);
			}
			
			Console.WriteLine("Done");
			Console.ReadLine();
		}
	}
}