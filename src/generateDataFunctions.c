#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generateDataFunctions.h"
#include "sumFunctions.h"

void populateArray(int* array, long long arrLen, int range) {
	for (long long i = 0; i < arrLen; i++) {
		array[i] = (rand() % (range * 2 + 1)) - range;
	}
}

double timeSumArray(int* array, long long arrLen, int threads) {
	struct timespec start, end;
	double time;

	if (threads < 1) {
		clock_gettime(CLOCK_MONOTONIC, &start);
		sumArray(array, arrLen);
		clock_gettime(CLOCK_MONOTONIC, &end);
	} else {
		clock_gettime(CLOCK_MONOTONIC, &start);
		sumArrayMultithread(array, arrLen, threads);
		clock_gettime(CLOCK_MONOTONIC, &end);
	}

	time = (end.tv_sec - start.tv_sec)
		+ (end.tv_nsec - start.tv_nsec) / 1000000000.0;

	return time;

}

int appendtimeSumArrayOverParamsToCSV(
	char* filePath,
	int range,
	int trials,
	long long* arrLens,
	int arrLensLen,
	int* threadCounts,
	int threadCountsLen) {
	
	int *arr;
	long long size;
	long double time;
	FILE* fp = fopen(filePath, "w");

	if (fp == NULL) return 1;

	fprintf(fp, "Array Size:,");
	for (int i = 0; i < arrLensLen - 1; i++) {
		fprintf(fp, "%lld,", arrLens[i]);
	}
	fprintf(fp, "%lld\n", arrLens[arrLensLen - 1]);

	fprintf(fp, "SumArray (no multithreading),");
	for (int i = 0; i < arrLensLen; i++) {
		size = arrLens[i];
		arr = (int*)malloc(size * sizeof(int));
		time = 0.0;

		for (int j = 0; j < trials; j++) {
			populateArray(arr, size, range);
			time += timeSumArray(arr, size, -1);
		}

		time /= trials;

		if (i != arrLensLen - 1) {
			fprintf(fp, "%Lf,", time);
		} else {
			fprintf(fp, "%Lf\n", time);
		}

		free(arr);
	}

	fprintf(fp, "Thread Count:,\n");

	for (int i = 0; i < threadCountsLen; i++) {
		fprintf(fp, "%d,", threadCounts[i]);

		for (int j = 0; j < arrLensLen; j++) {
			size = arrLens[j];
			arr = (int*)malloc(size * sizeof(int));
			time = 0.0;

			for (int j = 0; j < trials; j++) {
				populateArray(arr, size, range);
				time += timeSumArray(arr, size, threadCounts[i]);
			}

			time /= trials;

			if (j != arrLensLen - 1) {
				fprintf(fp, "%Lf,", time);
			} else {
				fprintf(fp, "%Lf\n", time);
			}

			free(arr);
		}
	}
	fclose(fp);
	return 0;
}

void compareSumArrayAndSumArrayMultithread(
	long long size,
	int range,
	int threads) {

	struct timespec s1, e1, s2, e2;
	double timeSA, timeSAMT;
	int *arr = (int*)malloc(size * sizeof(int));

	populateArray(arr, size, range);

	clock_gettime(CLOCK_MONOTONIC, &s1);
	long long int sumSA = sumArray(arr, size);
	clock_gettime(CLOCK_MONOTONIC, &e1);

	clock_gettime(CLOCK_MONOTONIC, &s2);
	long long int sumSAMT = sumArrayMultithread(arr, size, threads);
	clock_gettime(CLOCK_MONOTONIC, &e2);

	printf("Size of array sorted: %lld\n", size);

	printf("sumArray function on arr yields: %lld\n",
		sumSA
	);

	timeSA = (e1.tv_sec - s1.tv_sec)
		+ (e1.tv_nsec - s1.tv_nsec) / 1000000000.0;
	printf("TIME: %f\n", timeSA);

	printf("sumArrayMultithread function with %d threads on arr yields: %lld\n",
		threads,
		sumSAMT
	);

	timeSAMT = (e2.tv_sec - s2.tv_sec)
		+ (e2.tv_nsec - s2.tv_nsec) / 1000000000.0;
	printf("TIME: %f\n", timeSAMT);

	free(arr);
}