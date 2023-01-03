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

    // 入栈
    for (int i = 1; i <= 10; i++) {
        ss.push(i);
    }

    // 输出运算符重载
    cout << ss;

    // 获取栈顶元素
    int elem;
    ss.getTop(elem);

    cout << "栈顶元素：" << elem << endl;

    // 出栈
    ss.pop(elem);
    cout << "出栈元素：" << elem << endl;
    cout << ss;

    // 栈大小
    cout << "栈大小：" << ss.size() << endl;

    return 0;
}