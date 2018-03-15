// permutations.h

/*
   read data from the standard in and write permutations to the stanadard out
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
#include <stdbool.h>
/*
   reads a string from the standard in.
   bin == false:
      reads a string from the standard in
      the value of n is set to the length of the string (not including null terminator)
      and char * is a pointer to the malloc'd string
   bin == true:
      reads a byte as uint8 number of bytes to follow
      then reads that many chars
      n is set to the number of chars read
      and returns a pointer to the malloc'd char array

*/
char *readBase(bool bin, int *n);

/*
   string a of length n
   calculate all permutations and output to the standard out

   bin == true
      write one byte representing the input string length
      then write the permutation bytes
   bin == false
      print human readable number of characters
      print one permutated string per line

   reversed: if true, individually reverse the output permutations

   lexo: if true, use lexographic ordering, else heap's algorithm (minimal swaps)
   
*/
void printPerms(char *a, uint8_t n, bool bin, bool reversed, bool lexo);
void printHeapPerms(char *a, uint8_t n, bool bin, bool reversed);
void printLexPerms(char *a, uint8_t n, bool bin, bool reversed);

/* 
   permute a in place to next lexographic permutation
   return value negative if last permutation 
   n is the number of characters to permute
*/
int nextLexPerm(char *a, int n);

/*
   permute a in place to next heap permutation
   pass i = 0, c pointer to zeroed array length n
   with first call.

   then continue using same c and i
*/
void nextHeapPerm(char *a, int n, int *c, int *i);

void swap(char *a, uint8_t i, uint8_t j);
void output(char *a, uint8_t n, bool bin, bool reversed);
void reverse(char *a, int start, int stop);
bool in_str(char *a, char b);