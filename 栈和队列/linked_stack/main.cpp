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

    // 入栈
    for (int i = 1; i <= 10; i++)
        ls.push(i);

    // 输出运算符重载
    cout << ls;

    // 获取栈顶元素
    int elem;
    ls.getTop(elem);
    cout << "栈顶元素为：" << elem << endl;

    // 出栈
    ls.pop(elem);
    cout << "出栈元素为：" << elem << endl;
    cout << ls;

    // 获取栈大小
    cout << "栈大小：" << ls.size() << endl;

    return 0;
}