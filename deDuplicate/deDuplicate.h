#ifndef _DE_DUPLICATE_H_
#define _DE_DUPLICATE_H_

/*
* deDuplicate.h
* removes duplicates from an array of uint64_t
* Keeps original order.
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

uint64_t *deDuplicate(uint64_t *base, size_t nitems, size_t *nout);

#endif /* _DE_DUPLICATE_H_ */