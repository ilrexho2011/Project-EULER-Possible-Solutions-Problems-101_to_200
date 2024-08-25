using System;

namespace problem109
{
	class Class1
	{
		
		private static int Check(int[] score, int max) {
			int startd=20;
			int endd=40;
			int counter=0;
			// one dart
			for (int i=startd; i<endd; i++) {
				if (score[i]==max) {
					//Console.WriteLine("single "+DebugMe(score,i)+" "+score[i]);
					counter++;
				}
			}

			// one dart with bull
			if (max==50) counter++;

			// two darts
			for (int i=0; i<score.Length; i++) {
				for (int j=startd; j<endd; j++) {
					if (score[i]+score[j]==max) {
						//Console.WriteLine("double "+DebugMe(score,i)+" "+DebugMe(score,j)+" "+score[i]+" "+score[j]);
						counter++;
					}
				}
			}

			// two darts with bull
			for (int i=0; i<score.Length; i++) {
				if (score[i]+50==max) {
					//Console.WriteLine("single "+DebugMe(score,i)+" "+score[i]);
					counter++;
				}
			}

			

			// three darts
			int treblea=0;
			int trebleb=0;
			for (int i=0; i<score.Length; i++) {
				for (int j=0; j<score.Length; j++) {
					for (int k=startd; k<endd; k++) {
						if (score[i]+score[j]+score[k]==max) {
							//Console.WriteLine("treble "+DebugMe(score,i)+" "+DebugMe(score,j)+" "+DebugMe(score,k)+" "+score[i]+" "+score[j]+" "+score[k]);
							if (i==j) {
								treblea++;
							} else {
								trebleb++;
							}
						}
					}
				}
			}

			// three darts with bull
			for (int i=0; i<score.Length; i++) {
				for (int j=0; j<score.Length; j++) {
					if (score[i]+score[j]+50==max) {
						//Console.WriteLine("double "+DebugMe(score,i)+" "+DebugMe(score,j)+" "+score[i]+" "+score[j]);
						if (i==j) {
							treblea++;
						} else {
							trebleb++;
						}
					}
				}
			}

			counter+=treblea+trebleb/2;

			return counter;
		}
		

		[STAThread]
		static void Main(string[] args)
		{
			long time=Environment.TickCount;
			int max=99;
			int[] score=new int[62];
			score[60]=25;
			score[61]=50;
			for (int i=1; i<21; i++) {
				score[i-1]=i;
				score[20+i-1]=2*i;
				score[40+i-1]=3*i;
            }
			
			
			int tot=0;
			for (int i=1; i<=max; i++) {
				tot+=Check(score,i);
			}

			Console.WriteLine("Solution: "+tot);
			Console.WriteLine("Time elapsed = "+(Environment.TickCount-time)+" msecs");


			Console.ReadLine();
		}
	}
}