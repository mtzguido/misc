#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define INF (-1)

struct temp_node
{
	int nodenum;
	int val;
};

inline int menor(int x,int y)
{
	if (y==INF) return (x!=INF);
	if (x==INF) return 0;
	return (x<y);
}

inline int min(int x,int y)
{
	if (menor(x,y))
		return x;
	else
		return y;
}

inline void swap(int* x,int* y)
{
	int t;
	t=*x;
	*x=*y;
	*y=t;
}

inline void swapnodes(struct temp_node* x,struct temp_node* y)
{
	struct temp_node t;
	t=*x;
	*x=*y;
	*y=t;
}

void flotar(struct temp_node* heap,int pos)
{
	while(pos > 0 && menor(heap[pos].val,heap[(pos-1)/2].val))
	{
		swapnodes(&heap[pos],&heap[(pos-1)/2]);
		pos = (pos-1)/2;
	}
}

void hundir(struct temp_node* heap,int size, int pos)
{
	int s;

	while(1)
	{
		s=pos;
		if(2*pos+1<size && menor(heap[2*pos+1].val,heap[pos].val)) s=2*pos+1;
		if(2*pos+2<size && menor(heap[2*pos+2].val,heap[s].val)) s=2*pos+2;

		if(s!=pos)
		{
			swapnodes(&heap[s],&heap[pos]);
			//printf("Hundiendo %i a %i.\n",pos,s);
			pos=s;
		} else break;
	}
}

int find_paths(int** costs,int start, int cant_nodos,int end) //-1 representa a infinito
{
	struct temp_node nodes[cant_nodos];
	int act; // nodo activo (ultimo nodo correcto)
			 // el heap es [0..act-1]
			 // nodos correctos [act..cant_nodos-1]
	int i;

	//los nodos correctos van al final

	for(i=0;i<cant_nodos;++i)
	{
		nodes[i].nodenum = i;
		nodes[i].val = INF;
	}

	nodes[start].val = 0;

	swapnodes(&nodes[start],&nodes[cant_nodos-1]);
	act=cant_nodos-1;

	while((act>0) && (nodes[act].nodenum != end) && (nodes[act].val != INF))
	{
		for(i=0;i<act;++i)
		{
			//esta comparacion se hace cant_nodos^2 veces
			if(costs[nodes[act].nodenum][nodes[i].nodenum] == INF)
			{
				continue;
			}

			if(menor(nodes[act].val + costs[nodes[act].nodenum][nodes[i].nodenum],nodes[i].val))
			{
				//actualizo distancia
				nodes[i].val = nodes[act].val + costs[nodes[act].nodenum][nodes[i].nodenum];

				//mantengo el heap (floto)
				flotar(nodes,i);
			}
		}

		swapnodes(&nodes[0],&nodes[act-1]); //extraigo el minimo
		act--;
		//hundo
		hundir(nodes,act,0);
	}

	return nodes[act].val; // si el bucle termino por nodes[act].nodenum==end tenemos el costo
						   // si termino por llegar a un valor INF debe ser el costo tambien INF
						   // ya que solo pueden quedar vertices con valor INF
}

int** leer(int size)
{
	int** A;
	int i,j;


	A=malloc(size*sizeof(int*));
	if(A==NULL) abort();

	for(i=0;i<size;++i)
	{
		A[i] = malloc(size*sizeof(int));
		if(A[i]==NULL) abort();
	}
	printf("Ingrese matriz de costos.\n");

	for(i=0;i<size;++i)
		for(j=0;j<size;++j)
			scanf("%i",&A[i][j]); //i fila

	return A;

}

int main(int argc,char** argv)
{
	int** A;
	int n,end;
	int i;
	int res;
	clock_t t1,t2;

	scanf("%i %i",&n,&end);
	A=leer(n);

	t1=clock();
	res=find_paths(A,0,n,end);
	t2=clock();

	printf("%i\n",res);
/*
	t2=(int)((t2-t1)*1000/CLOCKS_PER_SEC); //milisec

	printf("Completado en %2.i:%2.i:%2.i:%3.i. (Tamano %i)\n"
		,t2/3600000
		,(t2/60000)%60
		,(t2/1000)%60
		,t2%1000
		,n);
*/
	for(i=0;i<n;++i)
		free(A[i]);
	free(A);

	return 0;
}


