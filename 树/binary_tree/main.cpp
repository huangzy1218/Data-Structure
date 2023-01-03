/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of binary tree
 * @version 0.1
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "binarytree.h"

int main()
{
    BinaryTree<int> tree('#');
    string testBinTree = "1(2(3,4(5,)),6(,7))#";

    // ����
    cin >> tree;

    // ���
    cout << tree;

    // ��ֵ���������
    BinaryTree<int> tree2 = tree;

    // �е�
    cout << "\n�����Ƿ����" << boolalpha << (tree == tree2) << endl;

    // �����
    cout << "������ȣ�" << tree.height() << endl;

    // �ڵ����
    cout << "���Ľ�������" << tree.size() << endl;

    // ��ȡ�����
    BinTreeNode<int>* r = tree.getRoot();
    cout << "��ȡ������ֵ��" << r->data << endl;
    cout << "��ȡ����������ֵ��" << tree.leftChild(r)->data << endl;
    cout << "��ȡ���ڵ��ҽ���ֵ��" << tree.rightChild(r)->data << endl;

    // ����ǰ������������������
    BinaryTree<int> tree3;
    int pre[5] = { 1, 2, 3, 4, 5 };
    int in[5] = { 1, 2, 3, 4, 5 };
    tree3.createBinaryTree(pre, in, 5, 1);
    cout << tree3;

    // �ǵݹ�������
    cout << "�ǵݹ����" << endl;
    tree3.output();

    return 0;
}