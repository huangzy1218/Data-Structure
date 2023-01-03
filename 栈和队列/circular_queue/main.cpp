/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of circular list
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "seqqueue.h"

int main(void)
{
    SeqQueue<int> sq;

    // �����
    for (int i = 1; i <= 10; i++) {
        sq.enQueue(i);
    }

    // ������������
    cout << sq;

    // ��ȡ����Ԫ��
    int elem;
    sq.getFront(elem);
    cout << "����Ԫ�أ�" << elem << endl;

    // ����
    sq.deQueue(elem);
    cout << "����Ԫ�أ�" << elem << endl;

    cout << sq;

    return 0;
}