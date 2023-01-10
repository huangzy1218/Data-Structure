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

    // ����
    for (int i = 0; i <= 12; i++)
        tree.insert(i);

    // ���
    tree.output();

    // ɾ��
    int val = 8;
    tree.remove(8);
    tree.output();

    // ����
    if (tree.search(val))
        cout << val << " ����" << endl;
    else
        cout << val << " ������" << endl;

    // ����
    cout << "���ߣ�" << tree.height() << endl;

    return 0;
}