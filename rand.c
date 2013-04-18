#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

/* genera cadenas aleatorios de long dada */

int main(int argc, char **argv) {
	int i, len;
	char cc[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012345667890_=";

	if (argc != 2 || atoi(argv[1]) <= 0) {
		fprintf(stderr, "Usage: %s <len>\nLen must be positive\n", argv[0]);
		exit(-1);
	}

	srand(getpid() + time(NULL) + getppid());

	len = atoi(argv[1]);
	for(i=0; i<len; ++i) {
		putchar(cc[rand() % (sizeof (cc) - 1) ]);
	}

	putchar('\n');

	return 0;
}
