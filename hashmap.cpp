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


HashMap::HashMap(uint64_t tableSize)
{
	_table = (HashLink**) calloc(tableSize, sizeof(HashLink*));
	_tableSize = tableSize;
	_count = 0;
}

HashMap::~HashMap()
{
	// Deallocate all HashLinks and table.
	for (uint64_t i=0; i<_tableSize; i++) {
		if (_table[i] != 0) {
			_deleteHashLink(_table[i]);
		}
	}
}

VALTYPE HashMap::get(KEYTYPE key)
{
	uint64_t hash = _hashKey(key);
	HashLink* link = _table[hash];

	// Find the link with the right key, assuming that if a bucket exists here, the key has to be here, too.
	if (link != 0) {
		while (link->key() != key) {
			link = link->next();
		}
		return link->val();
	}

	// Otherwise, return 0.
	return 0;
}

void HashMap::inc(KEYTYPE key)
{
	uint64_t hash = _hashKey(key);
	HashLink* link = _table[hash];

	if (link != 0) {
		if (link->key() == key) {
			link->val(link->val()+1);
		}
		else if (link->next() == 0) {
			link->next(new HashLink(key, 1));
			_count++;
		}
		else {
			link = link->next();
		}
	}
	else {
		_table[hash] = new HashLink(key, 1);
		_count++;
	}
}

uint64_t HashMap::getCount()
{
	return _count;
}

uint64_t HashMap::getCapacity()
{
	return _tableSize;
}

float HashMap::getLoad()
{
	uint64_t numBuckets = 0;
	for(uint64_t i=0; i<_tableSize; i++) {
		if (_table[i] != 0) {
			numBuckets++;
		}
	}

	return ((float) numBuckets) / _tableSize;
}

void HashMap::getKeys(KEYTYPE* keys)
{
	uint64_t key_index = 0;
	HashLink* hl = 0;   // Keep track of next HashLink from which to grab a key.

	for (uint64_t i=0; i<_tableSize; i++) {
		hl = _table[i];
		while (hl != 0) {
			keys[key_index] = hl->key();
			hl = hl->next();
		}
	}
}

// TODO: Need a better hash function.
uint64_t HashMap::_hashKey(KEYTYPE key)
{
	uint64_t out = 0;
	for (int i=0; key[i] != '\0'; i++) {
		out = (out+key[i]) % _tableSize;
	}

	assert(out < _tableSize);   // We really don't want this to happen.

	return out;
}

void HashMap::_deleteHashLink(HashLink* p)
{
	if (p->next() != 0) {
		_deleteHashLink(p->next());
	}
	delete p;
}

void HashMap::_insert(KEYTYPE key, VALTYPE val)
{
	uint64_t hash = _hashKey(key);
	HashLink* link = _table[hash];

	// If bucket already exists, find the last link in bucket.
	if (link != 0) {
		while (link->next() != 0) {
			link = link->next();
		}
		link->next(new HashLink(key, val));
	}
	else {
		_table[hash] = new HashLink(key, val);
	}

	_count++;
}

