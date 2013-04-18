#include <stdio.h>
#include <stdint.h>

int hendrie(register int64_t x, register int log)
{
	register int64_t t;
	register int64_t s;
	register int i;
	
	s = pot2(log);
	
	while(1)
	{
		x = x - s;
	
		if(x == 0) return log;
		
		if(s < x+(log+1))
			return 0;
		
		t = s>>2;
		log-=2;
		
		i = 0;
		while(1)
		{
			s = x - i*t;
			
			if(s>t)
			{
				x = s - t;
				t>>=1;
				log--;
			} else {
				
				x = x%t;
				
				/*x = t<<1;*/
				
				if(x)
					x+=t;
				else  
				{
					x = t = t<<1;
					log++;
				}
				
				s = t;
				break;
			}
			i++;
		}
	}
	
	return 0;
}

int main()
{
	register int64_t x;
	int log;
	register char c;

	while(1)
	{
		x=0;
	
		while((c=getchar())!='\n')
			x = 10*x + (c-'0');

		if(x==0) return 0;
		
		log=log2int(x);
		printf("%i\n",hendrie(x,log));
	}
	
	return 0;
}
