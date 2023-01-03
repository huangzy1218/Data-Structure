/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of double linked list
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "DblList.h"
#include <iostream>
using namespace std;
int main(void)
{
    DblList<int> dl;

    // 输入
    dl.input();

    // 输出
    dl.output();

    // 插入
    cout << "输入插入位置和元素值" << endl;
    int pos, value;
    cin >> pos >> value;
    dl.insert(pos, value);
    dl.output();

    // 删除
    cout << "输入需删除的元素下标" << endl;
    cin >> pos;
    dl.remove(pos, value);
    dl.output();

    // 获取
    cout << "请输入元素下标：" << endl;
    cin >> pos;
    dl.getData(pos, value); // 链表下标从1开始，而输入下标从1
    cout << "下标: " << pos << " 值: " << value << endl;

    // 获取前驱
    cin >> pos;
    cout << dl.getPreData(pos) << endl;

    // 获取后继
    cin >> pos;
    cout << dl.getNextData(pos) << endl;

    // 设置
    cout << "输入要设置的元素下标及值：" << endl;
    cin >> pos >> value;
    dl.setData(pos, value);

    // 长度
    cout << "双向链表长度为：" << dl.length() << endl;

    // 查找
    cout << "输入所要查找的元素：" << endl;
    cin >> value;
    DblNode<int>* ptr = dl.search(value);
    if (ptr == NULL) {
        cout << "未查询到该元素" << endl;
    } else {
        cout << "该元素存在" << endl;
    }

    // 排序
    dl.sort();
    cout << "排序后，单链表如下：" << endl;
    dl.output();

    return 0;
}