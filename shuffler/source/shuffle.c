// shuffle.c
// counts how many moves in the shuffle described at 
// https://fivethirtyeight.com/features/how-long-will-you-shuffle-this-damn-deck-of-cards/
// for permutations in groups of n
// n is the first byte on stdin
// follwed by bytes with integer representation
// of the card numbers 

/*
   Copyright 2018 Brian G. Evans
 
   Licensed under the Apache License, Version 2.0 (the "License"); 
   you may not use this file except in compliance with the License. 
   You may obtain a copy of the License at 
 
       http://www.apache.org/licenses/LICENSE-2.0 
 
   Unless required by applicable law or agreed to in writing, software 
   distributed under the License is distributed on an "AS IS" BASIS, 
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
   See the License for the specific language governing permissions and 
   limitations under the License. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int shuffleCount(uint8_t *a, int n);
uint64_t factorial (uint64_t n);

int main(int argc, char **argv) {
	bool verbose = false;

	if (argc > 1 && strcmp(argv[1], "-v") == 0) {
		verbose = true;
		printf("n,shuffleCount,perm,best\n");
	}
	
	fprintf(stderr, "reading decksize");
	int n = getchar();
	uint64_t totalPerms = factorial(n);
	char a[n+1], bestPerm[n+1];
	int bestCount = -1;
	uint64_t permsTried = 1;

	a[n] = '\0';
	while (feof(stdin) == 0) {
		char ch = getchar();
		if (ch == EOF) {
			return 0;
		} else {
			ungetc(ch, stdin);
		}
		for(int i = 0; i < n; i++){
			a[i] = getchar();
		}

		int sc = shuffleCount(a, n);

		if (verbose) {
				printf("%lu,%d,", permsTried, sc);
				for (int i = 0; i < n; i++) {
					printf("%c", a[i] + 'a' - 1);
				}
				putchar(',');
		}

		if (sc > bestCount) {
			bestCount = sc;
			memcpy(bestPerm, a, n+1);

			if(!verbose){
				fprintf(stderr, "%d moves\n", sc);
				printf("%d moves, perm# %lu\n", sc, permsTried);
				for (int i = 0; i < n; i++) {
					fprintf(stderr,"%2x ", a[i]);
					printf("%2x ", a[i]);
				}
				putchar('\n');
				putc('\n', stderr);
			} 
			else {
				putchar('*');
			}
		}

		if (verbose) {
			putchar('\n');
		}
		if (permsTried++%1000000 == 0) {
			fprintf(stderr, "%luM / %luM\n", permsTried/1000000L, totalPerms/1000000L);
		}
	}
	fprintf(stderr, "best: %d, ", )
	for (int i = 0; i < n; i++) {
		fprintf(stderr, "%c", a[i] + 'a' - 1);
	}
	fprintf(stderr, "\n");
	return 0;
}

uint64_t factorial (uint64_t n) {
	if (n <= 1) return 1;
	return factorial(n-1) * n;
}

int shuffleCount(uint8_t *a, int n) {
	//printf("entering shuffleCount");
	int count = 0;
	static uint8_t b[256], temp[256];
	memcpy(b, a, n);

	while (b[0] != 1) {
		++count;
		int c = b[0];
		for (int i = 0; i < c; i++){
			temp[i] = b[c - i - 1];
		}
		for (int i = 0; i < c; i++){
			b[i] = temp[i];
		}
	}

	return count;
}