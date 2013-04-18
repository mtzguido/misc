#include <stdio.h>
#define MAX 200

int C[MAX+1][MAX+1];
int s[MAX+1][MAX+1];
int p[MAX+1];

int mincost(int i, int f)
{
	int k;
	int m;
	int t1,t2;

	if(C[i][f] != -1) return C[i][f];
	
	if(i==f)
	{
		//printf("C_%i..%i = 0\n",i,f); 
		C[i][f] = 0;
		return 0;
	} else {

		m = mincost(i,i) + mincost(i+1,f) + p[i-1]*p[i]*p[f];
		s[i][f] = i;
		for(k=i+1;k<f;++k)
		{
		 	t1 = mincost(i,k);
			t2 = mincost(k+1,f);
			if(t1 + t2 + p[i-1]*p[k]*p[f] < m)	
			{
				m = t1 + t2 + p[i-1]*p[k]*p[f];
				s[i][f] = k;
			}	
		}
		//printf("C_%i..%i = %i\n",i,f,m);
		C[i][f] = m;
		return m;
	}
}

int print(int i,int f)
{
	if(i==f)
		printf("%i",i);
	else
	{
		putchar('(');
		print(i,s[i][f]);
		printf("x");
		print(s[i][f]+1,f);
		putchar(')');
	}
}

int main()
{
	int n;
	int i,j;

	scanf("%i",&n);

	if (n > MAX)
		return;

	for(i=0;i<=n;++i)
		scanf("%i",&p[i]);
	
	for(i=0;i<=MAX;++i)
		for(j=0;j<=MAX;++j)
			C[i][j] = -1;

	i = mincost(1,n);

	print(1,n); putchar('\n');
	printf("%i\n",i);
			

	return 0;
}
