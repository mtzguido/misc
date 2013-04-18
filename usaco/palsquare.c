/*
ID: guidoma1
LANG: C
TASK: palsquare
*/

#include <stdio.h>

int b;
FILE *fin,*fout;

char todig(int a)
{
	if(a<10) return a+'0';
	else return a-10+'A';
}

void check(int num)
{
	char s1[100];
	char s2[100];
	int t;
	int i;
	int ii;
	int j;
	
	
	t = num;
	ii = 0;
	
	while(t>0)
	{
		s1[ii++] = todig(t%b);
		t=t/b;
	}
	s1[ii] = 0;
	
	
	t=num*num;
	i=0;
	while(t>0)
	{
		s2[i++] = todig(t%b);
		t=t/b;
	}
	s2[i] = 0;
	
	for(j=0;j<i;++j)
		if(s2[j] != s2[i-1-j]) return;
	
	i--;ii--;
	
	while(ii>=0) fputc(s1[ii--],fout);
	fputc(' ',fout);
	while(i>=0) fputc(s2[i--],fout);
	fputc('\n',fout);
}

int main()
{	
	int i;
	fin = fopen("palsquare.in","r");
	fout = fopen("palsquare.out","w");
	
	fscanf(fin,"%i",&b);
	
	for(i=1;i<301;++i)
		check(i);
		
	return 0;
}
