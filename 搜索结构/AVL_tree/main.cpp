/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of AVL tree
 * @version 0.1
 * @date 2023-01-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "AVLTree.h"

int main(void)
{
    AVLTree<int> tree;

    // 插入
    for (int i = 0; i <= 12; i++)
        tree.insert(i);

    // 输出
    tree.output();

    // 删除
    int val = 8;
    tree.remove(8);
    tree.output();

    // 查找
    if (tree.search(val))
        cout << val << " 存在" << endl;
    else
        cout << val << " 不存在" << endl;

    // 树高
    cout << "树高：" << tree.height() << endl;

    return 0;
}