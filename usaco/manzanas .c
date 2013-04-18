#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int x,y;
} xy;

xy manzanas[2001];
int r[2001];

int N;

int max(int x,int y)
{
	return (x>y)?x:y;
}

int max_manzanas(int p)
{
	int m = 0;
	int i;
	
	if(r[p] != -1) return r[p];
	
	for(i=0;i<N;++i)
		if(manzanas[i].y>manzanas[p].y && abs(manzanas[i].y-manzanas[p].y)>=abs(manzanas[i].x-manzanas[p].x))
			m = max(m,max_manzanas(i) + 1);
			
	r[p] = m;
	return m;
}

int main()
{
	int i;
	
	scanf("%i",&N);
	for(i=0;i<N;++i)
	{
		r[i] = -1;
		scanf("%i %i",&manzanas[i].x,&manzanas[i].y);
	}
	
	r[2000] = -1;
	manzanas[2000].x = manzanas[2000].y = 0;
	
	printf("%i\n",max_manzanas(2000));
	
	return 0;
}
