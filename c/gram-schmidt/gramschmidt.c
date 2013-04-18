#include <stdio.h>
#include <stdlib.h>

float innerProduct(float* v1, float* v2, int l)
{
	int i;
	float r = 0;

	for(i=0;i<l;++i)
		r = r + v1[i]*v2[i];
	
	return r;
}

void linComb(float a, float* v1, float b, float* v2, int l) //v1 = a*v1 + b*v2
{
	int i;

	for(i=0;i<l;++i)
		v1[i] = a*v1[i] + b*v2[i];
}

float ortogonalize(float* v1, float* v2, int l) //cambia v1 para dejarlo ortogonal a v2
{
	float k;

	k = innerProduct(v2,v2,l);
	k = innerProduct(v1,v2,l) / k;

	linComb(1,v1,-k,v2,l);
}

void gs(float* M, int l, int r)
{
	int i,j;

	for(i=1;i<r;++i)
	{
		for(j=0;j<i;++j)
		{
			ortogonalize(M + i*l,M + j*l,l);
		}
	}
}

int main()
{
	float* M;
	int l,r;
	int i,j;

	printf("Longitud de los vectores: ");
	scanf("%i",&l);
	printf("Cantidad de vectores: ");
	scanf("%i",&r);
	
	M = malloc(sizeof(float) * l * r);

	if(M == NULL)
	{
		printf("No hay memoria.\n");
		exit(1);
	}
	
	for(i = 0;i<r;++i)
		for(j=0;j<l;++j)		
			scanf("%f",M + i*l + j);

	gs(M,l,r);

	for(i = 0;i<r;++i)
	{
		for(j=0;j<l;++j)
			printf("%f ",M[i*l + j]);
		
		putchar('\n');
	}
	
	return 0;
}
