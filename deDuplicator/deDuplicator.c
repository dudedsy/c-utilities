/**
* deDuplicator.c
* creates an object which can recieve uint64_t values and tell you if the object has previously seen that value.
* bevans.eng@gmail.com 
*/

/**
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
#include "deDuplicator.h"

struct deDuplicator {
   uint64_t *foundVals; // pointer to the head of the found array
   uint n;               // number of values found so far
   uint size;            // size of the underlying array
};

static void addVal(deDuplicatorPtr_t deDup, uint64_t n, int index);
static int DED_bgte(uint64_t *svals, uint64_t find, uint start, uint stop);

// create a new deDuplicator object
deDuplicatorPtr_t DED_init(){
   deDuplicatorPtr_t deDup = malloc(sizeof(struct deDuplicator));
   deDup->foundVals = malloc(4 * sizeof(uint64_t));
   deDup->n = 0;
   deDup->size = 4;
}

// tell us if the number has been previously seen
// true if the number has not been seen by this object
bool DED_scan(deDuplicatorPtr_t deDup, uint64_t n){
   if (deDup->n == 0) {
      addVal(deDup, n, 0);
      return true;
   }

   int index = DED_bgte(deDup->foundVals, n, 0, deDup->n);

   if (index < deDup->n && deDup->foundVals[index] == n) {
      return false;
   }

   addVal(deDup, n, index);
   return true;

   /*
   for (int i = 0; i < deDup->n; i++){
      if (deDup->foundVals[i] == n) return false;
   }
   addVal(deDup, n, 0);
   return true;
   */
}

// free the deDuplicator object and all associated memory
void DED_cleanup(deDuplicatorPtr_t deDup) {
   free(deDup->foundVals); 
   free(deDup);
}


// sorted, unique list of uint64s
// index of the number if it is in the list
// or else the index of the smallest number greater than find
// AKA: the index the number should have, were it in the list.
static int DED_bgte(uint64_t *svals, uint64_t find, uint start, uint stop){
   uint mid = (start + stop) / 2;

   if (start == mid) {
      if (svals[mid] >= find) { return mid; }
      if (svals[mid] < find) { return mid + 1; }
   }
   if (svals[mid] > find)   { return DED_bgte(svals, find, start, mid); }
   /* if (svals[mid] <= find)*/  return DED_bgte(svals, find, mid, stop); 
} 

static void addVal(deDuplicatorPtr_t deDup, uint64_t n, int index){
   if (deDup->size == deDup->n) {
      deDup->size *= 2;
      deDup-> foundVals = realloc(deDup->foundVals, deDup-> size * sizeof(uint64_t));
   }
   
   for (int i = deDup->n - 1; i >= index; i--) {
      deDup->foundVals[i + 1] = deDup->foundVals[i];
   }
   deDup->foundVals[index] = n;

   deDup->n++;

}