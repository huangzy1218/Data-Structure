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

    // 入队列
    for (int i = 1; i <= 10; i++) {
        sq.enQueue(i);
    }

    // 输出运算符重载
    cout << sq;

    // 获取队首元素
    int elem;
    sq.getFront(elem);
    cout << "队首元素：" << elem << endl;

    // 出队
    sq.deQueue(elem);
    cout << "出队元素：" << elem << endl;

    cout << sq;

    return 0;
}