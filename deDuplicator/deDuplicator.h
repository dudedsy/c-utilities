#ifndef _DE_DUPLICATOR_H_
#define _DE_DUPLICATOR_H_

/*
* deDuplicate.h
* creates an object which can recieve uint64_t values and tell you if the object has previously seen that value.
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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct deDuplicator *deDuplicatorPtr_t;

// create a new deDuplicator object
deDuplicatorPtr_t DED_init();

// tell us if the number has been previously seen
// true if the number has not been previously scanned
bool DED_scan(deDuplicatorPtr_t deDup, uint64_t n);

static int DED_bgte(uint64_t *svals, uint64_t find, uint start, uint stop);

// free the deDuplicator object and all associated memory
void DED_cleanup(deDuplicatorPtr_t deDup);

#endif /* _DE_DUPLICATOR_H_ */