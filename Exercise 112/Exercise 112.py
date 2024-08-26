class Program {

		private static bool IsAsc(long n) {
			if (n<10) return true;
			int last=(int)(n%10);
			n/=10;
			while (n>=1) {
				if (n%10<=last) {
					last=(int)(n%10);
					n/=10;
				} else {
					return false;
				}
			}
			return true;
		}

		private static bool IsDesc(long n) {
			if (n<10) return true;
			int last=(int)(n%10);
			n/=10;
			while (n>=1) {
				if (n%10>=last) {
					last=(int)(n%10);
					n/=10;
				} else {
					return false;
				}
			}
			return true;
		}

		private static bool IsBounce(long n) {
			if (IsAsc(n)) return false;
			if (IsDesc(n)) return false;
			return true;
		}

		static void Main(string[] args) {

			int bouncing=0;
			int tot=0;

			for (int i=1;;i++) {
				if (IsBounce(i)) {
					bouncing++;
				}
				tot++;
				if (bouncing*100>=tot*99) {
					Console.WriteLine(i+" -> "+(100*(double)bouncing/(double)tot)+"%");
					break;
				}
			}

			Console.WriteLine("Done");
			Console.ReadLine();
		}