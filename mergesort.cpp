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
	//printf("Merging: %u ", left);
	//for (int i=0; i<lSize; i++) printf("%s ", left[i]);
	//printf("and %u ", right);
	//for (int i=0; i<rSize; i++) printf("%s ", right[i]);
	//printf("\n");

	// Allocate temporary array to sort into.
	char* tmp[lSize+rSize];
	for (uint64_t i=0; i<lSize+rSize; i++) {
		tmp[i] = (char*) calloc(WORD_MAXLENGTH+1, sizeof(char));
	}

	uint64_t ti = 0;   // tmp index
	uint64_t li = 0;   // Left index
	uint64_t ri = 0;   // Right index

	// Merge into temporary array.
	while (li < lSize || ri < rSize) {
		if (li < lSize && ri < rSize) {
			sprintf(tmp[ti++], (strcmp(left[li], right[ri]) > 0) ? left[li++] : right[ri++]);
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

