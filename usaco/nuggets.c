#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int x, int y)
{
	int t;
	
	while(y>0)
	{
		t = x%y;
		x = y;
		y = t;
	}
	
	return x;
}

int coprimos(int* tam, int cant)
{
	int g;
	int i;
	
	g = 0;
	
	for(i=0;i<cant;++i)
	{
		g=gcd(g,tam[i]);
		
		if(g==1)
			return 1;
	}
	
	return 0;
}

int main()
{

	char* buff;
	int cant;
	int* tam;
	int i,j;
	int min,max;
	int consec,last;

	scanf("%i",&cant);
	tam = malloc(cant * sizeof(int));
	
	for(i=0;i<cant;++i)
	{
		scanf("%i",&tam[i]);
		
		if(i==0) min = max = tam[i];
		else if(tam[i] < min) min = tam[i];
		else if(tam[i] > max) max = tam[i];
	}
	
	if(min == 1 || !coprimos(tam,cant))
	{
		printf("0\n");
		return 0;
	}
	
	buff = malloc(max * sizeof(char));
	memset(buff,0,max*sizeof(char));
	
	consec = 0;
	last = -1;
	for(i=1;;++i)
	{
		if(buff[i%max] == 0)
			for(j=0;j<cant;++j)
				if(i == tam[j] || buff[(max+(i-tam[j]))%max])
				{
					buff[i%max] = 1;
					break;
				}
		
		if(buff[i%max])
			consec++;
		else
		{
			last = i;
			consec = 0;
		}
		
		if(consec == min)
			break;
	}
	
	printf("%i\n",last);
	
	return 0;
}
