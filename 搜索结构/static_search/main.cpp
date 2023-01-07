/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of sequence search and binary search
 * @version 0.1
 * @date 2023-01-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "staticsearch.h"
#include <iostream>

int main(void)
{
    vector<int> vect(10);
    for (int i = 0; i < 10; i++) {
        vect[i] = i + 1;
    }
    StaticSearch<int> ss(vect);

    int target = 1;
    // ˳�����
    int index = ss.seqSearch(target);
    cout << index << endl;

    // ���ֲ���
    index = ss.binarySearch(target);
    cout << index << endl;

    return 0;
}