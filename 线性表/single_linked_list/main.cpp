/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of single linked list
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "List.h"
#include <iostream>
using namespace std;
int main(void)
{
    List<int> l;

    // 输入
    l.input();

    // 输出
    l.output();

    // 插入
    cout << "输入插入位置和元素值" << endl;
    int pos, value;
    cin >> pos >> value;
    l.insert(pos, value);
    l.output();

    // 删除
    cout << "输入需删除的元素下标" << endl;
    cin >> pos;
    l.remove(pos, value);
    l.output();

    // 获取
    cout << "输入元素下标：" << endl;
    cin >> pos;
    l.getData(pos, value); // 链表下标从1开始，而输入下标从1
    cout << "下标: " << pos << " 值: " << value << endl;

    // 设置
    cout << "输入要设置的元素下标及值：" << endl;
    cin >> pos >> value;
    l.setData(pos, value);

    // 长度
    cout << "单链表长度为：" << l.length() << endl;

    // 查找
    cout << "输入所要查找的元素：" << endl;
    cin >> value;
    LinkNode<int>* ptr = l.search(value);
    if (ptr == NULL) {
        cout << "未查询到该元素" << endl;
    } else {
        cout << "该元素存在" << endl;
    }

    // 排序
    l.sort();
    cout << "排序后，单链表如下：" << endl;
    l.output();

    return 0;
}