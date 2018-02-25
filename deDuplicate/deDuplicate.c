/*
* deDuplicate.c
* removes duplicates from an array of uint64_t
* Keeps original order.
* bevans.eng@gmail.com 
*/

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

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "deDuplicate.h"

typedef struct pair pair;
struct pair{
	uint64_t value;
	unsigned int index;
};

int comparePairsByValue(const void *vfirst, const void *vsecond){
	pair *first = (pair*) vfirst, *second = (pair*) vsecond;
	if (first->value == second->value) {
		return first->index - second->index;
	} else {
		return first->value - second->value;
	}
}

int comparePairsByIndex(const void *vfirst, const void *vsecond){
	pair *first = (pair*) vfirst, *second = (pair*) vsecond;
	if (first->index == second->index) {
		return first->value - second->value;
	} else {
		return first->index - second->index;
	}
}

uint64_t *deDuplicate(uint64_t *base, size_t nitems, size_t *nout) {
	pair indexedValues[nitems];
	int lastval;
	  
	uint64_t *outArray;

	for (int i = 0; i < nitems; i++){
		indexedValues[i].value = base[i];
		indexedValues[i].index = i;
	}

	qsort(indexedValues, nitems, sizeof(pair), comparePairsByValue);

	*nout = 1;
	for (int i = *nout; i < nitems; i++){
		if (indexedValues[i].value != indexedValues[*nout - 1].value) {
			indexedValues[(*nout)++] = indexedValues[i];
		} 
	}

	qsort(indexedValues, *nout, sizeof(pair), comparePairsByIndex);

	outArray = (uint64_t*) malloc(sizeof(uint64_t) * (*nout));
	for (int i = 0; i < *nout; i++){
		outArray[i] = indexedValues[i].value;
	}
	return outArray;
}



