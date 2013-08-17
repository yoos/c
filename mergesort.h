#ifndef MERGESORT_H
#define MERGESORT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <config.h>

/**
 * @brief Top-down merge sort in reverse alphabetical order
 */
void mergeSort(char** list, uint64_t size);

/**
 * @brief Allocates new array into which to merge left and right. Old array is
 * deallocated.
 */
void merge(char** left, char** right, uint64_t lSize, uint64_t rSize);

#endif // MERGESORT_H

