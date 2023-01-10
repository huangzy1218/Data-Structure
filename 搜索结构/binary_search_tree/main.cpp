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

    // ����
    tree.input(); // g a e d f h j i l k #

    // ���
    tree.output();

    // ����
    char val = 'b';
    tree.insert(val);
    tree.output();

    // ɾ��
    tree.remove(val);

    // ����
    if (tree.search(val))
        cout << val << " ����" << endl;
    else
        cout << val << " ������" << endl;

    return 0;
}