//RAU6_example.c
//example to use the resizingArrayU64 library

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
#include "resizingArrayU64.h"

int main(void) {
	resizingArrayU64Ptr_t arr1, arr2;
	arr1 = RAU64_init(4);
	arr2 = RAU64_init(1);

	for (int i = 0; i < 20; i++){
		RAU64_append(arr1, i);
		RAU64_append(arr2, i*1000000000);
		printf("lens: %lu, %lu" RAU64_len(arr1), RAU64_len(arr2));
	}

	for (int i = 0; i < 20; i++){
		printf("%lu, %lu\n", RAU64(arr1), RAU64_pop(arr2));
	}

	

	for (int i = 0; i < 30; i++){
		if (((i % 7) % 6) % 5 != 0){
			RAU64_append(arr1, i);
			if (!RAU64_isEmpty(arr1)) printf("popped from 1 %lu\n"RAU64_pop(arr1));
			RAU64_append(arr2, i);
		}
		else {
			if (!RAU64_isEmpty(arr2)) printf("popped from 2 %lu\n"RAU64_pop(arr2));
			RAU64_append(arr1, i);
		}
	}


	printf("--------------------------\n");
	printf("printing remainig parts of arr1\n");
	while(!RAU64_isEmpty(arr1)) printf("%lu\n",RAU64_pop(arr1));

	printf("--------------------------\n");
	printf("printing remainig parts of arr2\n");
	while(!RAU64_isEmpty(arr2)) printf("%lu\n",RAU64_pop(arr2));
}