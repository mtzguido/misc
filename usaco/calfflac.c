#include <stdio.h>

/*
ID: guidoma1
LANG: C
TASK: calfflac
*/

int maxlen = -1;
int maxlenreal = -1;
int maxpos = -1;

int isletter(char c)
{
	if(c>='A' && c<='Z') return 1;
	if(c>='a' && c<='z') return 1;
	return 0;
}

char toup(char c)
{
	if(c>='a' && c<='z')
		return c-'a'+'A';
	
	return c;
}

int ispalindlen(char* in, int len)
{
	char s[2001];
	int i;
	int j;
	int k;
	
	i=0;
	j=0;
	while(i<len)
	{
		if(in[j] == 0) return -1;

		if(isletter(in[j]))
			s[i++] = toup(in[j]);
		
		j++;
	}
	
	for(k=0;k<i;++k)
		if(s[k] != s[i-1-k]) return -1;
		
	return j;
}
	
int haspalindlen(char* in, int len)
{
	int i;
	int j;
	
	for(i=0;in[i];++i)
		if(isletter(in[i]) && (j=ispalindlen(in+i,len))!=-1)
		{
			if(len > maxlen)
			{
				maxlen = len;
				maxlenreal = j;
				maxpos = i;
				return 1;
			}
		}
		
	return 0;
}

int findodd(char* in)
{
	int min;
	int max;
	int t;
	
	min = 1;
	max = 2001;
	
	while(min+2<max)
	{
		printf("%i %i\n",min,max);
		t=2*((min+max)/4)+1;
		if(haspalindlen(in,t))
			min = t;
		else
			max = t;
	}
	
	return min;
}

int findeven(char* in)
{
	int min;
	int max;
	int t;
	
	min = 0;
	max = 2000;
	
	while(min+2<max)
	{
		t=2*((min+max)/4);
		if(haspalindlen(in,t))
			min = t;
		else
			max = t;
	}
	
	return min;
}

int main()
{
	FILE *in,*out;
	char s[20005];
	int i;
	
	in = fopen("calfflac.in","r");
	
	i=0;
		
	
	while(!feof(in))
		s[i++] = fgetc(in);
	
	s[i] = 0;
	fclose(in);
	
	findodd(s);
	findeven(s);

	out = fopen("calfflac.out","w");
	s[maxpos+maxlenreal] = 0;
	fprintf(out,"%i\n%s\n",maxlen,s+maxpos);
	fclose(out);
	
	return 0;
}
