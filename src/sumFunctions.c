#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "sumFunctions.h"

long long sumArray(int* array, long long arrLen) {
	long long sum = 0;
	for (long long i = 0; i < arrLen; i++) {
		sum += array[i];
	}
	return sum;
}

void* threadSumArraySection(void* arguments) {
	struct thread_args *args = (struct thread_args*) arguments;

	int tNum = args->threadNum;
	long long sLen = args->sectionLen;
	long long aLen = args->arrLen;

	long long lower = tNum * sLen;
	// Ensure upper bound is not over length of array
	long long upper = ((tNum + 1) * sLen > aLen) ? aLen : (tNum + 1) * sLen;

	for (long long i = lower; i < upper; i++) {
		args->summedSection += args->array[i];
	}
}

long long sumArrayMultithread(int* array, long long arrLen, int threads) {
	if (threads < 1) return 0;

	long long sum = 0;
	pthread_t thread[threads];
	struct thread_args args[threads];

	for (int i = 0; i < threads; i++) {
		args[i].array = array;
		args[i].threadNum = i;
		args[i].sectionLen = ceil(arrLen / (double)threads); // data loss?
		args[i].arrLen = arrLen;
		args[i].summedSection = 0;

		if (pthread_create(&(thread[i]), 
			NULL, 
			threadSumArraySection, 
			&(args[i])) != 0
		) {
			return -1;
		}
	}
	for (int i = 0; i < threads; i++) {
		pthread_join(thread[i], NULL);
		sum += args[i].summedSection;
	}

	return sum;
}