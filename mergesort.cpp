#include <mergesort.h>

void mergeSort(char** list, uint64_t size)
{
	// Base case -- don't do anything.
	if (size <= 1) {
		return;
	}

	uint64_t pivot = size / 2;
	mergeSort(list, pivot);
	mergeSort(list+pivot, size-pivot);

	merge(list, list+pivot, pivot, size-pivot);
}

void merge(char** left, char** right, uint64_t lSize, uint64_t rSize)
{
	char* sorted[lSize+rSize];
	for (uint64_t i=0; i<lSize+rSize; i++) {
		sorted[i] = (char*) calloc(WORD_MAXLENGTH+1, sizeof(char));
	}

	uint64_t si = 0;       // Sorted index
	uint64_t li = 0;       // Left index
	uint64_t ri = lSize;   // Right index

	// Merge.
	while (li < lSize || ri < lSize+rSize) {
		sorted[si++] = (strcmp(left[li], right[ri]) == -1 || ri == rSize) ? left[li++] : right[ri++];
	}

	// Free memory.
	for (uint64_t i=0; i<lSize+rSize; i++) {
		free(left[i]);
	}
	free(left);
	free(right);

	left = sorted;
}

