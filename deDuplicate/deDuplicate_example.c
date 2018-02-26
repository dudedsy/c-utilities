/* deDuplicate_example.c
 *
 * example use of the deDuplicator in deDuplicate.h
 * first item an positive integer list length
 * takes a list of newline separated  numbers from the standard in,
 * Then de-duplicates that list and sends to the standard out
 *
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

#include <stdio.h>
#include <stdint.h>
#include "deDuplicate.h"


int main(void) {
  int nitems;
	uint64_t *inArr;
  uint64_t *deDuplicated; 
	size_t nout;

  scanf("%d", &nitems);

  inArr = malloc(nitems * sizeof(uint64_t));

  for (int i = 0; i < nitems; i++) {
    scanf("%lu", inArr + i);
  }
    
	deDuplicated = deDuplicate(inArr, nitems, &nout);
	
  for (int i = 0; i < nout; i++){
		printf("%d\n", (int) deDuplicated[i]);
	}
	printf("\n");
	
  return 0;
}