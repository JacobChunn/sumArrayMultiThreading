#ifndef _SUMFUNCTIONS_H_
#define _SUMFUNCTIONS_H_

	extern long long sumArray(int* array, long long arrLen);
	extern void* threadSumArraySection(void* arguments);
	extern long long sumArrayMultithread(int* array, long long arrLen, int threads);
	struct thread_args {
		int* array;
		int threadNum;
		long long sectionLen;
		long long arrLen;
		long long summedSection;
	};

#endif