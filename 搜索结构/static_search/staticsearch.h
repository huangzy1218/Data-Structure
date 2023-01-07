/**
 * @file staticsearch.h
 * @author Huang Z.Y.
 * @brief 顺序查找算法(Sequential Search)又称顺序搜索算法或者线性搜索算法，
 * 是所有查找算法中最基础、最简单的。顺序查找算法适用于绝大多数场景，查找表中存放有序序列或者无序序列，都可以使用此算法。
 * 二分查找(Binary Search)又称折半查找、二分搜索、折半搜索，必须保证查找表中存放的是有序序列（升序或者降序）。
 * @version 0.1
 * @date 2023-01-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef STATICSEARCH_H
#define STATICSEARCH_H
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class StaticSearch {
public:
    StaticSearch(vector<T>& vect)
        : elements(vect)
    {
    }
    int seqSearch(const T x); // 顺序搜索
    int binarySearch(const T x); // 折半搜索

private:
    vector<T> elements;
};

// 顺序搜索
template <class T>
int StaticSearch<T>::seqSearch(const T x)
{
    // currentSize 作为控制搜索过程自动结束的“监视哨”使用。
    int currentSize = elements.size();
    int i = 0;

    while (i < currentSize) {
        if (elements[i] == x)
            return i;
        i++;
    }

    return currentSize;
};

// 折半搜索
template <class T>
int StaticSearch<T>::binarySearch(const T x)
{
    int high = elements.size() - 1, low = 0, mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if (x > elements[mid])
            low = mid + 1;
        else if (x < elements[mid])
            high = mid - 1;
        else
            return mid;
    }
    return elements.size();
};

#endif