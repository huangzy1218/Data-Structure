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

#include "SeqStack.h"
using namespace std;
int main(void)
{
    SeqStack<int> ss;

    // ��ջ
    for (int i = 1; i <= 10; i++) {
        ss.push(i);
    }

    // ������������
    cout << ss;

    // ��ȡջ��Ԫ��
    int elem;
    ss.getTop(elem);

    cout << "ջ��Ԫ�أ�" << elem << endl;

    // ��ջ
    ss.pop(elem);
    cout << "��ջԪ�أ�" << elem << endl;
    cout << ss;

    // ջ��С
    cout << "ջ��С��" << ss.size() << endl;

    return 0;
}