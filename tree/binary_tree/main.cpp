#include "binarytree.h"

int main()
{
    BinaryTree<int> tree('#');
    cin >> tree;
    cout << tree;
    BinaryTree<int> tree2 = tree;
    cout << "\n�����Ƿ����" << boolalpha << (tree == tree2) << endl;
    cout << "������ȣ�" << tree.height() << endl;
    cout << "���Ľ�������" << tree.size() << endl;
    BinTreeNode<int> *r = tree.getRoot();
    cout << "��ȡ������ֵ��" << r->data << endl;
    cout << "��ȡ����������ֵ��" << tree.leftChild(r)->data << endl;
    cout << "��ȡ���ڵ��ҽ���ֵ��" << tree.rightChild(r)->data << endl;
    cout << "����ǰ��������������������" << endl;
    BinaryTree<int> tree3;
    int pre[5] = {1, 2, 3, 4, 5};
    int in[5] = {1, 2, 3, 4, 5};
    tree3.createBinaryTree(pre, in, 5, 1);
    cout << tree3;

    return 0;
}