/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of general list
 * @version 0.1
 * @date 2023-01-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "GenList.h"

int main()
{
    GenList<char> genList;

    // 创建广义表 a,(#),b,c,(d,(e));
    genList.createGenList();

    // 遍历输出
    genList.traverse();

    // 查找
    char target = 'a';
    if (genList.find(target)) {
        cout << "查找到 " << target << endl;
    } else {
        cout << "未查找到 " << target << endl;
    }

    // 拷贝
    GenList<char> demo = genList.copy();

    // 层次输出
    demo.output();

    return 0;
}