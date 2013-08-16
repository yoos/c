/**
 * Minimal hashmap implementation for this task.
 */

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <stdint.h>
#include <string>

#define KEYTYPE std::string
#define VALTYPE uint16_t

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
	uint64_t   _count;        // Number of HashLinks

	// Helper functions
	uint64_t _hashKey(KEYTYPE key);   // Generate hash.
	void _deleteHashLink(HashLink* p);   // Delete HashLinks.
	void _insert(KEYTYPE key, VALTYPE val);   // Insert key-value pairs.

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
	 * @brief Store all keys in array allocated by caller.
	 * @param keys Pointer to array storing keys.
	 *
	 * @output Number of keys stored in array.
	 */
	void getKeys(KEYTYPE* keys);
};


#endif // HASHMAP_H

