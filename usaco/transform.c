#include <stdio.h>
#include <stdlib.h>

/*
ID: guidoma1
LANG: C
TASK: transform
*/ 

int N;
char tabla[10][10];
char final[10][10];

void swap(char* a, char* b)
{
	char t;
	t = *a;
	*a = *b;
	*b = t;
}

void rot(char* a, char* b, char* c, char* d)
{
	char t;
	t = *d;
	*d = *c;
	*c = *b;
	*b = *a;
	*a = t;
}

void rotboard()
{
	int i,j;
	
	for(i=0;i<N/2;++i)
		for(j=0;j<(N+1)/2;++j)
			rot(&tabla[i][j],&tabla[j][N-i-1],&tabla[N-i-1][N-j-1],&tabla[N-j-1][i]);
}

void reflect()
{
	int i,j;
	
	for(i=0;i<N;++i)
		for(j=0;j<N/2;++j)
			swap(&tabla[i][j],&tabla[i][N-j-1]);
		
}

int eq()
{
	int i,j;
	
	for(i=0;i<N;++i)
		for(j=0;j<N;++j)
			if(tabla[i][j] != final[i][j]) return 0;
			
	return 1;
}

void terminar(int i,FILE* fout)
{
	fprintf(fout,"%i\n",i);
	exit(0);
}

int main()
{
	int i,j;fscanf(dict,"%s",s);
	
	
	FILE *fin,*fout;
	
	fin=fopen("transform.in","r");
	fout=fopen("transform.out","w");
	
	
	fscanf(fin,"%i",&N);
	fgetc(fin);
	
	for(i=0;i<N;++i)
	{
		for(j=0;j<N;++j)
			tabla[i][j] = fgetc(fin);
		
		fgetc(fin);
	}
	
	for(i=0;i<N;++i)
	{
		for(j=0;j<N;++j)
			final[i][j] = fgetc(fin);
		
		fgetc(fin);
	}
	
	rotboard();
	if(eq()) terminar(1,fout);
	rotboard();
	if(eq()) terminar(2,fout);
	rotboard();
	if(eq()) terminar(3,fout);
	rotboard();
	
	reflect();
	if(eq()) terminar(4,fout);
	
	rotboard();
	if(eq()) terminar(5,fout);
	rotboard();
	if(eq()) terminar(5,fout);
	rotboard();
	if(eq()) terminar(5,fout);
	rotboard();
	
	reflect();
	
	if(eq()) terminar(6,fout);
	
	terminar(7,fout);
	
	return 0;
}
	
	
	
