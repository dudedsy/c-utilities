Some c utilities I use for various numerical and algorithmic processing

/deDuplicate

a list deDuplicating tool for lists of uint64_t.
This was a question that was posed to me that I found somewhat interesting.
This utility will remove duplicates from a list and keep it in the original order.

/deDuplicator

An on-line version of deDuplicate, 
The deDuplicator implements an interface which creates a deDuplicator object
The deDuplicator object scans numbers and tells you whether it has seen them before.
It also exposes a binary search function for sorted unique lists of uint64_t
This function gives the correct insertion location for a new number to add to the sorted list of uniques
If the search number is already in the list, it gives the location of the search number.

/RAU64

a resizing array of uint64_t
abstract data type allows automagic resizing arrays ala python right here in c!
