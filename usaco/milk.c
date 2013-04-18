#include <stdio.h>

/*
ID: guidoma1
LANG: C
TASK: milk
*/

int main()
{
	int rem;
	int spent;
	int N;
	int amount[5000];
	int price[5000];
	FILE *in,*out;
	int i;
	int mpos;
	
	in = fopen("milk.in","r");
	fscanf(in,"%i %i",&rem,&N);
	
	for(i=0;i<N;++i)
		fscanf(in,"%i %i",&price[i],&amount[i]);
	
	fclose(in);
	
	spent = 0;
	while(rem>0)
	{
		mpos = 0;
		
		for(i=0;i<N;++i)
			if(price[i] < price[mpos])
				mpos = i;
		
		if(amount[mpos] <= rem)
		{
			rem -= amount[mpos];
			spent += price[mpos]*amount[mpos];
			price[mpos] = 1001;
		} else {
			spent+= rem * price[mpos];
			rem = 0;
		}
	}
	
	out = fopen("milk.out","w");
	fprintf(out,"%i\n",spent);
	fclose(out);
	
	return 0;
}
	
