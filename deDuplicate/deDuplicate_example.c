/* deDuplicate_example.c
 * example use of the deDuplicator in deDuplicate.h
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

int main(void) {
	uint64_t test[] = {11,11,3,6,5,9,5}; 
    uint64_t *deDuplicated;
	int nitems = 7; 
	size_t nout;
    
	deDuplicated = deDuplicate(test, nitems, &nout);
	for (int i = 0; i < nout; i++){
		printf("%d\n", (int) done[i]);
	}
	printf("\n");
	return 0;
}