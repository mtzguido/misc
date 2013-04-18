#include <stdio.h>
#include <stdlib.h>

int MIN(int x,int y)
{
    if (x<y) return x;
    return y;
}

int main(){
	int* M;
    int* T;
	int ancho,alto;
	int i,j;

	printf("Ingrese el ancho y el alto: ");
	scanf("%i %i",&ancho,&alto);

	M = malloc(ancho*alto*sizeof(int));
    T = malloc(ancho*sizeof(int));

	printf("Ingrese la tabla: \n");
	for (i=0;i<alto;i++)
	    for(j=0;j<ancho;j++)
	            scanf("%i",&M[i*ancho+j]);

    T[0]=M[0];
    for(j=1;j<ancho;j++)
        T[j] = T[j-1] + M[j];

    for(i=1;i<alto;i++){
        T[0] += M[i * ancho];

        for(j=1;j<ancho;j++)
            T[j] = M[i*ancho+j] + MIN(T[j],T[j-1]);

    }

 /*   i=alto-1;
    j=ancho-1;

    while(i!=0 && j!=0)
    {
        if(M[(i-1)*alto + j] > M[i*alto + j - 1])
        {
            putchar('R');
            j--;
        } else {
            putchar('D');
            i--;
        }
    }

    while(i--!=0) putchar('D');
    while(j--!=0) putchar('R');
*/
    printf("\n\nEl costo es: %i\n",T[ancho-1]);

    return 0;
}
