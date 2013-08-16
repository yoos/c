#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include <hashmap.h>

int main(int argc, char **argv)
{
	HashLink hello("hello", 1);
	HashLink world("world", 2);

	hello.next(&world);

	printf("%d %d\n", hello.val(), hello.next()->val());

	hello.val(3);
	hello.next()->val(5);

	printf("%d %d\n", hello.val(), hello.next()->val());

	return 0;
}

