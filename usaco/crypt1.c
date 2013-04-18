/*
ID: guidoma1
LANG: C
TASK: crypt1
*/

#include <stdio.h>
#include <stdlib.h>

int n;
int digs[10];

int isdig(int x)
{
	int i;
	
	for(i=0;i<n;++i)
		if(digs[i] == x)
			return 1;
			
	return 0;
}

int validnum(int x)
{
	if(x==0) return 0;
	while(x>0)
	{
		if(!isdig(x%10))
			return 0;
			
		x/=10;
	}
	
	return 1;
}

int valid(int d1, int d2, int d3, int d4, int d5)
{
	int n1,n2;
	
	n1 = 100*digs[d1] + 10*digs[d2] + digs[d3];
	n2 = 10*digs[d4] + digs[d5];
	
	if(validnum(n1*n2) && validnum(n1*digs[d4]) && validnum(n1*digs[d5]) && n1*digs[d4] <1000 && n1*digs[d5]<1000 && n1*n2<10000)
	{
		printf("valid: %i %i\n",n1,n2);
		return 1;
	}
	else
		return 0;	
}

int main()
{
	int i;
	int count = 0;
	int d1,d2,d3,d4,d5;

	FILE *in,*out;
	
	in = fopen("crypt1.in","r");
	out = fopen("crypt1.out","w");
	
	fscanf(in,"%i",&n);
	
	for(i=0;i<n;++i)
		fscanf(in,"%i",&digs[i]);
		
	for(d1=0;d1<n;++d1)
		for(d2=0;d2<n;++d2)
			for(d3=0;d3<n;++d3)
				for(d4=0;d4<n;++d4)
					for(d5=0;d5<n;++d5)
						if(valid(d1,d2,d3,d4,d5))
							count++;
							
							
	fprintf(out,"%i\n",count);

	return 0;
}
	
