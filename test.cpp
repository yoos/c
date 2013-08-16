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

	hm.inc("hello");
	assert(hm.getCount() == 1);
	assert(hm.get("hello") == 1);

	hm.inc("hello");
	assert(hm.getCount() == 1);
	assert(hm.get("hello") == 2);
}

int main(int argc, char** argv)
{
	test_hashlink();
	test_hashmap();

	return 0;
}

