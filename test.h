#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <hashmap.h>

void test_hashlink()
{
	HashLink hello("hello", 1);
	HashLink world("world", 2);

	hello.next(&world);

	printf("%d %d\n", hello.val(), hello.next()->val());

	hello.val(3);
	hello.next()->val(5);

	printf("%d %d\n", hello.val(), hello.next()->val());
}

void test_hashmap()
{
}

void test_all()
{
	test_hashlink();
	test_hashmap();
}

#endif // TEST_H

