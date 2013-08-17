#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#include <hashmap.h>

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
		printf("Usage: %s <file to parse>\n", argv[0]);
		return -1;
	}

	HashMap wordsMap(100);   // Create hashmap with 100 capacity to begin with.

	readFile(argv[1], &wordsMap);

	printf("Wordcount: %d  Hashmap load: %f\n", wordsMap.getCount(), wordsMap.getLoad());

	char* wordsArray[wordsMap.getCount()];
	for (uint64_t i=0; i<wordsMap.getCount(); i++) {
		wordsArray[i] = (char*) calloc(200+1, sizeof(char));   // TODO: Assume maximum word length of 200 characters
	}
	wordsMap.getKeys(wordsArray);

	for (uint64_t i=0; i<wordsMap.getCount(); i++) {
		printf("%6d: %s\n", i, wordsArray[i]);
	}

	return 0;
}

