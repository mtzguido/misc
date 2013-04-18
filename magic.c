/* magic.c - Guido Martínez - ~2010
	prints a magic sequence of length n, meaning, a string
	that contains all possible permutations of the n symbols
	as substrings, and is of mininum length (for s symbols and
	desired word length l, l + s^l - 1).
	Can be configured to use arbitrary symbols.
	
	The solution is basically to model the problem as a graph,
	where nodes abc...wxy and bcd...xyz are adjacent, and then
	find an eulerian cycle.
*/


#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

char* data;
char* symb = NULL;

/* parms */
int nsymb;
int len;
int wrap;

/* terminated in -1 */
char* seq;
char* swap;

#define getbit(i) ((data[(i)/CHAR_BIT]>>((i)%CHAR_BIT))&1)
#define setbit(i) (data[(i)/CHAR_BIT] |= (1<<((i)%CHAR_BIT)))
#define unsetbit(i) (data[(i)/CHAR_BIT] &= ~(1<<((i)%CHAR_BIT)))

int mypow(int b, int e)
{
	int r=1;
	
	while(e)
	{
		r*=(e&1)?b:1;
		e>>=1;
		b*=b;
	}
	
	return r;
}

void mystrcpy(char* dest, char* src)
{
	while((*dest++ = *src++) != -1);
}

void printSymb(int i)
{
	if(symb != NULL)
	{
		putchar(symb[i]);
		return;
	}


	/* default symbols */
	
	if(i<26)
	{
		putchar('a'+i);
		return;
	} else i-=26;
	
	if(i<26)
	{
		putchar('A'+i);
		return;
	} else i-=26;
	
	if(i<10)
	{
		putchar('0'+i);
		return;
	} else i-=10;
}

void printSeq(char* seq)
{
	while(*seq != -1)
		printSymb(*seq++);

	putchar('\n');
}

int next(int tok)
{
	int i;
	static int mask = -1;
	
	if(mask == -1)
		mask = mypow(nsymb,len-1);
	
	tok = (tok % mask) * nsymb;
	
	for(i=0;i<nsymb;++i)
		if(getbit(tok+i) == 0)
			return tok+i;
	
	return -1;
}

/* writes the last symbol of the start
 * string and continues until it gets
 * stuck.
 */
int tour(int start, char* wbuf)
{
	int ret = 0;

	while(start != -1)
	{
		setbit(start);
		*wbuf++ = start % nsymb;
		ret++;
		start = next(start);
	}
	
	*wbuf = -1;
	return ret;
}

int getWord(char* buf, int index)
{
	int i,ret;
	
	ret = 0;
	
	for(i=index-len+1;i<=index;++i)
		ret=ret*nsymb + buf[i];
	
	return ret;
}
 
void magic()
{
	int i;
	int n;
	int r;
	
	/* start at 000..0 and set i to the last char */

	for(i=0;i<len-1;++i)
	{
		seq[i] = 0;
		if(!wrap)
			printSymb(seq[i]);
	}
	
	seq[i--] = -1;
	
	setbit(0);
	
	while(seq[i] != -1)
	{
		while((n=next(getWord(seq,i))) != -1)
		{
			mystrcpy(swap,seq+i+1);
			r = tour(n,seq+i+1);
			mystrcpy(seq+i+r+1,swap);	
		}
		
		printSymb(seq[i]);
		
		i++;
	}
	
	putchar('\n');
}

void usage()
{
	fprintf(stderr,"Usage: magic [-w] nsymb len [symbols]\n\n");
	fprintf(stderr,"Prints a magic sequence of length len and amount "
			"of symbols nsymb.\n");
	fprintf(stderr,"The sequence contains every string of "
			"length len as substring and is minimal\n");
	fprintf(stderr,"When symbols is passed, they are used as the "
			"string symbols.\nThe length must not be less than nsymb\n");
	fprintf(stderr,"If -w is present, the string is interpreted "
			"to be wrapped around.\n");
	
}

int main(int argc, char** argv)
{
	int argind = 1;

	if(argind >= argc)
	{
		fprintf(stderr,"Not enough arguments.\n");
		usage();
		exit(1);
	}
	
	if(strcmp(argv[argind],"-w") == 0)
	{
		wrap = 1;
		argind++;
	} else wrap = 0;
	
	if(argind >= argc)
	{
		fprintf(stderr,"Not enough arguments.\n");
		usage();
		exit(1);
	}
	nsymb = atoi(argv[argind++]);
	
	if(argind >= argc)
	{
		fprintf(stderr,"Not enough arguments.\n");
		usage();
		exit(1);
	}
	len = atoi(argv[argind++]);
	
	if(argind < argc)
	{
		symb = argv[argind];
		if(strlen(symb) < nsymb)
		{
			fprintf(stderr,"Not enough symbols.\n");
			exit(2);
		}
	}
	
	if(symb == NULL && nsymb > 62)
	{
		fprintf(stderr,"Only 62 symbols available when unspecified.\n");
		exit(2);
	}

	data = calloc((mypow(nsymb,len)-1)/CHAR_BIT + 1,1);
	seq = malloc(mypow(nsymb,len) + len + 1);
	swap = malloc(mypow(nsymb,len) + len + 1);
	
	if(data == NULL || seq == NULL || swap == NULL)
	{
		perror("malloc");
		fprintf(stderr,"Not enough memory.\n");
		exit(1);
	}

	magic();

	free(data);
	free(seq);
	free(swap);
	
	return 0;
}
