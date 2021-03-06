#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <hashmap.h>
#include <mergesort.h>

void test_hashlink()
{
	HashLink hello("hello", 1);
	HashLink world("world", 2);

	hello.next(&world);

	assert(hello.val() == 1);
	assert(hello.next()->val() == 2);

	hello.val(3);
	hello.next()->val(5);

	assert(hello.val() == 3);
	assert(hello.next()->val() == 5);
}

void test_hashmap()
{
	HashMap hm(100);
	assert(hm.getCount() == 0);
	assert(hm.getCapacity() == 100);

	// Can we increment?
	hm.inc("hello");
	assert(hm.getCount() == 1);
	assert(hm.get("hello") == 1);

	// Can we increment again?
	hm.inc("hello");
	assert(hm.getCount() == 1);
	assert(hm.get("hello") == 2);

	// Can we increment a different key?
	hm.inc("world");
	assert(hm.getCount() == 2);
	assert(hm.get("world") == 1);
	assert(hm.get("mars") == 0);

	// Calculate table load.
	hm.inc("!");
	assert(hm.getCount() == 3);
	assert(hm.get("world") == 1);
	assert(hm.get("!") == 1);
	assert(hm.getLoad() == 0.03f);

	// More collisions
	hm.inc("ymrld");   // Same hash value as "world"
	assert(hm.getCount() == 4);
	assert(hm.get("ymrld") == 1);
	assert(hm.getLoad() == 0.04f);

	// Does the table dynamically resize?
	HashMap hm1(1);
	assert(hm1.getCapacity() == 1);
	hm1.inc("first");
	assert(hm1.getCount() == 1);
	assert(hm1.get("first") == 1);
	assert(hm1.getCapacity() == 2);
	assert(hm1.getLoad() == 0.5f);
	hm1.inc("first");
	hm1.inc("first1");   // This should evaluate to a different hash value than "first", for a table size of 2.
	assert(hm1.getCount() == 2);
	assert(hm1.get("first") == 2);
	assert(hm1.get("first1") == 1);
	assert(hm1.getCapacity() == 4);
	assert(hm1.getLoad() == 0.5f);
}

void test_mergesort()
{
	// My mergesort updates the input array in place, so we need test input on
	// the heap.
	char* words[15];
	for (int i=0; i<15; i++) {
		words[i] = (char*) calloc(10, sizeof(char));
	}
	sprintf(words[0], "mercury");
	sprintf(words[1], "venus");
	sprintf(words[2], "earth");
	sprintf(words[3], "mars");
	sprintf(words[4], "jupiter");
	sprintf(words[5], "saturn");
	sprintf(words[6], "uranus");
	sprintf(words[7], "neptune");
	sprintf(words[8], "moho");
	sprintf(words[9], "eve");
	sprintf(words[10], "kerbin");
	sprintf(words[11], "duna");
	sprintf(words[12], "dres");
	sprintf(words[13], "jool");
	sprintf(words[14], "eeloo");

	mergeSort(words, 15, 10);
	for (int i=0; i<14; i++) {
		assert(wordCompare(words[i], words[i+1]) > 0);
	}

	// Deallocate.
	for (int i=0; i<15; i++) {
		free(words[i]);
	}
}

int main(int argc, char** argv)
{
	test_hashlink();
	test_hashmap();
	test_mergesort();

	return 0;
}

