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
#include "deDuplicator.h"


int main(void) {
  uint64_t cur;
  char c;

  deDuplicatorPtr_t deDup = DED_init();

  while (scanf("%lu", &cur) == 1) {
    if (DED_scan(deDup, cur)){
      printf("%lu\n", cur);
    }
  }

  DED_cleanup(deDup);
	
  return 0;
}