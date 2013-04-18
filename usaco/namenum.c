#include <stdio.h>
#include <stdlib.h>

char* tabla[10] = {"","","ABC","DEF","GHI","JKL","MNO","PRS","TUV","WXY"};
/*
ID: guidoma1
LANG: C
TASK: namenum
*/

int eq(char i,char a)
{
	if(tabla[i-'0'][0] == a || tabla[i-'0'][1] == a || tabla[i-'0'][2] == a) return 1;
	
	else return 0;
}

int match(char* ID,char* cad)
{
	int i;
	
	for(i=0;ID[i];i++)
		if(!eq(ID[i],cad[i])) return 0;
		
	return (cad[i]==0);
}

int main()
{
	char ID[12];
	int i;
	char s[100];
	int p = 0;
	FILE *in,*out;
	FILE *dict;
	
	in = fopen("namenum.in","r");
	out = fopen("namenum.out","w");
	dict = fopen("dict.txt","r");
	
	fscanf(in,"%s",ID);
	
	for(i=0;ID[i];++i)
		if(ID[i] == '1')
			return 0;
	
	while(!feof(dict))
	{
		fscanf(dict,"%s",s);
		if(match(ID,s))
		{
			fprintf(out,"%s\n",s);
			p=1;
		}
	}	
	
	if(p==0)
		fprintf(out,"NONE\n");
	
	return 0;
}
