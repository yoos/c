#include <hashmap.h>

HashLink::HashLink(KEYTYPE key, VALTYPE val)
{
	_key = key;
	_val = val;
	_next = 0;
}

KEYTYPE HashLink::key()
{
	return _key;
}

VALTYPE HashLink::val()
{
	return _val;
}

HashLink* HashLink::next()
{
	return _next;
}

void HashLink::val(VALTYPE v)
{
	_val = v;
}

void HashLink::next(HashLink* p)
{
	_next = p;
}

