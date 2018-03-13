//perm.c


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
#include <string.h>
#include <stdlib.h>
#include "permutations.h"

int main(int argc, char **argv) {
	bool binaryMode;
	switch (argc) {
		case 0: case 1:
			binaryMode = false;
			break;
		case 2:
			if (strcmp(argv[1],"-b") == 0){
				binaryMode = true;
				break;
			} else {
				fprintf(stderr, "unrecognized paramemter %s, ", argv[1]);
			}
		default:
			fprintf(stderr, "bad arguments (argc = %d)\n"
					"call as %s -b for binary mode\n"
					"or call with no args for human mode\n", 
					argc, argv[0]);
			return 2;
	}

  int n;
  char *a;

  if (binaryMode) {
  	n = getchar();
    a = malloc((n+1) * sizeof(char));

  	for (int i = 0; i < n; i++){
  		a[i] = getchar();
  	}

  	putchar((unsigned char) n);
  }

  else {
  	scanf("%d", &n);
  	a = malloc((n+1) * sizeof(char));
  	
    char fstr[16];
    sprintf(fstr, " %ds", n);
  	fstr[0] = '%';
  	scanf(fstr, &a);

  	printf("%d", n);
  	printf("%s \n", a);
	}

  printPerms(a, n, binaryMode);
  free(a);
}