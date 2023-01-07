/**
 * @file staticsearch.h
 * @author Huang Z.Y.
 * @brief ˳������㷨(Sequential Search)�ֳ�˳�������㷨�������������㷨��
 * �����в����㷨�����������򵥵ġ�˳������㷨�����ھ���������������ұ��д���������л����������У�������ʹ�ô��㷨��
 * ���ֲ���(Binary Search)�ֳ��۰���ҡ������������۰����������뱣֤���ұ��д�ŵ����������У�������߽��򣩡�
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
    int seqSearch(const T x); // ˳������
    int binarySearch(const T x); // �۰�����

private:
    vector<T> elements;
};

// ˳������
template <class T>
int StaticSearch<T>::seqSearch(const T x)
{
    // currentSize ��Ϊ�������������Զ������ġ������ڡ�ʹ�á�
    int currentSize = elements.size();
    int i = 0;

    while (i < currentSize) {
        if (elements[i] == x)
            return i;
        i++;
    }

    return currentSize;
};

// �۰�����
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