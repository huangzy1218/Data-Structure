/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of general list
 * @version 0.1
 * @date 2023-01-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "GenList.h"

int main()
{
    GenList<char> genList;

    // ��������� a,(#),b,c,(d,(e));
    genList.createGenList();

    // �������
    genList.traverse();

    // ����
    char target = 'a';
    if (genList.find(target)) {
        cout << "���ҵ� " << target << endl;
    } else {
        cout << "δ���ҵ� " << target << endl;
    }

    // ����
    GenList<char> demo = genList.copy();

    // ������
    demo.output();

    return 0;
}