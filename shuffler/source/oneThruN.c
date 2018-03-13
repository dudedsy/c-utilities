// oneThruN.c
// prints the numbers 1 thru n to the standard out

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "useage: %s [number] (-n) where number is the integer max number to print\n", argv[0]);
		return 1;
	}
	
	unsigned n;
	if(sscanf(argv[1], "%u", &n) == 0) {
		fprintf(stderr, "useage: %s [number] (-n)\n", argv[0]);
		return 1;
	}
	
	if (argc > 2 && strcmp(argv[2], "-n") == 0) putchar((char) n);

	for (unsigned  i = 1; i <= n; i++) putchar ((char) i);
	
	return 0;
}