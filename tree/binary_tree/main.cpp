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

    // 输入
    cin >> tree;

    // 输出
    cout << tree;

    // 赋值运算符重载
    BinaryTree<int> tree2 = tree;

    // 判等
    cout << "\n两树是否相等" << boolalpha << (tree == tree2) << endl;

    // 树深度
    cout << "树的深度：" << tree.height() << endl;

    // 节点个数
    cout << "树的结点个数：" << tree.size() << endl;

    // 获取根结点
    BinTreeNode<int>* r = tree.getRoot();
    cout << "获取根结点的值：" << r->data << endl;
    cout << "获取根结点左结点的值：" << tree.leftChild(r)->data << endl;
    cout << "获取根节点右结点的值：" << tree.rightChild(r)->data << endl;

    // 根据前序遍历结果建立二叉树
    BinaryTree<int> tree3;
    int pre[5] = { 1, 2, 3, 4, 5 };
    int in[5] = { 1, 2, 3, 4, 5 };
    tree3.createBinaryTree(pre, in, 5, 1);
    cout << tree3;

    // 非递归遍历输出
    cout << "非递归输出" << endl;
    tree3.output();

    return 0;
}