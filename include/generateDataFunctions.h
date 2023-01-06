#ifndef _GENERATEDATAFUNCTIONS_H_
#define _GENERATEDATAFUNCTIONS_H_

	extern void populateArray(int* array, long long arrLen, int range);
	extern double timeSumArray(int* array, long long arrLen, int threads);
	extern int appendtimeSumArrayOverParamsToCSV(
		char* filePath,
		int range,
		int trials,
		long long* arrLens,
		int arrLensLen,
		int* threadCounts,
		int threadCountsLen);
	extern void compareSumArrayAndSumArrayMultithread(long long size,
		int range,
		int threads);

#endif