/*
ID: guidoma1
LANG: C
TASK: dualpal
*/

#include <stdio.h>
#include <string.h>

FILE *fin,*fout;

char todig(int a)
{
	if(a<10) return a+'0';
	else return a-10+'A';
}

int pal(char* s)
{
	int i;
	
	for(i=0;i<strlen(s);++i)
		if(s[i] != s[strlen(s)-i-1]) return 0;
		
	return 1;
}

int check(int num)
{
	char s[100];

	int count=0;
	int base;
	int t;
	int ii;
	
	for(base=2;base<11;++base)
	{
		t = num;
		ii = 0;
		
		while(t>0)
		{
			s[ii++] = todig(t%base);
			t=t/base;
		}
		s[ii] = 0;
	
		if(pal(s)) count++;
		if(count>=2) break;
	}
	
	if(count<2) return 0;
	
	fprintf(fout,"%i\n",num);
	
	return 1;
}

int main()
{	
	int N,S;
	fin = fopen("dualpal.in","r");
	fout = fopen("dualpal.out","w");
	
	fscanf(fin,"%i %i",&N,&S);
	S++;
	
	while(N)
		N-=check(S++);
		
	return 0;
}
