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
	_numBuckets = 0;
	_count = 0;
}

HashMap::~HashMap()
{
	// Deallocate all HashLinks and table.
	for (uint64_t i=0; i<_tableSize; i++) {
		if (_table[i] != 0) {
			_deleteBucket(_table[i]);
		}
	}

	free(_table);
}

VALTYPE HashMap::get(KEYTYPE key)
{
	uint64_t hash = _hashKey(key, _tableSize);
	HashLink* link = _table[hash];

	// Find the link with the right key, assuming that if a bucket exists here, the key has to be here, too.
	if (link != 0) {
		// Dig through bucket.
		while (link->key() != key && link->next() != 0) {
			link = link->next();
		}

		// Have we found the key?
		if (link->key() == key) {
			return link->val();
		}
	}

	// Otherwise, return 0.
	return 0;
}

void HashMap::inc(KEYTYPE key)
{
	uint64_t hash = _hashKey(key, _tableSize);
	HashLink* link = _table[hash];

	if (link != 0) {
		// Dig through bucket.
		while (link->key() != key && link->next() != 0) {
			link = link->next();
		}

		// Have we found the key?
		if (link->key() == key) {
			link->val(link->val()+1);
		}
		// If not, create new.
		else {
			link->next(new HashLink(key, 1));
			_count++;
		}
	}
	else {
		// Create new link.
		_table[hash] = new HashLink(key, 1);
		_numBuckets++;
		_count++;

		// If load is too high, resize table.
		if (getLoad() > LOAD_THRESHOLD) {
			_resizeTable();
		}
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
	return ((float) _numBuckets) / _tableSize;
}

void HashMap::getKeys(char** keys)
{
	uint64_t key_index = 0;
	HashLink* link = 0;   // Keep track of next HashLink from which to grab a key.

	for (uint64_t i=0; i<_tableSize; i++) {
		link = _table[i];
		while (link != 0) {
			sprintf(keys[key_index], link->key().c_str());
			link = link->next();
			key_index++;
		}
	}
}

// TODO: Need a better hash function.
uint64_t HashMap::_hashKey(KEYTYPE key, uint64_t tableSize)
{
	uint64_t out = 0;
	for (int i=0; key[i] != '\0'; i++) {
		out = (out+key[i]) % tableSize;
	}

	assert(out < tableSize);   // We really don't want this to happen.

	return out;
}

void HashMap::_deleteBucket(HashLink* p)
{
	if (p->next() != 0) {
		_deleteBucket(p->next());
	}
	delete p;
}

void HashMap::_newTableInsert(KEYTYPE key, VALTYPE val)
{
	uint64_t hash = _hashKey(key, _tableSize);
	HashLink* link = _table[hash];

	if (link != 0) {
		// Find next available slot.
		while (link->next() != 0) {
			link = link->next();
		}
		link->next(new HashLink(key, val));
	}
	else {
		_table[hash] = new HashLink(key, val);
		_numBuckets++;
	}
}

void HashMap::_resizeTable()
{
	HashLink** _oldTable = _table;   // Move old table to temporary location.
	uint64_t   _oldTableSize = _tableSize;   // Save old table size.
	_tableSize *= RESIZE_FACTOR;   // Update table size.
	_numBuckets = 0;   // Reset bucket count.
	_table = (HashLink**) calloc(_tableSize, sizeof(HashLink*));   // Allocate new table.

	// Step through the old table and populate new table using new hash values.
	HashLink* oldLink = 0;
	for (uint64_t i=0; i<_oldTableSize; i++) {
		if (_oldTable[i] != 0) {
			oldLink = _oldTable[i];
			while (oldLink->next() != 0) {
				// Insert link into new table.
				_newTableInsert(oldLink->key(), oldLink->val());

				// Move onto next link.
				oldLink = oldLink->next();
			}
			// Last one
			_newTableInsert(oldLink->key(), oldLink->val());
		}
	}

	// Deallocate old table.
	for (uint64_t i=0; i<_oldTableSize; i++) {
		if (_oldTable[i] != 0) {
			_deleteBucket(_oldTable[i]);
		}
	}
	free(_oldTable);
}

