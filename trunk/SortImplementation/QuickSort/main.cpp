// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>

#define USE_TEMPLATE
#ifdef USE_TEMPLATE
#include "QuickSort.h"

using namespace zTools::AlgorithmsImp;
#else
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition_Increasing_AllSame(int* pArray, int p, int r)
{
	int x = pArray[r];
	int i = p-1;
	for (int j=p; j<r; j++)
	{
		if(pArray[j]<x)
		{
			i++;
			int tmp = pArray[i];
			pArray[i] = pArray[j];
			pArray[j] = tmp;
		}
	}
	int tmp = pArray[r];
	pArray[r] = pArray[i+1];
	pArray[i+1] = tmp;
	return i+1;
}

int partition_EquelRegion(int* pArray, int p, int r, int* erBegin, int* erEnd)
{
	int x = pArray[r];
	int i = p-1;
	int s = p-1;
	for (int j=p; j<r; j++)
	{
		if(pArray[j]>x)
		{
			int oldi = i;
			i++;
			if(s==oldi)
			{
				s = i;
				swap(pArray+i, pArray+j);
			}
			else
			{
				swap(pArray+s+1, pArray+j);
				swap(pArray+s+1, pArray+i);
			}
		}
		else if(pArray[j]==x)
		{
			s++;
			swap(pArray+s, pArray+j);
		}
	}
	swap(pArray+r, pArray+i+1);
	*erBegin = i+1;
	*erEnd = i==s ? i+1 : s;
	return i+1;
}

void QuickSort_EqualRegion(int* pArray, int p, int r)
{
	if(pArray==NULL || p>=r)	return;
	int erBegin = 0;
	int erEnd = 0;
	int q = partition_EquelRegion(pArray, p, r, &erBegin, &erEnd);
	QuickSort_EqualRegion(pArray, p, erBegin-1);
	QuickSort_EqualRegion(pArray, erEnd+1, r);
}

void QuickSort_Increasing(int* pArray, int p, int r)
{
	if(pArray==NULL || p>=r)	return;
	int q = partition_Increasing_AllSame(pArray, p, r);
	QuickSort_Increasing(pArray, p, q-1);
	QuickSort_Increasing(pArray, q+1, r);
}
#endif
#include <assert.h>

int main(int argc, char* argv[])
{
// 	std::default_random_engine engine;
// 	std::normal_distribution<int> dist(10, 100);
// 	for (int i=0; i<100; i++)
// 	{
// 		printf("%d\n", rand(1, 100));
// 	}
// 	getchar();
	int testData[10] = {5, 4, 8, 2, 9, 0, 1, 3, 7, 6};
	int testData1[10] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
	int testData2[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int testData3[10] = {0, 1, 2, 0, 1, 2, 3, 2, 1, 0};
	int testData4[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int testData5[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
#ifdef USE_TEMPLATE
// 	QuickSort<int, Comparer_ge<int>>(testData, 0, 9);
// 	QuickSort<int, Comparer_ge<int>>(testData1, 0, 9);
// 	QuickSort<int, Comparer_ge<int>>(testData2, 0, 9);
// 	QuickSort<int, Comparer_ge<int>>(testData3, 0, 9);
// 	QuickSort<int, Comparer_ge<int>>(testData4, 0, 9);
// 	QuickSort<int, Comparer_ge<int>>(testData5, 0, 9);

	std::vector<int> tdVec0(10);
	memcpy(&tdVec0[0], testData, sizeof(int)*10);
	QuickSort<std::vector<int>::iterator, Comparer_ge<int>>(tdVec0.begin(), tdVec0.end()-1);
	std::vector<int> tdVec1(10);
	memcpy(&tdVec1[0], testData1, sizeof(int)*10);
	QuickSort<std::vector<int>::iterator, Comparer_ge<int>>(tdVec1.begin(), tdVec1.end()-1);
	std::vector<int> tdVec2(10);
	memcpy(&tdVec2[0], testData2, sizeof(int)*10);
	QuickSort<std::vector<int>::iterator, Comparer_ge<int>>(tdVec2.begin(), tdVec2.end()-1);
	std::vector<int> tdVec3(10);
	memcpy(&tdVec3[0], testData3, sizeof(int)*10);
	QuickSort<std::vector<int>::iterator, Comparer_ge<int>>(tdVec3.begin(), tdVec3.end()-1);
	std::vector<int> tdVec4(10);
	memcpy(&tdVec4[0], testData4, sizeof(int)*10);
	QuickSort<std::vector<int>::iterator, Comparer_ge<int>>(tdVec4.begin(), tdVec4.end()-1);
	std::vector<int> tdVec5(10);
	memcpy(&tdVec5[0], testData5, sizeof(int)*10);
	QuickSort<std::vector<int>::iterator, Comparer_ge<int>>(tdVec5.begin(), tdVec5.end()-1);

	std::vector<int> randData;
	for(int i=0; i<1000; i++)
	{
		randData.push_back(rand(1, 800));
	}
	QuickSort<std::vector<int>::iterator, Comparer_ge<int>>(randData.begin(), randData.end()-1);
	int last = -1;
	for (int i=0; i<randData.size(); i++)
	{
		if(last!=-1)
			assert(randData[i]<=last);
		last = randData[i];
	}

// 	QuickSort_EqualRegion<int, Comparer_less<int>>(testData, 0, 9);
// 	QuickSort_EqualRegion<int, Comparer_less<int>>(testData1, 0, 9);
// 	QuickSort_EqualRegion<int, Comparer_less<int>>(testData2, 0, 9);
// 	QuickSort_EqualRegion<int, Comparer_less<int>>(testData3, 0, 9);
// 	QuickSort_EqualRegion<int, Comparer_less<int>>(testData4, 0, 9);
// 	QuickSort_EqualRegion<int, Comparer_less<int>>(testData5, 0, 9);
#else	
	
	QuickSort_EqualRegion(testData, 0, 9);
	QuickSort_EqualRegion(testData1, 0, 9);
	QuickSort_EqualRegion(testData2, 0, 9);
	QuickSort_EqualRegion(testData3, 0, 9);
	QuickSort_EqualRegion(testData4, 0, 9);
	QuickSort_EqualRegion(testData5, 0, 9);

	QuickSort_Increasing(testData, 0, 9);
	QuickSort_Increasing(testData1, 0, 9);
	QuickSort_Increasing(testData2, 0, 9);
	QuickSort_Increasing(testData3, 0, 9);
	QuickSort_Increasing(testData4, 0, 9);
	QuickSort_Increasing(testData5, 0, 9);
#endif
	return 0;
}

