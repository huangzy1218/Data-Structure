#include "binarytree.h"

int main()
{
    BinaryTree<int> tree('#');
    cin >> tree;
    cout << tree;
    BinaryTree<int> tree2 = tree;
    cout << "\n两树是否相等" << boolalpha << (tree == tree2) << endl;
    cout << "树的深度：" << tree.height() << endl;
    cout << "树的结点个数：" << tree.size() << endl;
    BinTreeNode<int> *r = tree.getRoot();
    cout << "获取根结点的值：" << r->data << endl;
    cout << "获取根结点左结点的值：" << tree.leftChild(r)->data << endl;
    cout << "获取根节点右结点的值：" << tree.rightChild(r)->data << endl;
    cout << "根据前序遍历结果建立二叉树：" << endl;
    BinaryTree<int> tree3;
    int pre[5] = {1, 2, 3, 4, 5};
    int in[5] = {1, 2, 3, 4, 5};
    tree3.createBinaryTree(pre, in, 5, 1);
    cout << tree3;

    return 0;
}