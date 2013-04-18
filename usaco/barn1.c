#include <stdio.h>
#include <stdlib.h>

/*
ID: guidoma1
LANG: C
TASK: barn1
*/

int comp(const void* X,const void* Y)
{
	int x,y;
	x = *((int*)X);
	y = *((int*)Y);
	
	if(x==y) return 0;
	if(x>y) return 1;
	return -1;
}
		

int main()
{
	FILE *in,*out;
	int maxboards;
	int am_stalls;
	int am_cows;
	int cows[201];
	int i;
	int t;
	int covered;
	int min,max;
	
	in = fopen("barn1.in","r");
	fscanf(in,"%i %i %i",&maxboards,&am_stalls,&am_cows);

	for(i=0;i<am_cows;++i)
	{
		fscanf(in,"%i",&t);
		cows[i] = t;
		if(i==0)
			min = max = t;
		
		if(t<min) min = t;
		if(t>max) max = t;
		
	}
	
	covered = max-min+1;
	
	fclose(in);

	qsort(cows,am_cows,sizeof(int),comp);
		
	for(i=0;i<am_cows-1;++i)
		cows[i] = cows[i+1] - cows[i] - 1;
	
	qsort(cows,am_cows-1,sizeof(int),comp);
	
	for(i=0;i<maxboards-1 && i<am_cows-1;++i)
	{
		covered-=cows[am_cows-2-i];
	}
	
	out = fopen("barn1.out","w");
	fprintf(out,"%i\n",covered);
	fclose(out);
	

	
	
	return 0;
}
	
	
