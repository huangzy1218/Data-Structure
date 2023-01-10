/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of binary search tree
 * @version 0.1
 * @date 2023-01-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "BST.h"

int main(void)
{
    BST<char> tree('#');

    // 输入
    tree.input(); // g a e d f h j i l k #

    // 输出
    tree.output();

    // 插入
    char val = 'b';
    tree.insert(val);
    tree.output();

    // 删除
    tree.remove(val);

    // 查找
    if (tree.search(val))
        cout << val << " 存在" << endl;
    else
        cout << val << " 不存在" << endl;

    return 0;
}