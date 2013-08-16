#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <hashmap.h>

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
	hm.inc("xnrld");   // Same hash value as "world"
	assert(hm.getCount() == 3);
	assert(hm.get("world") == 1);
	assert(hm.get("xnrld") == 1);
	assert(hm.getLoad() == 0.02f);

	// More collisions
	hm.inc("ymrld");   // Same hash value as "world"
	assert(hm.getCount() == 4);
	assert(hm.get("ymrld") == 1);
	assert(hm.getLoad() == 0.02f);
}

int main(int argc, char** argv)
{
	test_hashlink();
	test_hashmap();

	return 0;
}

