// bth.c

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
#include <string.h>

int main(int argc, char **argv) {
	int lineSize;
	int err = 1;

	if (argc < 2) {
		lineSize = 10;
		err = 0;
	}
	else if (argc == 2 && strcmp(argv[1], "-s") == 0) {
		lineSize = getchar();
		err = 0;
	}
	else if (argc == 2 && sscanf(argv[1], "%d", &lineSize) == 1) {
		err = 0;
	}

	if (argc > 2 || err != 0) {
		fprintf(stderr, "useage: %s [number | -s (mode first character from stream indicates codes per line)]", argv[0]);
		return 1;
	}

	int i = 0;
	while (feof(stdin) == 0) {
			i++;
			printf("%02x ", getchar());
			if (i == lineSize) {
				putchar('\n');
				i = 0;
			}
	}
	putchar('\n');
}