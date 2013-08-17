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
	//printf("Merging: %u ", left);
	//for (int i=0; i<lSize; i++) printf("%s ", left[i]);
	//printf("and %u ", right);
	//for (int i=0; i<rSize; i++) printf("%s ", right[i]);
	//printf("\n");

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
			sprintf(tmp[ti++], (wordCompare(left[li], right[ri], wordMaxLength) > 0) ? left[li++] : right[ri++]);   // Ignore case.
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

int wordCompare(char* word1, char* word2, uint64_t wordMaxLength)
{
	char loword1[wordMaxLength+1];
	char loword2[wordMaxLength+1];

	// Ignore case by converting everything to lowercase.
	for (uint64_t i=0; word1[i] != '\0'; i++) {
		loword1[i] = tolower(word1[i]);
	}
	for (uint64_t i=0; word2[i] != '\0'; i++) {
		loword2[i] = tolower(word2[i]);
	}

	return strcmp(word1, word2);
}

