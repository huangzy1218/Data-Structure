/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of linked stack
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "LinkedStack.h"

int main(void)
{
    LinkedStack<int> ls;

    // ��ջ
    for (int i = 1; i <= 10; i++)
        ls.push(i);

    // ������������
    cout << ls;

    // ��ȡջ��Ԫ��
    int elem;
    ls.getTop(elem);
    cout << "ջ��Ԫ��Ϊ��" << elem << endl;

    // ��ջ
    ls.pop(elem);
    cout << "��ջԪ��Ϊ��" << elem << endl;
    cout << ls;

    // ��ȡջ��С
    cout << "ջ��С��" << ls.size() << endl;

    return 0;
}