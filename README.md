Some c utilities I use for various numerical and algorithmic processing

/deDuplicate

A list deDuplicating tool for lists of uint64_t.
This was a question that was posed to me that I found somewhat interesting.
This utility will remove duplicates from a list and keep it in the original order.

/deDuplicator
An on-line version of deDuplicate, 
The deDuplicator implements an interface which creates a deDuplicator object.
The deDuplicator object scans numbers and tells you whether it has seen them before.
It also exposes a binary search function for sorted unique lists of uint64_t.
This function gives the correct insertion location for a new number to add to the sorted list of uniques
If the search number is already in the list, it gives the location of the search number.

/RAU64

A resizing array of uint64_t
abstract data type allows automagic resizing arrays ala python right here in c!

/shuffler
pipeline of tools for the conway shuffle.

perm.c depends on permutations.c, permutations.h
heap's permutations algorithm.
-b flag uses binary input and output modes

shuffle.c does conway shuffles and counts max steps
-v flag makes it write all permutations and scores, not just winners.

oneThruN.c prints the numbers 1...n-1 to standard out
-n flag starts the list with its length as a byte.


