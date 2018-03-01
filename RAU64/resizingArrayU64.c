// resizingArrayU64.c
// a c module to implement resizing arrays

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
#include <stdbool.h>
#include <string.h>
#include "resizingArrayU64.h"

#define MIN(A, B) (A < B) ? A : B
#define MAX(A, B) (A < B) ? B : A

static void resize(ResizingArrayU64Ptr_t arrPtr, uint64_t newSize);

struct resizingArrayStruct_t {
	uint64_t *arr;
	uint64_t count;
	uint64_t size;
};

uint64_t RAU64_valueAt(ResizingArrayU64Ptr_t arrPtr, int64_t index) {
	if (index < 0) index = arrPtr->count + index; // allows negative indexing ala python
	if (index < 0 || index >= arrPtr->count) return -1;

	return arrPtr->arr[index];
}

bool RAU64_setValueAt(ResizingArrayU64Ptr_t arrPtr, int64_t index, uint64_t value) {
	if (index < 0) index = arrPtr->count + index; // allows negative indexing ala python
	if (index < 0 || index >= arrPtr->count) return false;

	arrPtr->arr[index] = value;
	return true;
}

void RAU64_append(ResizingArrayU64Ptr_t arrPtr, uint64_t value) {
	if (arrPtr->count < arrPtr->size) arrPtr->arr[arrPtr->count++] = value;
	else {
		resize(arrPtr, 2 * arrPtr->size);
		RAU64_append(arrPtr, value);
	}
}

uint64_t RAU64_len(ResizingArrayU64Ptr_t arrPtr) {
	return arrPtr->count;
}

uint64_t RAU64_isEmpty(ResizingArrayU64Ptr_t arrPtr) {
	return arrPtr->count <= 0;
}

uint64_t RAU64_pop(ResizingArrayU64Ptr_t arrPtr) {
	if (arrPtr->count < 1) return -1;
	uint64_t toReturn;
	--(arrPtr->count);
	toReturn = arrPtr->arr[arrPtr->count];
	if (arrPtr->count < (arrPtr->size / 4)) resize(arrPtr, arrPtr->size / 2);
	return toReturn;
}

void RAU64_extend(ResizingArrayU64Ptr_t base, ResizingArrayU64Ptr_t extension){
	if (base->count + extension->count <= base->size){
		memcpy(base->arr + base->count, extension->arr, extension->count * sizeof(uint64_t));
	} else {
		resize(base, MAX(base->size * 2, base->size + extension->size));
		RAU64_extend(base, extension);
	}
}

ResizingArrayU64Ptr_t RAU64_init(uint64_t initialSize) {
	// initialize struct
	ResizingArrayU64Ptr_t toReturn;
	toReturn = malloc(sizeof(struct resizingArrayStruct_t));
	
	// set values
	toReturn->count = 0;
	toReturn->size = initialSize;

	//initialize array
	toReturn->arr = malloc(initialSize * sizeof (uint64_t));

	return toReturn;
}

void RAU64_cleanup(ResizingArrayU64Ptr_t arrPtr) {
	free(arrPtr->arr);
	free(arrPtr);
}

// changes the size of the underlying array
static void resize(ResizingArrayU64Ptr_t arrPtr, uint64_t newSize) {
	arrPtr->arr = realloc(arrPtr->arr, newSize * sizeof(uint64_t));
	arrPtr->size = newSize;
}