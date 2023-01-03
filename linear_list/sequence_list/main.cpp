/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of sequence list
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "seqlist.h"
#include <iostream>
using namespace std;
int main(void)
{
    SeqList<int> sl;

    // 输入
    sl.input();

    // 输出
    sl.output();

    // 插入
    cout << "输入插入位置和元素值" << endl;
    int pos, value;
    cin >> pos >> value;
    sl.insert(pos, value);
    sl.output();

    // 删除
    cout << "输入删除的元素下标" << endl;
    cin >> pos;
    sl.remove(pos, value);
    sl.output();

    // 获取
    cout << "输入元素下标：" << endl;
    cin >> pos;
    sl.getData(pos, value); // 下标从 0 开始
    cout << "下标为" << pos << " 的元素为：" << value << endl;

    // 重置
    cout << "输入要设置的元素下标及值：" << endl;
    cin >> pos >> value;
    sl.setData(pos, value);

    // 长度
    cout << "顺序表长度为：" << sl.length() << endl;

    // 查找
    cout << "输入查找的元素：" << endl;
    cin >> value;
    pos = sl.search(value);
    if (pos == -1) {
        cout << "未查询到该元素" << endl;
    } else {
        cout << "该元素存在" << endl;
    }

    // 排序
    sl.sort();
    cout << "排序后，单链表如下：" << endl;
    sl.output();

    return 0;
}