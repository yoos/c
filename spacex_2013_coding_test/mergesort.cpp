#include <mergesort.h>

void mergeSort(char** list, uint64_t size, uint64_t wordMaxLength)
{
	// Base case -- don't do anything.
	if (size <= 1) {
		return;
	}

	uint64_t pivot = size / 2;
	mergeSort(list, pivot, wordMaxLength);
	mergeSort(list+pivot, size-pivot, wordMaxLength);

	merge(list, list+pivot, pivot, size-pivot, wordMaxLength);
}

void merge(char** left, char** right, uint64_t lSize, uint64_t rSize, uint64_t wordMaxLength)
{
	// Allocate temporary array to sort into.
	char* tmp[lSize+rSize];
	for (uint64_t i=0; i<lSize+rSize; i++) {
		tmp[i] = (char*) calloc(wordMaxLength+1, sizeof(char));
	}

	uint64_t ti = 0;   // tmp index
	uint64_t li = 0;   // Left index
	uint64_t ri = 0;   // Right index

	// Merge into temporary array.
	while (li < lSize || ri < rSize) {
		if (li < lSize && ri < rSize) {
			sprintf(tmp[ti++], (wordCompare(left[li], right[ri]) > 0) ? left[li++] : right[ri++]);
		}
		else if (li < lSize) {
			sprintf(tmp[ti++], left[li++]);
		}
		else {
			sprintf(tmp[ti++], right[ri++]);
		}
	}

	// Copy contents of temporary array into old memory location and free memory.
	for (uint64_t i=0; i<lSize+rSize; i++) {
		sprintf(left[i], tmp[i]);
		free(tmp[i]);
	}
}

int wordCompare(char* word1, char* word2)
{
	return strcmp(word1, word2);
}

