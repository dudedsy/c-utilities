// resizingArrayU64.h
// a resizing array abstract data type

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

#include <stdint.h>
#include <stdbool.h>

typedef struct resizingArrayStruct_t *ResizingArrayU64Ptr_t;

// initializes an array with a given number of values, initialized to zero
ResizingArrayU64Ptr_t RAU64_init(uint64_t initialCount);

//returns the number of items in the list.
uint64_t RAU64_len(ResizingArrayU64Ptr_t arrPtr);

//returns true if the list is empty
uint64_t RAU64_isEmpty(ResizingArrayU64Ptr_t arrPtr);

// returns the value at index
// -1 sentinel value for index out of range...
// allows negative indexing ala python.
uint64_t RAU64_valueAt(ResizingArrayU64Ptr_t arrPtr, int64_t index);

// sets the value at the given index and returns true
// if the array is that big already
// otherwise returns false and does nothing
// negative indexes allowed
bool RAU64_setValueAt(ResizingArrayU64Ptr_t arrPtr, int64_t index, uint64_t value);

// append a value to the list
// goes at the end, increases the count. increases underlying size if necessary
void RAU64_append(ResizingArrayU64Ptr_t arrPtr, uint64_t value);

// remove and return the last value on the list
uint64_t RAU64_pop(ResizingArrayU64Ptr_t arrPtr);

// append another list onto the end of this one
// base is extended by extension
// extension is unchanged.
void RAU64_extend(ResizingArrayU64Ptr_t base, ResizingArrayU64Ptr_t extension);

// free all memory and destroy the array
void RAU64_cleanup(ResizingArrayU64Ptr_t arrPtr);