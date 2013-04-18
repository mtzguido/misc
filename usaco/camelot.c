#include <stdio.h>
#include <stdlib.h>
/*
TASK: camelot
LANG: C
ID: guidoma1
*/

int ancho,alto;

int costo[26][40][26][40];

int ncab;
int cabx[1041];
int caby[1041];

int reyx;
int reyy;

int colax[1041];
int colay[1041];
int lencola;
int primerocola;

int validPos(int x, int y)
{
	return (x>=0 && x<ancho && y>=0 && y<alto);
}

void llenarDistC()
{
	int i,j,k,l;
	int x,y;
	
	for(i=0;i<ancho;++i)
		for(j=0;j<alto;++j)
		{
			for(k=0;k<ancho;++k)
				for(l=0;l<alto;++l)
					costo[i][j][k][l] = 1e8;
				
			colax[0] = i;
			colay[0] = j;
			costo[i][j][i][j] = 0;
			lencola = 1;
			primerocola = 0;
			
			while(lencola>0)
			{
				x = colax[primerocola];
				y = colay[primerocola];
			
				lencola--;
				primerocola++;
				
				if(validPos(x+2,y+1) && costo[i][j][x+2][y+1] == 1e8)
				{
					costo[i][j][x+2][y+1] = 1 + costo[i][j][x][y];
					colax[lencola+primerocola] = x+2;
					colay[lencola+primerocola] = y+1;
					lencola++;
				}
				if(validPos(x+2,y-1) && costo[i][j][x+2][y-1] == 1e8)
				{
					costo[i][j][x+2][y-1] = 1 + costo[i][j][x][y];
					colax[lencola+primerocola] = x+2;
					colay[lencola+primerocola] = y-1;
					lencola++;
				}
				if(validPos(x-2,y+1) && costo[i][j][x-2][y+1] == 1e8)
				{
					costo[i][j][x-2][y+1] = 1 + costo[i][j][x][y];
					colax[lencola+primerocola] = x-2;
					colay[lencola+primerocola] = y+1;
					lencola++;
				}
				if(validPos(x-2,y-1) && costo[i][j][x-2][y-1] == 1e8)
				{
					costo[i][j][x-2][y-1] = 1 + costo[i][j][x][y];
					colax[lencola+primerocola] = x-2;
					colay[lencola+primerocola] = y-1;
					lencola++;
				}
				if(validPos(x+1,y+2) && costo[i][j][x+1][y+2] == 1e8)
				{
					costo[i][j][x+1][y+2] = 1 + costo[i][j][x][y];
					colax[lencola+primerocola] = x+1;
					colay[lencola+primerocola] = y+2;
					lencola++;
				}
				if(validPos(x+1,y-2) && costo[i][j][x+1][y-2] == 1e8)
				{
					costo[i][j][x+1][y-2] = 1 + costo[i][j][x][y];
					colax[lencola+primerocola] = x+1;
					colay[lencola+primerocola] = y-2;
					lencola++;
				}
				if(validPos(x-1,y+2) && costo[i][j][x-1][y+2] == 1e8)
				{
					costo[i][j][x-1][y+2] = 1 + costo[i][j][x][y];
					colax[lencola+primerocola] = x-1;
					colay[lencola+primerocola] = y+2;
					lencola++;
				}
				if(validPos(x-1,y-2) && costo[i][j][x-1][y-2] == 1e8)
				{
					costo[i][j][x-1][y-2] = 1 + costo[i][j][x][y];
					colax[lencola+primerocola] = x-1;
					colay[lencola+primerocola] = y-2;
					lencola++;
				}
			}
		}
}

int distC(int x1, int y1, int x2, int y2)
{
	return costo[x1][y1][x2][y2];
}

int max(int x, int y)
{
	return (x>y)?x:y;
}

int min(int x, int y)
{
	return (x<y)?x:y;
}

int distR(int x1, int y1, int x2, int y2)
{
	return max(max(x1-x2,x2-x1),max(y1-y2,y2-y1));
}

int main()
{
	char c;
	int t;
	
	int x1,y1;
	int x2,y2;
	int i;
	int fix;
	
	FILE* in;
	FILE* out;

	int sumatodos;
	int costo=1e6;
	
	in = fopen("camelot.in","r");
	out = fopen("camelot.out","w");
	
	fscanf(in,"%i %i\n",&alto,&ancho);
	llenarDistC();
	
	fscanf(in,"%c %i\n",&c,&t);
	reyx = c-'A';
	reyy = t-1;
	
	ncab = 0;
	while(fscanf(in,"%c %i\n",&c,&t) == 2)
	{
		cabx[ncab] = c-'A';
		caby[ncab] = t-1;
		ncab++;
	}
	
	if(ncab == 0)
	{
		fprintf(out,"0\n");
		return 0;
	}
	
	for(x2=0;x2<ancho;++x2)
		for(y2=0;y2<alto;++y2) /* pos final */
		{
			sumatodos = 0;
			for(i=0;i<ncab;++i)
			{
				sumatodos+=distC(cabx[i],caby[i],x2,y2);
				if(sumatodos >= costo) continue;
			}
				
			for(x1=0;x1<ancho;++x1)
				for(y1=0;y1<alto;++y1)
				{					
					if(sumatodos + distR(reyx,reyy,x1,y1) >= costo) continue;
					fix = sumatodos + distC(x1,y1,x2,y2) + distR(reyx,reyy,x1,y1);
					
					for(i=0;i<ncab;++i)
						costo = min(costo, distC(cabx[i],caby[i],x1,y1)- distC(cabx[i],caby[i],x2,y2) + fix);
				}
		}

	fprintf(out,"%i\n",costo);

	return 0;
}
