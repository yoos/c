/**
 * Minimal hashmap implementation for this task.
 */

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <assert.h>

#include <config.h>

class HashLink {
	KEYTYPE     _key;
	VALTYPE     _val;
	HashLink*   _next;

public:
	HashLink(KEYTYPE key, VALTYPE val);
	KEYTYPE   key();        // Get key
	VALTYPE   val();        // Get value
	HashLink* next();       // Get next link
	void      val(VALTYPE v);      // Set value
	void      next(HashLink* p);   // Set next link
};

class HashMap {
	HashLink** _table;        // Array of pointers to HashLinks
	uint64_t   _tableSize;    // Size of table
	uint64_t   _numBuckets;   // Number of buckets
	uint64_t   _count;        // Number of HashLinks
	uint64_t   _maxDepth;     // Maximum bucket depth
	uint64_t   _maxKeyLength;   // Maximum key length

	// Helper functions
	uint64_t _hashKey(KEYTYPE key, uint64_t tableSize);   // Generate hash.
	void _deleteBucket(HashLink* p);   // Delete HashLinks.
	void _newTableInsert(KEYTYPE key, VALTYPE val);   // Insert key-value pairs into new table.
	void _resizeTable();   // Resize table if load is too high.

public:
	HashMap(uint64_t tableSize);
	~HashMap();

	VALTYPE get(KEYTYPE key);   // Get value
	void    inc(KEYTYPE key);   // Increment.

	/**
	 * @brief Get number of links in table.
	 */
	uint64_t getCount();

	/**
	 * @brief Get capacity of table.
	 */
	uint64_t getCapacity();

	/**
	 * @brief Get maximum depth of table.
	 */
	uint64_t getMaxDepth();

	/**
	 * @brief Get maximum key length.
	 */
	uint64_t getMaxKeyLength();

	/**
	 * @brief Get table load.
	 */
	float getLoad();

	/**
	 * @brief Store all keys in array allocated by caller.
	 * @param keys Pointer to array storing keys.
	 *
	 * @output Number of keys stored in array.
	 */
	void getKeys(char** keys);
};


#endif // HASHMAP_H

