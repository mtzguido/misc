#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//NO VALIDO LA ENTRADA, si la entrada no es una expresion valida puede pasar cualquier cosa

char* ops = "()+-*/^";

int isdigito(char c) //devuelve verdadero si c es un digito
{
	return ('0' <= c && c <= '9');
}

int prec(char op) //devuelve la precedencia de un operador. si "op" no esta en "ops" se rompe todo
{
	int i;
	i = 0;
	while(ops[i] != op) i++;
	return i;
}

char opstack[100]; //aca van los operadores
int valstack[100]; //aca los valores
int lenop; //longitud de las pilas
int lenval;

void readsymbol() //lee un operador o un valor, lo que haya
{
	char c;
	int val;
	
	while((c = getchar()) == ' ');
	if(isdigito(c)) //si es un num
	{
		val = c-'0';
		while(isdigito(c=getchar()))
			val = 10*val + (c-'0'); //leo todos los digitos hasta que recibo algo que no es un digito
		
		ungetc(c,stdin); //devuelvo el caracter a la entrada estandar
		valstack[lenval++] = val; //lo agrego a la pila
	} else {
		opstack[lenop++] = c; //agrego el operador a la pila
	}
}

int powint(int b, int e)
{
	int r = 1;
	
	while(e)
	{
		r *= (e&1)?b:1;
		e>>=1;
		b*=b;
	}
	
	return r;
}

int evalop(char op, int l, int r) //evalua
{
	switch(op)
	{
		case '+': return l+r;
		case '-': return l-r;
		case '*': return l*r;
		case '/': return l/r;
		case '^': return powint(l,r);
	}
	
	return 0;
}

void eval()
{
	if(lenop < 2) return; //1 operador o menos no hacemos nada
	
	if(opstack[lenop-2] == '(' && opstack[lenop-1] == ')') //si hay parentesis y ningun operador en el medio los borramos
	{
		lenop=lenop-2; //osea simplificamos cosas como "(1)" a "1"
		eval(); //evaluo de nuevo hasta que no quede nada
	} else if(prec(opstack[lenop-2]) >= prec(opstack[lenop-1])) { //si el operador de atras tiene mas precedencia, lo puedo calcular
		if(opstack[lenop-1] == '(') return; //si era un parentesis no hago nada, esto es medio choto pero funca
		valstack[lenval-2] = evalop(opstack[lenop-2],valstack[lenval-2],valstack[lenval-1]); //si no, evaluo y lo meto en el penultimo de la pila
		lenval--; //combine 2 valores, queda 1 menos
		opstack[lenop-2] = opstack[lenop-1]; //saco el operador que acabo de calcular
		lenop--; //lo saque -> hay menos :P
		eval(); //evaluo de nuevo hasta que no quede nada
	}
}

int main()
{
	char c;
	a:
	lenop = lenval = 0;

	while((c=getchar())!= '\n')
	{
		//printf("%c!\n",opstack[0]);
		ungetc(c,stdin); //devuelvo lo que acabo de sacar
		readsymbol(); //leo algo
		eval(); //evaluo
	}
	opstack[lenop++] = ')'; //esto hace colapsar todo, es una cagada pero anda
	eval(); //evaluo con el parentesis que meti
	
	printf("%i\n",valstack[0]); //en la primera pos queda el resultado
	goto a;
	
	return 0;
}
