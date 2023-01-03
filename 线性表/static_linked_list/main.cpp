/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of static linked list
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "staticlist.h"
#include <iostream>
using namespace std;
int main(void)
{
    StaticList<int> sl;

    // 追加
    for (int i = 1; i <= 10; i++) {
        sl.append(i);
    }

    // 输出
    sl.output();

    // 插入
    sl.insert(10, 1);

    // 删除
    sl.remove(1); // 下标从 1 开始
    sl.output();

    // 查找
    if (sl.search(1)) {
        cout << "查找成功" << endl;
    } else {
        cout << "查找失败" << endl;
    }

    // 长度
    cout << "静态链表长度：" << sl.length() << endl;

    return 0;
}