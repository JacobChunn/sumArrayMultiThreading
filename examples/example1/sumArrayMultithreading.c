#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "sumFunctions.h"
#include "generateDataFunctions.h"

void main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("No file argument specified\n");
		return;
	}

	long long  arrLens[] = {1, 10, 100, 1000, 10000,
		100000, 1000000};

	int threadCounts[] = {1, 2, 3, 4, 8, 12, 16, 20, 24, 28, 32};

	int errCheck = appendtimeSumArrayOverParamsToCSV(
		argv[1],
		10000,
		1,
		arrLens,
		(int)(sizeof(arrLens) / sizeof(arrLens[0])),
		threadCounts,
		(int)(sizeof(threadCounts) / sizeof(threadCounts[0])));

	if (errCheck) {
		printf("Invalid file path provided\n");
	} else {
		printf("CSV has been successfully updated\n");
	}
}