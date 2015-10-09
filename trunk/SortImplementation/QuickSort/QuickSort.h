/**
 * @file 	QuickSort.h
 * @brief 	快速排序算法的实现，使用模版的方式希望能做到尽可能的重用
 * @author 	zhuqingquan
 * @version 1.0.0.0
 * @data 	2014/3/9   14:35
 **/

#pragma once
#ifndef _ZTOOLS_ALGORITHMSIMP_QuickSort_H__
#define _ZTOOLS_ALGORITHMSIMP_QuickSort_H__

#include <algorithm>
#include <cstdlib>
#include <random>
#include <Windows.h>
#include <iterator>

namespace zTools
{
namespace AlgorithmsImp
{
	unsigned long getSeed()
	{
		LARGE_INTEGER la;
		QueryPerformanceCounter(&la);
		return (unsigned long)la.QuadPart;
	}

	int rand(int low, int up)
	{
		srand(getSeed());
		return std::rand() % (up-low) + low;
	}

	template<typename ValueType>
	inline bool CompareFunc_le(const ValueType& lObj, const ValueType& rObj)
	{
		return lObj<=rObj;
	}

	template<typename ValueType>
	class Comparer_le
	{
	public:
		inline bool operator()(const ValueType& lObj, const ValueType& rObj) const
		{
			return lObj<=rObj;
		}
	};

	template<typename ValueType>
	class Comparer_less
	{
	public:
		inline bool operator()(const ValueType& lObj, const ValueType& rObj) const
		{
			return lObj<rObj;
		}
	};

	template<typename ValueType>
	class Comparer_ge
	{
	public:
		inline bool operator()(const ValueType& lObj, const ValueType& rObj) const
		{
			return lObj>=rObj;
		}
	};

	template<typename ValueType>
	class Comparer_greater
	{
	public:
		inline bool operator()(const ValueType& lObj, const ValueType& rObj) const
		{
			return lObj>rObj;
		}
	};

	template<typename ValueType, typename Comparer>
	int partition(ValueType pArray[], int p, int r, const Comparer& cmp)
	{
		int pivot = rand(p,r+1);
		ValueType x = pArray[pivot];
		std::swap(pArray[pivot], pArray[r]);
		int i = p-1;
		for (int j=p; j<r; j++)
		{
			if(cmp(pArray[j],x))
			{
				i++;
				std::swap(pArray[i], pArray[j]);
			}
		}
		std::swap(pArray[i+1], pArray[r]);
		return i+1;
	}

	template<typename ValueType, typename Comparer>
	void QuickSort(ValueType pArray[], int p, int r)
	{
		if(pArray==NULL || p>=r)	return;
		int q = partition(pArray, p, r, Comparer());
		QuickSort<ValueType, Comparer>(pArray, p, q-1);
		QuickSort<ValueType, Comparer>(pArray, q+1, r);
	}

	template<typename Iterator>
	Iterator getPivot_helper(Iterator p, Iterator r, std::input_iterator_tag)
	{
		return r;
	}

	template<typename Iterator>
	Iterator getPivot_helper(Iterator p, Iterator r, std::random_access_iterator_tag)
	{
		std::iterator_traits<Iterator>::difference_type distance = r-p;
		if(distance<=0)
			return r;
		int dist = (int)distance;
		int pivotDist = rand(0, dist);
		return p+pivotDist;
	}

	template<typename Iterator>
	Iterator getPivot(Iterator p, Iterator r)
	{
		return getPivot_helper(p, r, std::iterator_traits<Iterator>::iterator_category());
	}

	template<typename Iterator, typename Comparer>
	Iterator partition(Iterator p, Iterator r, const Comparer& cmp)
	{
		Iterator pivot = getPivot(p, r);
		std::swap(*(r), *pivot);
		Iterator i = r;
		for (Iterator j=p; j!=r; j++)
		{
			if(cmp(*j, *(r)))
			{
				i = i==r ? p : ++i;
				std::swap(*i, *j);
			}
		}
		if(i==r)
			std::swap(*p, *r);
		else
			std::swap(*(i+1), *(r));
		return i==r ? p : i+1;
	}

	template<typename Iterator, typename Comparer>
	void QuickSort(Iterator p, Iterator r)
	{
		if(p>=r)	return;
		Iterator q = zTools::AlgorithmsImp::partition<Iterator, Comparer>(p, r, Comparer());
		if(p!=q)
			QuickSort<Iterator, Comparer>(p, q-1);
		if(q!=r)
			QuickSort<Iterator, Comparer>(q+1, r);
	}

	template<typename ValueType, typename Comparer>
	int partition_EquelRegion(ValueType pArray[], int p, int r, int* erBegin, int* erEnd, const Comparer& cmp)
	{
		int pivot = rand(p,r+1);
		ValueType x = pArray[pivot];
		std::swap(pArray[pivot], pArray[r]);
		int i = p-1;
		int s = p-1;
		for (int j=p; j<r; j++)
		{
			if(cmp(pArray[j],x))
			{
				int oldi = i;
				i++;
				if(s==oldi)
				{
					s = i;
					std::swap(pArray[i], pArray[j]);
				}
				else
				{
					std::swap(pArray[s+1], pArray[j]);
					std::swap(pArray[s+1], pArray[i]);
				}
			}
			else if(pArray[j]==x)
			{
				s++;
				std::swap(pArray[s], pArray[j]);
			}
		}
		std::swap(pArray[r], pArray[i+1]);
		*erBegin = i+1;
		*erEnd = i==s ? i+1 : s;
		return i+1;
	}

	template<typename ValueType, typename Comparer>
	void QuickSort_EqualRegion(ValueType pArray[], int p, int r)
	{
		if(pArray==NULL || p>=r)	return;
		int erBegin = 0;
		int erEnd = 0;
		int q = partition_EquelRegion(pArray, p, r, &erBegin, &erEnd, Comparer());
		QuickSort_EqualRegion<ValueType, Comparer>(pArray, p, erBegin-1);
		QuickSort_EqualRegion<ValueType, Comparer>(pArray, erEnd+1, r);
	}
}
}

#endif // _ZTOOLS_ALGORITHMSIMP_QuickSort_H__