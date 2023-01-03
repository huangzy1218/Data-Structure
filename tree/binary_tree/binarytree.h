/**
 * @file binarytree.h
 * @author Huang Z.Y.
 * @brief ������(binary tree)�� n ������Ԫ�صļ��ϣ�
 * �ü��ϻ���Ϊ�ա�������һ����Ϊ����root����Ԫ�ؼ��������ཻ�ġ����ֱ��Ϊ���������������Ķ�������ɡ�
 * @version 0.1
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <queue>
#include <stack>
using namespace std;
template <class T>
struct BinTreeNode // �������������
{
    T data; // ������
    BinTreeNode<T>*leftChild, *rightChild; // ����Ů������Ů����
    BinTreeNode()
        : leftChild(nullptr)
        , rightChild(nullptr)
    {
    }
    BinTreeNode(T x, BinTreeNode<T>* l = nullptr, BinTreeNode<T>* r = nullptr)
        : data(x)
        , leftChild(l)
        , rightChild(r)
    {
    }
};

template <class T>
class BinaryTree {
public:
    BinaryTree()
        : root(nullptr)
    {
    } // ���캯��
    BinaryTree(T value)
        : refValue(value)
        , root(nullptr)
    {
    } // ���캯��
    BinaryTree(const BinaryTree<T>& s); // �������캯��
    ~BinaryTree() { destory(root); } // ��������
    bool isEmpty() { return root == nullptr; } // �ж��Ƿ�Ϊ����
    void createBinaryTree(T* VLR, T* LVR, int n, int m); // ����ǰ�����������������������
    BinTreeNode<T>* parent(BinTreeNode<T>* current) //  ���ظ��ڵ�
    { // ��ǰ���Ϊ���ڵ�
        return (root == nullptr || root == current) ? nullptr : parent(root, current);
    }
    BinTreeNode<T>* leftChild(BinTreeNode<T>* current) // ��������Ů
    {
        return (current != nullptr) ? current->leftChild : nullptr;
    }
    BinTreeNode<T>* rightChild(BinTreeNode<T>* current) // ��������Ů
    {
        return (current != nullptr) ? current->rightChild : nullptr;
    }
    void createBinTree(istream& in, BinTreeNode<T>*& subTree, int n); // ����ǰ���������������
    int height() // ��������
    {
        return height(root);
    }
    int size() { return size(root); } // ���ؽ����
    BinTreeNode<T>* getRoot() const { return root; } // ȡ��
    void preOrder() // ǰ�����
    {
        preOrder(root);
    }
    void inOrder() // �������
    {
        preOrder(root);
    }
    void postOrder() // �������
    {
        postOrder(root);
    }
    void output(); // ���
    void levelOrder(); // ��������
    int insert(const T& item); // ������Ԫ��
    BinTreeNode<T>* find(T& item) const; // ����
    BinTreeNode<T>* createBinaryTree(T* VLR, T* LVR, int n); // ����ǰ���������������Ľ������������
    // protected:
    BinTreeNode<T>* root; // �����������
    T refValue; // ����ֹͣ�����־
    void createBinTree(istream& in, BinTreeNode<T>*& subTree); // �����ж��뽨��
    // bool insert(BinTreeNode<T> *&subTree);                                    // ����
    void destory(BinTreeNode<T>*& subTree); // ɾ��
    // bool find(BinTreeNode<T> *subTree, const T &x) const;                     // ����
    BinTreeNode<T>* copy(BinTreeNode<T>* orignode); // ����
    int height(BinTreeNode<T>* subTree) const; // ��������
    int size(BinTreeNode<T>* subTree) const; // ���ؽ����
    BinTreeNode<T>* parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current); // ���ظ����
    BinTreeNode<T>* find(BinTreeNode<T>* subTree, const T& x) const; // ��Ѱx
    void preorderTraverse(); // ǰ��������
    void inorderTraverse(); // ����������
    void postorderTraverse(); // �����������
    void preOrder(BinTreeNode<T>* subTree); // ǰ�����
    void inOrder(BinTreeNode<T>* subTree); // �������
    void postOrder(BinTreeNode<T>* subTree); // �������
    template <class U>
    friend istream& operator>>(istream& in, BinaryTree<U>* tree); // �������������
    template <class U>
    friend ostream& operator<<(ostream& out, BinaryTree<U>& Tree); // ������������
    void visit(BinTreeNode<T>* p);
};

// ���٣�˽�У�
template <class T>
void BinaryTree<T>::destory(BinTreeNode<T>*& subTree)
{
    if (subTree != nullptr) {
        destory(subTree->leftChild);
        destory(subTree->rightChild);
        delete subTree;
    }
};

// ���Ԫ��
template <class T>
void BinaryTree<T>::visit(BinTreeNode<T>* p)
{
    if (p != nullptr) {
        cout << p->data << " ";
    }
};

// ���ظ���㣺�ӽ��subTree��ʼ������current�ĸ����
template <class T>
BinTreeNode<T>* BinaryTree<T>::parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current)
{
    if (subTree == nullptr) {
        return nullptr;
    }
    if (subTree->leftChild == current || subTree->rightChild == current) {
        return subTree;
    }
    BinTreeNode<T>* p;
    if ((p = parent(subTree->leftChild, current)) != nullptr) // �ݹ�������������
    {
        return p;
    } else {
        return parent(subTree->rightChild, current); // �ݹ�������������
    }
};

// ǰ��������
template <class T>
void BinaryTree<T>::preorderTraverse()
{
    std::stack<BinTreeNode<T>*> stk;
    BinTreeNode<T>* p = root;
    stk.push(root);

    while (!stk.empty()) {
        p = stk.top();
        stk.pop();
        visit(p);
        if (p->rightChild != nullptr) {
            stk.push(p->rightChild);
        }
        if (p->leftChild != nullptr) {
            stk.push(p->leftChild);
        }
    }
};

// ����������
template <class T>
void BinaryTree<T>::inorderTraverse()
{
    std::stack<BinTreeNode<T>*> stk;
    BinTreeNode<T>* p = root;

    do {
        while (p != nullptr) {
            stk.push(p);
            p = p->leftChild; // ����ָ��ָ������Ů���
        }
        if (!stk.empty()) {
            p = stk.top();
            stk.pop(); // ��ջ�����ʸ��ڵ�
            visit(p);
            p = p->rightChild; // ��������Ů���
        }
    } while (p != nullptr || !stk.empty());
};

// ����������
template <class T>
void BinaryTree<T>::postorderTraverse()
{
    BinTreeNode<T>*p = root, *r = nullptr;
    std::stack<BinTreeNode<T>*> stk;

    while (p != nullptr || !stk.empty()) {
        if (p != nullptr) {
            stk.push(p);
            p = p->leftChild; // ��������ջ
        } else {
            p = stk.top();
            if (p->rightChild && p->rightChild != r) {
                p = p->rightChild;
                stk.push(p);
                p = p->leftChild;
            } else {
                p = stk.top();
                stk.pop();
                visit(p);
                r = p; // ��Ƿ��ʽ��
                p = nullptr; // �ÿ� p
            }
        }
    }
};

// ���
template <class T>
void BinaryTree<T>::output()
{
    cout << "������ǰ�������" << endl;
    preorderTraverse();
    cout << "\n���������������" << endl;
    inorderTraverse();
    cout << "\n����������������" << endl;
    postorderTraverse();
    cout << "\n���������������" << endl;
    levelOrder();
    cout << endl;
};

// ����һ�Ŷ�����
template <class T>
void BinaryTree<T>::createBinTree(istream& in, BinTreeNode<T>*& bt)
{
    std::stack<BinTreeNode<T>*> stk;
    bt = nullptr; // �ÿն�����
    BinTreeNode<T>*p, *t;
    int k; // �������������ı��
    char ch;
    in >> ch; // �� in ����˳���ȡ�ַ�
    while (ch != refValue) { // ����ַ�����
        switch (ch) {
        case '(': // ��������
            stk.push(p);
            k = 1;
            break;
        case ')': // �˳�����
            t = stk.top();
            stk.pop();
            break;
        case ',':
            k = 2;
            break;
        default:
            p = new BinTreeNode<T>(ch - '0');
            if (bt == nullptr)
                bt = p;
            else if (k == 1) {
                t = stk.top();
                t->leftChild = p;
            } else {
                t = stk.top();
                t->rightChild = p;
            }
        }
        in >> ch;
    }
};

// ���벢����һ�Ŷ�����
template <class T>
istream& operator>>(istream& in, BinaryTree<T>& tree)
{
    tree.createBinTree(in, tree.root);
    return in;
}

// ���һ�Ŷ�����
template <class T>
ostream& operator<<(ostream& out, BinaryTree<T>& tree)
{
    out << "������ǰ�������" << endl;
    tree.preOrder();
    out << "\n���������������" << endl;
    tree.inOrder();
    out << "\n����������������" << endl;
    tree.postOrder();
    out << "\n���������������" << endl;
    tree.levelOrder();
    out << std::endl;
    return out;
};

// ����������󡢸����ң�
template <class T>
void BinaryTree<T>::inOrder(BinTreeNode<T>* subTree)
{
    if (subTree != nullptr) {
        inOrder(subTree->leftChild); // �����������������
        visit(subTree); // ���ʸ����
        inOrder(subTree->rightChild); // �����������������
    }
};

// ǰ��������������ң�
template <class T>
void BinaryTree<T>::preOrder(BinTreeNode<T>* subTree)
{
    if (subTree != nullptr) {
        visit(subTree); // ���ʸ����
        preOrder(subTree->leftChild); // ǰ����ʸ���������
        preOrder(subTree->rightChild); // ǰ����ʸ���������
    }
};

// ������������ҡ�����
template <class T>
void BinaryTree<T>::postOrder(BinTreeNode<T>* subTree)
{
    if (subTree != nullptr) {
        postOrder(subTree->leftChild); // ������ʸ���������
        postOrder(subTree->rightChild); // ������ʸ���������
        visit(subTree); // ���ʸ��ڵ�
    }
};

// ������subTreeΪ���Ķ������Ľ�����
template <class T>
int BinaryTree<T>::size(BinTreeNode<T>* subTree) const
{
    if (subTree == nullptr) {
        return 0;
    } else {
        return 1 + size(subTree->leftChild) + size(subTree->rightChild);
    }
};

// ������subTreeΪ���Ķ�����������
template <class T>
int BinaryTree<T>::height(BinTreeNode<T>* subTree) const
{
    if (subTree == nullptr) {
        return 0;
    } else {
        int i = height(subTree->leftChild) + 1;
        int j = height(subTree->rightChild) + 1;
        return max(i, j);
    }
};

// ���ƹ��캯��
template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& s)
{
    root = copy(s.root);
};

// ����origin�������ĸ���
template <class T>
BinTreeNode<T>* BinaryTree<T>::copy(BinTreeNode<T>* orignode)
{
    if (orignode == nullptr) {
        return nullptr;
    }
    BinTreeNode<T>* temp = new BinTreeNode<T>();
    temp->data = orignode->data;
    temp->leftChild = copy(orignode->leftChild);
    temp->rightChild = copy(orignode->rightChild);
    return temp;
};

// �ж��������Ƿ����
template <class T>
int operator==(const BinaryTree<T>& s, const BinaryTree<T>& t)
{
    return (equal(s.root, t.root)) ? true : false;
};

// �ж������Ƿ����
template <class T>
bool equal(BinTreeNode<T>* a, BinTreeNode<T>* b)
{
    if (a == nullptr && b == nullptr) {
        return true;
    }
    if (a != nullptr && b != nullptr && a->data == b->data && equal(a->leftChild, b->leftChild) && equal(a->rightChild, b->rightChild)) {
        return true;
    }
    return false;
};

// ����ǰ���������������
template <class T>
void BinaryTree<T>::createBinTree(istream& in, BinTreeNode<T>*& subTree, int n)
{
    T item;
    in >> item;
    if (item != refValue) {
        subTree = new BinTreeNode<T>(item);
        if (subTree == nullptr) {
            cerr << "�ڴ�����쳣" << endl;
            exit(1);
        }
        createBinTree(in, subTree->leftChild);
        createBinTree(in, subTree->rightChild);
    } else {
        subTree = nullptr;
    }
};

// �����������ǵݹ飩
template <class T>
void BinaryTree<T>::levelOrder()
{
    std::queue<BinTreeNode<T>*> q;
    BinTreeNode<T>* p = root;
    q.push(p);
    while (!q.empty()) {
        p = q.front();
        q.pop();
        visit(p);
        if (p->leftChild != nullptr) {
            q.push(p->leftChild);
        }
        if (p->rightChild != nullptr) {
            q.push(p->rightChild);
        }
    }
};

// ����ǰ���������������Ľ������������
// ǰ�������ABHFDECKG�������������HBDFAEKCG��
// -->A(HDBF,EKCG) --> A(B(H,DF),EKCG) --> A(B(H,F(D)), EKCG) -->
// A(B(H, F(D)), E(KCG)) --> A(B(H, F(D)), E(C(K,G)))
template <class T>
BinTreeNode<T>* BinaryTree<T>::createBinaryTree(T* VLR, T* LVR, int n)
{
    if (n == 0) {
        return nullptr;
    }
    int k = 0;
    while (VLR[0] != LVR[k]) // �����������Ѱ�Ҹ���λ��
    {
        k++;
    }
    BinTreeNode<T>* t = new BinTreeNode<T>(VLR[0]); // ���������
    t->leftChild = createBinaryTree(VLR + 1, LVR, k); // ����������
    t->rightChild = createBinaryTree(VLR + k + 1, LVR + k + 1, n - k - 1); // ����������
    return t;
};

// ����ǰ���������������Ľ��������������nΪԪ�ظ�����mΪ����ֵ������������
template <class T>
void BinaryTree<T>::createBinaryTree(T* VLR, T* LVR, int n, int m)
{
    // int n = sizeof(VLR) / sizeof(T); �˻�Ϊָ��
    root = createBinaryTree(VLR, LVR, n);
};

#endif