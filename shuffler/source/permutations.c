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

void printPerms(char *a, uint8_t n, bool bin, bool reversed){
	uint64_t c[n];
	uint64_t i = 0;

	for (i = 0; i < n; i++) {
		c[i] = 0;
	}
	
	output(a, n, bin, reversed);
	
	i = 0;
	while (i < n) {
		if (c[i] >= i) {
			c[i] = 0;
			++i;
			continue;
		}
		if (i%2 == 0) {
			swap(a, 0, i);
		} else {
			swap(a, c[i], i);
		}
		output(a, n, bin, reversed);
		++c[i];
		i = 0;
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

	output(a, n, bin, reversed);

	int k = findk(a, n);
	while (k >= 0) {
		int i = findi(a, k, n);
		swap(a, i, k);
		reverse(a, k + 1, n);
		output(a, n, bin, reversed);
		k = findk(a, n);
	}
}

void swap(char *a, uint8_t i, uint8_t j){
	char temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void output(char *a, uint8_t n, bool bin, bool reversed) {


	if (bin) {
		if (reversed) {
			for(int i = n-1; i >= 0; i--){
				putchar(a[i]);
			}
		}
		else {
			for(int i = 0; i < n; i++){
				putchar(a[i]);
			}
		}
	} else {
		if (reversed) {
			for (int i = n-1; i >= 0; i--){
				printf("%c",a[i]);
				if (i > 0) putchar(',');
			}
		}
		else {
			for (int i = 0; i < n; i++) {
				printf("%c",a[i]);
				if (i < n-1) putchar(',');
			}
		}
		putchar('\n');
	}
}
