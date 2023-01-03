/**
 * @file binarytree.h
 * @author Huang Z.Y.
 * @brief 二叉树(binary tree)是 n 个有限元素的集合，
 * 该集合或者为空、或者由一个称为根（root）的元素及两个不相交的、被分别称为左子树和右子树的二叉树组成。
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
struct BinTreeNode // 二叉树结点类型
{
    T data; // 数据域
    BinTreeNode<T>*leftChild, *rightChild; // 左子女，右子女链域
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
    } // 构造函数
    BinaryTree(T value)
        : refValue(value)
        , root(nullptr)
    {
    } // 构造函数
    BinaryTree(const BinaryTree<T>& s); // 拷贝构造函数
    ~BinaryTree() { destory(root); } // 析构函数
    bool isEmpty() { return root == nullptr; } // 判断是否为空树
    void createBinaryTree(T* VLR, T* LVR, int n, int m); // 利用前序和中序遍历结果构建二叉树
    BinTreeNode<T>* parent(BinTreeNode<T>* current) //  返回父节点
    { // 当前结点为根节点
        return (root == nullptr || root == current) ? nullptr : parent(root, current);
    }
    BinTreeNode<T>* leftChild(BinTreeNode<T>* current) // 返回左子女
    {
        return (current != nullptr) ? current->leftChild : nullptr;
    }
    BinTreeNode<T>* rightChild(BinTreeNode<T>* current) // 返回右子女
    {
        return (current != nullptr) ? current->rightChild : nullptr;
    }
    void createBinTree(istream& in, BinTreeNode<T>*& subTree, int n); // 利用前序遍历创建二叉树
    int height() // 返回树高
    {
        return height(root);
    }
    int size() { return size(root); } // 返回结点数
    BinTreeNode<T>* getRoot() const { return root; } // 取根
    void preOrder() // 前序遍历
    {
        preOrder(root);
    }
    void inOrder() // 中序遍历
    {
        preOrder(root);
    }
    void postOrder() // 后序遍历
    {
        postOrder(root);
    }
    void output(); // 输出
    void levelOrder(); // 层次序遍历
    int insert(const T& item); // 插入新元素
    BinTreeNode<T>* find(T& item) const; // 搜索
    BinTreeNode<T>* createBinaryTree(T* VLR, T* LVR, int n); // 根据前序遍历和中序遍历的结果构建二叉树
    // protected:
    BinTreeNode<T>* root; // 二叉树根结点
    T refValue; // 数据停止输入标志
    void createBinTree(istream& in, BinTreeNode<T>*& subTree); // 从流中读入建树
    // bool insert(BinTreeNode<T> *&subTree);                                    // 插入
    void destory(BinTreeNode<T>*& subTree); // 删除
    // bool find(BinTreeNode<T> *subTree, const T &x) const;                     // 查找
    BinTreeNode<T>* copy(BinTreeNode<T>* orignode); // 复制
    int height(BinTreeNode<T>* subTree) const; // 返回树高
    int size(BinTreeNode<T>* subTree) const; // 返回结点树
    BinTreeNode<T>* parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current); // 返回父结点
    BinTreeNode<T>* find(BinTreeNode<T>* subTree, const T& x) const; // 搜寻x
    void preorderTraverse(); // 前序遍历输出
    void inorderTraverse(); // 中序遍历输出
    void postorderTraverse(); // 后续遍历输出
    void preOrder(BinTreeNode<T>* subTree); // 前序遍历
    void inOrder(BinTreeNode<T>* subTree); // 中序遍历
    void postOrder(BinTreeNode<T>* subTree); // 后序遍历
    template <class U>
    friend istream& operator>>(istream& in, BinaryTree<U>* tree); // 输入运算符重载
    template <class U>
    friend ostream& operator<<(ostream& out, BinaryTree<U>& Tree); // 输出运算符重载
    void visit(BinTreeNode<T>* p);
};

// 销毁（私有）
template <class T>
void BinaryTree<T>::destory(BinTreeNode<T>*& subTree)
{
    if (subTree != nullptr) {
        destory(subTree->leftChild);
        destory(subTree->rightChild);
        delete subTree;
    }
};

// 输出元素
template <class T>
void BinaryTree<T>::visit(BinTreeNode<T>* p)
{
    if (p != nullptr) {
        cout << p->data << " ";
    }
};

// 返回父结点：从结点subTree开始，搜索current的父结点
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
    if ((p = parent(subTree->leftChild, current)) != nullptr) // 递归在左子树搜索
    {
        return p;
    } else {
        return parent(subTree->rightChild, current); // 递归在右子树搜索
    }
};

// 前序遍历输出
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

// 中序遍历输出
template <class T>
void BinaryTree<T>::inorderTraverse()
{
    std::stack<BinTreeNode<T>*> stk;
    BinTreeNode<T>* p = root;

    do {
        while (p != nullptr) {
            stk.push(p);
            p = p->leftChild; // 遍历指针指向左子女结点
        }
        if (!stk.empty()) {
            p = stk.top();
            stk.pop(); // 退栈，访问根节点
            visit(p);
            p = p->rightChild; // 访问右子女结点
        }
    } while (p != nullptr || !stk.empty());
};

// 后序遍历输出
template <class T>
void BinaryTree<T>::postorderTraverse()
{
    BinTreeNode<T>*p = root, *r = nullptr;
    std::stack<BinTreeNode<T>*> stk;

    while (p != nullptr || !stk.empty()) {
        if (p != nullptr) {
            stk.push(p);
            p = p->leftChild; // 左子树入栈
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
                r = p; // 标记访问结点
                p = nullptr; // 置空 p
            }
        }
    }
};

// 输出
template <class T>
void BinaryTree<T>::output()
{
    cout << "二叉树前序遍历：" << endl;
    preorderTraverse();
    cout << "\n二叉树中序遍历：" << endl;
    inorderTraverse();
    cout << "\n二叉树后续遍历：" << endl;
    postorderTraverse();
    cout << "\n二叉树层序遍历：" << endl;
    levelOrder();
    cout << endl;
};

// 建立一颗二叉树
template <class T>
void BinaryTree<T>::createBinTree(istream& in, BinTreeNode<T>*& bt)
{
    std::stack<BinTreeNode<T>*> stk;
    bt = nullptr; // 置空二叉树
    BinTreeNode<T>*p, *t;
    int k; // 处理左右子树的标记
    char ch;
    in >> ch; // 从 in 流中顺序读取字符
    while (ch != refValue) { // 逐个字符处理
        switch (ch) {
        case '(': // 进入子树
            stk.push(p);
            k = 1;
            break;
        case ')': // 退出子树
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

// 输入并创建一颗二叉树
template <class T>
istream& operator>>(istream& in, BinaryTree<T>& tree)
{
    tree.createBinTree(in, tree.root);
    return in;
}

// 输出一颗二叉树
template <class T>
ostream& operator<<(ostream& out, BinaryTree<T>& tree)
{
    out << "二叉树前序遍历：" << endl;
    tree.preOrder();
    out << "\n二叉树中序遍历：" << endl;
    tree.inOrder();
    out << "\n二叉树后续遍历：" << endl;
    tree.postOrder();
    out << "\n二叉树层序遍历：" << endl;
    tree.levelOrder();
    out << std::endl;
    return out;
};

// 中序遍历（左、根、右）
template <class T>
void BinaryTree<T>::inOrder(BinTreeNode<T>* subTree)
{
    if (subTree != nullptr) {
        inOrder(subTree->leftChild); // 中序遍历根的左子树
        visit(subTree); // 访问根结点
        inOrder(subTree->rightChild); // 中序遍历根的右子树
    }
};

// 前序遍历（根、左、右）
template <class T>
void BinaryTree<T>::preOrder(BinTreeNode<T>* subTree)
{
    if (subTree != nullptr) {
        visit(subTree); // 访问根结点
        preOrder(subTree->leftChild); // 前序访问根的左子树
        preOrder(subTree->rightChild); // 前序访问根的右子树
    }
};

// 后序遍历（左、右、根）
template <class T>
void BinaryTree<T>::postOrder(BinTreeNode<T>* subTree)
{
    if (subTree != nullptr) {
        postOrder(subTree->leftChild); // 后序访问根的左子树
        postOrder(subTree->rightChild); // 后序访问根的右子树
        visit(subTree); // 访问根节点
    }
};

// 计算以subTree为根的二叉树的结点个数
template <class T>
int BinaryTree<T>::size(BinTreeNode<T>* subTree) const
{
    if (subTree == nullptr) {
        return 0;
    } else {
        return 1 + size(subTree->leftChild) + size(subTree->rightChild);
    }
};

// 计算以subTree为根的二叉树的树高
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

// 复制构造函数
template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& s)
{
    root = copy(s.root);
};

// 返回origin二叉树的副本
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

// 判断两棵树是否相等
template <class T>
int operator==(const BinaryTree<T>& s, const BinaryTree<T>& t)
{
    return (equal(s.root, t.root)) ? true : false;
};

// 判断两树是否相等
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

// 利用前序遍历建立二叉树
template <class T>
void BinaryTree<T>::createBinTree(istream& in, BinTreeNode<T>*& subTree, int n)
{
    T item;
    in >> item;
    if (item != refValue) {
        subTree = new BinTreeNode<T>(item);
        if (subTree == nullptr) {
            cerr << "内存分配异常" << endl;
            exit(1);
        }
        createBinTree(in, subTree->leftChild);
        createBinTree(in, subTree->rightChild);
    } else {
        subTree = nullptr;
    }
};

// 层次序遍历（非递归）
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

// 根据前序遍历和中序遍历的结果构建二叉树
// 前序遍历（ABHFDECKG），中序遍历（HBDFAEKCG）
// -->A(HDBF,EKCG) --> A(B(H,DF),EKCG) --> A(B(H,F(D)), EKCG) -->
// A(B(H, F(D)), E(KCG)) --> A(B(H, F(D)), E(C(K,G)))
template <class T>
BinTreeNode<T>* BinaryTree<T>::createBinaryTree(T* VLR, T* LVR, int n)
{
    if (n == 0) {
        return nullptr;
    }
    int k = 0;
    while (VLR[0] != LVR[k]) // 在中序遍历中寻找根的位置
    {
        k++;
    }
    BinTreeNode<T>* t = new BinTreeNode<T>(VLR[0]); // 创建根结点
    t->leftChild = createBinaryTree(VLR + 1, LVR, k); // 构建左子树
    t->rightChild = createBinaryTree(VLR + k + 1, LVR + k + 1, n - k - 1); // 构建右子树
    return t;
};

// 根据前序遍历和中序遍历的结果构建二叉树，n为元素个数，m为任意值，起到区分作用
template <class T>
void BinaryTree<T>::createBinaryTree(T* VLR, T* LVR, int n, int m)
{
    // int n = sizeof(VLR) / sizeof(T); 退化为指针
    root = createBinaryTree(VLR, LVR, n);
};

#endif