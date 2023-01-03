/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of linked queue
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "LinkedQueue.h"

int main(void)
{
    LinkedQueue<int> lq;

    // ���
    for (int i = 1; i <= 10; i++) {
        lq.enQueue(i);
    }

    // ������������
    cout << lq;

    // ��ȡ����Ԫ��
    int elem;
    lq.getFront(elem);
    cout << "����Ԫ�أ�" << elem << endl;

    // ����
    lq.deQueue(elem);
    cout << "����Ԫ�أ�" << elem << endl;

    cout << lq;

    return 0;
}