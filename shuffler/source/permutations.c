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
#include "permutations.h"

int printPerms(char *a, uint8_t n, bool bin){
	uint64_t c[n];
	uint64_t i = 0;

	for (i = 0; i < n; i++) {
		c[i] = 0;
	}
	
	output(a, n, bin);
	
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
		output(a, n, bin);
		++c[i];
		i = 0;
	}
}

void swap(char *a, uint8_t i, uint8_t j){
	char temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void output(char *a, uint8_t n, bool bin) {
	if (bin) {
		for(int i = 0; i < n; i++){
			putchar(a[i]);
		}
	} else {
		for (int i = 0; i < n; i++) {
			printf("%c",a[i]);
			if (i < n-1) putchar(',');
		}
		printf("%s", "\n");
	}
}
