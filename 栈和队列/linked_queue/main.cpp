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

    // 入队
    for (int i = 1; i <= 10; i++) {
        lq.enQueue(i);
    }

    // 输出运算符重载
    cout << lq;

    // 获取队首元素
    int elem;
    lq.getFront(elem);
    cout << "队首元素：" << elem << endl;

    // 出队
    lq.deQueue(elem);
    cout << "出队元素：" << elem << endl;

    cout << lq;

    return 0;
}