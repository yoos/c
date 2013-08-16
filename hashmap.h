#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>
#include <string>

#define KEYTYPE std::string
#define VALTYPE uint16_t

class HashLink {
	KEYTYPE _key;
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

#endif // HASHMAP_H

