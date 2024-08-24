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

		private static int[] MakeSum(int[] a) {
			int[] b=new int[(int)Math.Pow(2,a.Length)];
			for (int i=0; i<b.Length; i++) {
				b[i]=BinSum(a,i);
			}
			return b;
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
			StreamReader sr=new StreamReader("..\\..\\sets.txt");
			StringCollection sc=new StringCollection();
			string s="";
			while ((s=sr.ReadLine())!=null) {
				sc.Add(s.Trim());
			}
			sr.Close();
			
			long finalSum=0;
			foreach (string str in sc) {
				string[] tmp=str.Split(',');
				int[] a=new int[tmp.Length];
				for (int i=0; i<a.Length; i++) {
					a[i]=int.Parse(tmp[i]);
				}
				Array.Sort(a);
				int dim=a.Length;
				int[] sum=MakeSum(a);
				if (Verify(sum,dim)) {
					finalSum+=TotSum(a);
				}
				Console.WriteLine("Sum is: "+finalSum);
			}

			Console.WriteLine("Final Sum is: "+finalSum);
			Console.WriteLine("Done");
			Console.ReadLine();
		}
	}