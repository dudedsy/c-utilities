// shuffle.c
// counts how many moves in the shuffle described at 
// https://fivethirtyeight.com/features/how-long-will-you-shuffle-this-damn-deck-of-cards/
// for permutations in groups of n

// n is the first byte on stdin
// follwed by n bytes with integer representation
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
bool fileEnd(FILE *f);
void readPerm(char *a, int n);
void printPerm(char *a, int n);
void printVerbose(uint64_t permN, int sc, char *a, int n, bool best);
void printBasic(uint64_t permN, int sc, char *a, int n);

int main(int argc, char **argv) {
	bool verbose = false;
	if (argc > 1 && strcmp(argv[1], "-v") == 0) {
		verbose = true;
		printf("n,shuffleCount,perm,best\n");
	}
	int n = getchar();
	
	int64_t totalPerms = factorial(n);
	char a[n+1], bestPerm[n+1];
	
	int bestCount = -1;
	uint64_t permsTried = 1;
	uint64_t bestID;

	while (feof(stdin) == 0 && !fileEnd(stdin)) {
		readPerm(a, n);
		int sc = shuffleCount(a, n);

		if (verbose) printVerbose(permsTried, sc, a, n, sc > bestCount);

		if (sc > bestCount) {
			bestCount = sc;
			bestID = permsTried;
			memcpy(bestPerm, a, n+1);

			if(!verbose){
				printBasic(permsTried, sc, a, n);
			} 
		}

		if (permsTried++%1000000 == 0) {
			fprintf(stderr, "%luM / %luM\n", permsTried/1000000L, totalPerms/1000000L);
		}
	}

	if (!verbose) {
		printf("---------BEST--------------\n");
		printBasic(bestID, bestCount, bestPerm, n);
	}

	return 0;
}

bool fileEnd(FILE *f) {
	char ch = getchar();
	if (ch == EOF) return true;

	ungetc(ch, stdin);
	return false;
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

void readPerm(char *a, int n) {
	for(int i = 0; i < n; i++){
		a[i] = getchar();
	}
	a[n] = '\0';
}

void printPerm(char *a, int n) {
	for(int i = 0; i < n; i++){
		putchar(a[i] + 'a' - 1);
	}
}

void printVerbose(uint64_t permN, int sc, char *a, int n, bool best) {
	printf("%lu,%d,", permN, sc);
	printPerm(a, n);
	putchar(',');
	if (best) putchar('*');
	putchar('\n');
}

void printBasic(uint64_t permN, int sc, char *a, int n) {
	fprintf(stderr, "%d moves, perm# %lu\n", sc, permN);
	printf("%d moves, perm# %lu\n", sc, permN);
	for (int i = 0; i < n; i++) {
		fprintf(stderr,"%2x ", a[i]);
		printf("%2x ", a[i]);
	}
	putchar('\n');
	putc('\n', stderr);
}
