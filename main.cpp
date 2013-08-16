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

	HashMap words(100);   // Create hashmap with 100 capacity to begin with.

	readFile(argv[1], &words);

	printf("Wordcount: %d  Hashmap load: %f\n", words.getCount(), words.getLoad());

	return 0;
}

