#ifndef CONFIG_H
#define CONFIG_H

// Performance
#define HASHMAP_INIT_CAPACITY 100   // Initial capacity of hashmap used to store words found in input text file.

// HashMap
#define KEYTYPE std::string
#define VALTYPE uint16_t
#define LOAD_THRESHOLD 0.75   // Table load threshold at which we increase table size.
#define RESIZE_FACTOR 2   // Multiply table size by this factor on resize.

#define MAX(a,b) ((a>b) ? a : b)

#endif // CONFIG_H

