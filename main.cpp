#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#include <hashmap.h>
#include <mergesort.h>
#include <config.h>

void readFile(std::string filename, HashMap* words)
{
	std::ifstream file(filename.c_str());
	std::string word;

	if (file.is_open()) {
		while (file >> word) {
			words->inc(word);   // Add to hashmap.
		}
	}
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s <file to parse> [-v]\n", argv[0]);
		return -1;
	}

	// Create hashmap.
	HashMap wordsMap(HASHMAP_INIT_CAPACITY);

	// Read file and store wordcount to hashmap.
	readFile(argv[1], &wordsMap);

	// Store all words to array.
	char* wordsArray[wordsMap.getCount()];
	for (uint64_t i=0; i<wordsMap.getCount(); i++) {
		wordsArray[i] = (char*) calloc(WORD_MAXLENGTH+1, sizeof(char));   // TODO: Assume maximum word length of 200 characters
	}
	wordsMap.getKeys(wordsArray);

	// Sort array in reverse alphabetical order.
	mergeSort(wordsArray, wordsMap.getCount());

	// Print words in reverse alphabetical order along with their wordcounts.
	for (uint64_t i=0; i<wordsMap.getCount(); i++) {
		printf("%-20s: %2d\n", wordsArray[i], wordsMap.get(wordsArray[i]));
	}

	// Free memory.
	for (uint64_t i=0; i<wordsMap.getCount(); i++) {
		free(wordsArray[i]);
	}

	// Performance report.
	if (argc > 2 && strcmp(argv[2], "-v") == 0) {
		printf("\n\nUnique words counted: %d\n", wordsMap.getCount());
		printf("Hash map final size: %d\n", wordsMap.getCapacity());
		printf("Hash map final load: %f\n", wordsMap.getLoad());
		printf("Hash map maximum depth: %d\n", wordsMap.getMaxDepth());
	}

	return 0;
}

