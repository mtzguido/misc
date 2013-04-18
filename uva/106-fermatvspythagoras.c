#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int x, int y)
{
	int t;
	
	while(y>0)
	{
		t = x%y;
		x = y;
		y = t;
	}
	
	return x;
}

static unsigned intsqrt(unsigned long val) {
	    unsigned long temp, g=0, b = 0x8000, bshft = 15;
	    do {
	        if (val >= (temp = (((g << 1) + b)<<bshft--))) {
	           g += b;
	           val -= temp;
	        }
	    } while (b >>= 1);
	    return g;
	}

int main()
{
	int cant;
	int N[1000];
	int C[1000];
	int max = 0;
	int m,n;
	int k;
	int i,j;
	int* ap;
	int l1,l2,l3;
	int AA,BB,CC;
	int AAk,BBk,CCk;
		
	cant = 0;
	while(!feof(stdin))
	{	
		scanf("%i",&N[cant]);
		if(N[cant] == 0) break;
		if(N[cant] > max) max = N[cant];
		C[cant++] = 0;
	}
	
	ap = (int*)malloc((max+1) * sizeof(int));
	memset(ap,127,max*4 + 4);
	
	l3 = intsqrt(max);
	for(n=1;n<=l3;++n)
	{
		l1 = intsqrt(max-n*n);
		l2 = max/(2*n);
		l1 = l1<l2?l1:l2;
		
		for(m=n+1;m<=l1;++m)
		{	
			if(((m&1)==0 || (n&1)==0) && gcd(m,n) == 1)
			{
				BB = m*n<<1;
				CC = m-n;
				CC = CC*CC;
				CC += BB;
				AA = CC - ((n*n)<<1);

				for(k=0;k<cant;++k)
					if(CC <= N[k])
						C[k]++;
			
				for(AAk=AA,BBk=BB,CCk=CC;CCk<=max;AAk+=AA,BBk+=BB,CCk+=CC)
				{
					if(ap[AAk] > CCk) ap[AAk] = CCk;
					if(ap[BBk] > CCk) ap[BBk] = CCk;
					if(ap[CCk] > CCk) ap[CCk] = CCk;
				}
			}
		}
	}
	
	for(k=0;k<cant;++k)
	{
		j=0;
		for(i=1;i<=N[k];++i)
			if(ap[i] > N[k])
				j++;
		
		printf("%i %i\n",C[k],j);
	}
	
	return 0;
}
