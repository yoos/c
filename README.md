# SpaceX Coding Test

This is a C++ application that parses a text file, reads out the words
(characters separated by whitespace), and prints a word -> count list in
reverse alphabetical order. The C++ STL and Boost libraries have not been used
with the exception of std::string.


## Usage

	make
	./count <file to parse>

Optionally, `-v` can be specified on the command line to print performance
statistics.


## Big-O Runtime

### HashMap

The HashMap class has two main operations to examine: `inc()` and
`_resizeTable()`.

In summary:
	* `inc()`: Best O(1), worst O(n)
	* `_resizeTable()`: Best/worst O(n)

If the hash function was perfectly uniform and we could distribute the input
words evenly across the hash table, `inc()` would be an O(1) operation. On the
other hand, in the worst case where every word evaluates to the same hash
value, `inc()` would be an O(n) operation due to the linked list implementation
of the bucket data structure.

The `_resizeTable()` function needs to step through all words and allocate
a proportional amount of memory, so it can do no better than O(n). If we assume
a worst case insert performance of O(n), worst-case resizing is O(1) + O(2)
+ ... + O(n) = O(n(n+1)/2) = O(n^2).

### Merge Sort

Merge sort involves an O(n) merge operation that is repeated O(log n) times for
a total time of O(n log n).

### Overall

The overall time complexity is O(n log n).

The time complexities of miscellaneous parts of the program are indicated in
the comments in `main.cpp`. The overall time complexity of the program is equal
to that of the mergesort operation, which has the worst time complexity among
the various parts.


# Testing Strategies

	* First implemented hash map, file input, then merge sort.
	* Wrote tests (test.cpp) after implementing every piece.
	* First implementation of hashmap dynamic resizing resulted in segfault.
	  Used gdb to determine issue was an invalid call to a HashLink::next() in
	  \_resizeTable() (off-by-one in while loop).
	* Used printfs inside HashMap class to find the resize function wasn't
	  being called after the first resize. More printfs inside the HashMap
	  class itself showed me my tests were incorrect.
	* Used gdb and valgrind to determine I had (inappropriately) initialized
	  a test case on the stack for a mergesort algorithm that expects a mutable
	  input array.
	* Used valgrind to eliminate memory leaks.
	* Compiled with debugging symbols while testing.


## Assumptions

	* Input word file will not contain more than 1 million _unique_ words
	  (total number of words is a much smaller concern).
	* Recursive deletions of hash buckets won't run into stack overflow issues.


<!--
vim: ft=markdown
-->
