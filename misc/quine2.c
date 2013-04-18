#include <stdio.h>

#define N 10
#define C 34
#define T 9

/* este programa imprime su propio codigo fuente por la salida estandar */
int main()
{
	char* s = "#include <stdio.h>%c%c#define N 10%c#define C 34%c#define T 9%c%c/* este programa imprime su propio codigo fuente por la salida estandar */%cint main()%c{%c%cchar* s = %c%s%c;%c%c%cprintf(s,N,N,N,N,N,N,N,N,N,T,C,s,C,N,N,T,N,T,N,N,N);%c%creturn 0;%c}%c%c";

	printf(s,N,N,N,N,N,N,N,N,N,T,C,s,C,N,N,T,N,T,N,N,N);
	return 0;
}

