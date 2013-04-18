#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define OESTE(x) (((x)>>0)&1)
#define NORTE(x) (((x)>>1)&1)
#define ESTE(x)  (((x)>>2)&1)
#define SUR(x)   (((x)>>3)&1)

#define OESTEcons 1
#define NORTEcons 2
#define ESTEcons  4
#define SURcons   8

int M,N;
char* tab;
int* col;

int fill(int pos, int color)
{
	int hab;
	
	if(pos<0 || pos>=M*N || col[pos] == color)
		return 0;
	
	hab = 1;
	col[pos] = color;
		
	if(!OESTE(tab[pos]) && pos%M != 0)   hab += fill(pos-1,color);
	if(!NORTE(tab[pos]) && pos/M != 0)   hab += fill(pos-M,color);
	if(!ESTE(tab[pos])  && pos%M != M-1) hab += fill(pos+1,color);
	if(!SUR(tab[pos])   && pos/M != N-1) hab += fill(pos+M,color);

	return hab;
}

int max(int x, int y)
{
	return (x>y)?x:y;
}

int main()
{
	int i,j;
	int maxh = 0;
	
	int t;
	
	int x,y;
	char dir;
	
	scanf("%i %i",&M,&N);
	
	tab = malloc(M*N*sizeof(char));
	col = malloc(M*N*sizeof(int));
	
	memset(col,0,M*N*sizeof(int));
	
	for(i=0;i<M*N;++i)
	{
		scanf("%i",&tab[i]);
	}
	
	i = j = 0;
	
	while(j<M*N)
	{
		i++;
		maxh = max(maxh,fill(j,i));
		
		while(j<M*N && col[j]!=0) j++;
	}

	printf("%i\n%i\n",i,maxh);
	
	maxh=0;
	for(i=0;i<M;++i)
	{
		for(j=N-1;j>=0;--j)
		{
			assert(j*M+i < M*N);
			if(NORTE(tab[j*M+i]))
			{
				memset(col,0,M*N*sizeof(int));
				tab[j*M+i] &= ~NORTEcons;
				t = fill(j*M+i,1);

				if(t>maxh)
				{
					maxh=t;
					x=i; y=j;
					dir='N';
				}
				tab[j*M+i] |= NORTEcons;
			}
		}
		for(j=N-1;j>=0;--j)
		{
			if(ESTE(tab[j*M+i]))
			{
				memset(col,0,M*N*sizeof(int));
				tab[j*M+i] &= ~ESTEcons;
				t = fill(j*M+i,1);

				if(t>maxh)
				{
					maxh=t;
					x=i; y=j;
					dir='E';
				}
				tab[j*M+i] |= ESTEcons;
			}
		}
	}
	
	printf("%i\n",maxh);
	printf("%i %i %c\n",y+1,x+1,dir);
	return 0;
}
