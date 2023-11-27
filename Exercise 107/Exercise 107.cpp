
#define N 40
int x[N][N] /* VALUES OMMITED HERE '-' replaced by "-1" */

int y[N*N][3];
int z[N];

int com(const void *a,const void *b)
{
	return *(int*)a-*(int*)b;
}

int union_find(int i)
{
	if (z[i]==i) return i;
	return z[i]=u(z[i]);
}

int main()
{
	int i,j,n,s;
	n=s=0;
	for (i=0;i<N;++i) for (j=i;j<N;++j) if (x[i][j]!=-1)
	{
		y[n][0]=x[i][j];
		y[n][1]=i;
		y[n++][2]=j;
		s+=x[i][j];
	}
	qsort(y,n,sizeof(y[0]),com);
	for (i=0;i<40;++i) z[i]=i;
	for (i=j=0;j<39;++i)
	{
		if (union_find(y[i][1])!=union_find(y[i][2]))
		{
			++j;
			s-=y[i][0];
			z[union_find(y[i][1])]=union_find(y[i][2]);
		}
	}
	printf("%d\n",s);
	return 0;
}