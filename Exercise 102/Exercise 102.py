namespace problem102
{
	class Class1
	{
		private static bool Check(Vert v1, Vert v2, Vert v3) {
			double[] a=new double[]{v1.theta,v2.theta,v3.theta};
			Array.Sort(a);			
			if (a[2]-a[1]>Math.PI) return false;
			if (a[1]-a[0]>Math.PI) return false;
			if (2*Math.PI-a[2]+a[0]>Math.PI) return false;
			return true;
		}
		

		[STAThread]
		static void Main(string[] args)
		{
			
			FileStream fs=new FileStream("..\\..\\triangles.txt", FileMode.Open,FileAccess.Read);
			StreamReader sr=new StreamReader(fs);
			StringCollection sc=new StringCollection();
			string c="";
			while ((c=sr.ReadLine())!=null) {
				sc.Add(c.Trim());			
			}
			sr.Close();
			fs.Close();			
			
			int count=0;
			bool chk=false;
			
			for (int i=0; i<sc.Count; i++) {
				string[] tmp=sc[i].Split(',');
				chk=Check(new Vert(double.Parse(tmp[0]),double.Parse(tmp[1])),new Vert(double.Parse(tmp[2]),double.Parse(tmp[3])),new Vert(double.Parse(tmp[4]),double.Parse(tmp[5])));
				if (chk) count++;				
            }

			Console.WriteLine(count);
						
			Console.ReadLine();
		}
	}

	class Vert {
		public double x=0;
		public double y=0;
		public double theta=0;

		public Vert(double x, double y) {
			this.x=x;
			this.y=y;
			if (this.x!=0) {
				this.theta=Math.Atan(this.y/this.x);
				if (x<0 && y>=0) this.theta+=Math.PI;
				if (x<0 && y<0) this.theta+=Math.PI;
				if (x>0 && y<0) this.theta+=2*Math.PI;
			} else {
				if (y==0) {
					this.theta=0;
				} else if (y>0) {
					this.theta=Math.PI;
				} else {
					this.theta=-1*Math.PI;
				}
			}
		}
	}
}