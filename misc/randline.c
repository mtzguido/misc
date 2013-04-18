#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *progname;

void* stretch(void* buf, size_t newsz)
{
	void* t;

	t = realloc(buf, newsz);
	if(t == NULL) {
		fprintf(stderr, "%s: not enough memory\n", progname);
		exit(1);
	}

	return t;
}

int main(int argc, char *argv[])
{
	char   *keep;
	size_t  keepsz;
	char   *lbuf;
	size_t  bufsz;
	int     lineno;

	progname = argv[0];

	srand(getpid() + getppid());

	keepsz = 80;
	keep   = malloc(keepsz);
	bufsz  = 80;
	lbuf   = malloc(bufsz);

	while(!feof(stdin)) {
		int readln = 0;
		int done = 0;
		while(!done) {
			if(fgets(lbuf+readln, bufsz-readln, stdin) == NULL) {
				/* done = 1 */
				break;
			}

			if(lbuf[strlen(lbuf)-1] != '\n') { /* falta */
				readln = bufsz-1;
				lbuf = stretch(lbuf, 2*bufsz);
				bufsz *= 2;
			} else { /* ok */
				lbuf[strlen(lbuf)-1] = 0;
				done = 1;
			}
		}

		if(rand() % lineno == 0) {
			if(bufsz > keepsz) {
				keepsz = bufsz;
				keep = stretch(keep, keepsz);
			}
			strcpy(keep, lbuf);
		}

		lineno++;
	}

	printf("%s\n", keep);

	return 0;
}

