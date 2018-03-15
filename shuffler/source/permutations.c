// permutations.c

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
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "permutations.h"

static int cmpU8(const void *a, const void *b);
static inline int findk(char * a, int n);
static inline int findi(char *a, int k, int n);

void printPerms(char *a, uint8_t n, bool bin, bool reversed, bool lexo){
	if (bin) {
		putchar((unsigned char) n);
	}
	else {
		printf("%d", n);
	  	printf("%s \n", a);
	}

	if (lexo) {
		printLexPerms(a, n, bin, reversed);
	}
	else {
		printHeapPerms(a, n, bin, reversed);
	}
}

char *readBase(bool bin, int *n) {
	char *a;

	if (bin) { 
	  	*n = getchar();
    	a = malloc((*n + 1) * sizeof(char));

    	for (int i = 0; i < *n; i++){
  			a[i] = getchar();
  		}	
    }
    else {
    	scanf("%d", n);
	  	a = malloc((*n + 1) * sizeof(char));
	  	
	    char fstr[16];
	    sprintf(fstr, " %ds", *n);
	  	fstr[0] = '%';
	  	scanf(fstr, a);
    }

  	return a;
}

void printHeapPerms(char *a, uint8_t n, bool bin, bool reversed) {
	int c[n];
	int i;
	char acp[n];
	memcpy(acp, a, n);
	for (i = 0; i < n; i++) c[i] = 0;
	
	i=0;
	while (i < n) {
		output(acp, n, bin, reversed);
		nextHeapPerm(acp, n, c, &i);
	}
}

void nextHeapPerm(char *a, int n, int *c, int *i) {
	while (c[*i] >= *i) {
		c[*i] = 0;
		++(*i);
	}
	if (*i < n) {
		if (*i%2 == 0) {
			swap(a, 0, *i);
		}
		else {
			swap(a, c[*i], *i);
		}
		++c[*i];
		*i = 0;
	}
}

static int cmpU8(const void *a, const void *b) {
	return (*(uint8_t*)a - *(uint8_t*)b);
} 

static inline int findk(char * a, int n) {
	int k = n - 2;
	while (k >= 0) {
		if (a[k] < a[k + 1]) break;
		--k;
	}
	return k;
}

static inline int findi(char *a, int k, int n) {
	if (k < 0 || k >= n) return -1;
	int i = n - 1;
	while (a[k] >= a[i]) --i;
	return i;
} 

void reverse(char *a, int start, int stop) {
	char* end = a + stop - 1;
	a += start;

	char t;
	while (a < end) {
		t = *a;
		*a++ = *end;
		*end-- = t;
	}
}

void printLexPerms(char *a, uint8_t n, bool bin, bool reversed) {
	char acp[n];
	memcpy(acp, a, n);
	qsort(acp, n, sizeof(uint8_t), cmpU8);
	int k;

	do {
		output(acp, n, bin, reversed);
		k = nextLexPerm(acp, n);
	} while (k >= 0);
}

int nextLexPerm(char *a, int n) {
	int k = findk(a, n);
	if (k >= 0) {
		int i = findi(a, k, n);
		swap(a, i, k);
		reverse(a, k+1, n);
	}
	return k;
}

void swap(char *a, uint8_t i, uint8_t j){
	char temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void output(char *a, uint8_t n, bool bin, bool reversed) {
	if (bin && reversed) {
		for(int i = n-1; i >= 0; i--){
			putchar(a[i]);
		}
	}
	else if (bin){
		for(int i = 0; i < n; i++){
			putchar(a[i]);
		}
	}
	else if (reversed){
		for (int i = n-1; i >= 0; i--){
			printf("%c",a[i]);
			if (i > 0) putchar(',');
		}
		putchar('\n');
	}
	else {
		for (int i = 0; i < n; i++) {
			printf("%c",a[i]);
			if (i < n-1) putchar(',');
		}
		putchar('\n');
	}	
		
}

bool in_str(char *a, char b) {
	while (*a != '\0') {
		if (b == *a++) return true;
	}
	return false;
}