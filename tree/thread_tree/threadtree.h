#include <iostream>
// 线索二叉树类的结点
template <class T>
struct ThreadNode {
    int ltag, rtag; // 线索标签
    // tag == 0表示存放指向左子女的指针
    // tga == 1表示存放指向该结点前驱的线索
    ThreadNode<T>*leftChild, *rightChild; // 线索或子女指针
    T data; // 结点中包含的数据
    ThreadNode(const T item)
        : data(item)
        , leftChild(NULL)
        , rightChild(NULL)
        , ltag(0)
        , rtag(0)
    {
    }
};

// 线索化二叉树
template <class T>
class ThreadTree {
protected:
    ThreadNode<T>* root; // 树的根结点
    void createInThread(ThreadNode<T>* current, ThreadNode<T>*& pre);
    // 中序建立二叉树
    ThreadNode<T>* parent(ThreadNode<T>* t); // 寻找结点t的父结点
    void vist(ThreadNode<T>* p) // 遍历
    {
        std::cout << p->data << ' ';
    }

public:
    ThreadTree()
        : root(NULL)
    {
    } // 构造函数：构造空树
    void createInThread(); // 建立中序线索二叉树
    ThreadNode<T>* first(ThreadNode<T>* current); // 寻找中序下的第一个结点
    ThreadNode<T>* last(ThreadNode<T>* current); // 寻找中序下的最后一个结点
    ThreadNode<T>* next(ThreadNode<T>* current); // 寻找中序下的下一个结点
    ThreadNode<T>* prior(ThreadNode<T>* current); // 寻找中序下的前驱结点
    void inOrder(); // 中序遍历
    void preOrder(); // 前序遍历
    void postOrder(); // 后序遍历
};

// 寻找中序下的第一个结点
template <class T>
ThreadNode<T>* ThreadTree<T>::first(ThreadNode<T>* current)
{
    ThreadNode<T>* p = current;
    while (p->ltag == 0) {
        p = p->leftChild;
    }
    return p;
};

// 寻找中序下的下一个结点
template <class T>
ThreadNode<T>* ThreadTree<T>::next(ThreadNode<T>* current)
{
    ThreadNode<T>* p = current->rightChild;
    if (current->rtag == 0) {
        return first(p);
    } else {
        return p;
    }
};

// 寻找中序下的最后一个结点
template <class T>
ThreadNode<T>* ThreadTree<T>::last(ThreadNode<T>* current)
{
    ThreadNode<T>* p = current;
    while (p->rtag == 0) {
        p = p->rightChild;
    }
    return p;
};

// 寻找中序下的前驱结点
template <class T>
ThreadNode<T>* ThreadTree<T>::prior(ThreadNode<T>* current)
{
    ThreadNode<T>* p = current->leftChild;
    if (current->ltag == 0) {
        return last(p);
    } else {
        return p;
    }
};

// 中序遍历
template <class T>
void ThreadTree<T>::inOrder()
{
    ThreadNode<T>* p;
    for (p = first(root); p != NULL; p = next(p)) {
        visit(p);
    }
};

// 利用中序遍历对二叉树进行中序线索化
template <class T>
void ThreadTree<T>::createInThread()
{
    ThreadNode<T>* pre = NULL;
    if (root != NULL) {
        createInThread(root, pre);
        pre->rightChild = NULL;
        pre->rtag = 1; // 后处理中序的最后一个结点
    }
};

// 通过中序遍历，对二叉树线索化
// current表示当前结点，pre表示前驱结点
template <class T>
void ThreadTree<T>::createInThread(ThreadNode<T>* current, ThreadNode<T>*& pre)
{
    if (current == NULL) {
        return;
    }
    createInThread(current->leftChild, pre); // 左子树线索化
    if (current->leftChild == NULL) // 无左孩子，建立当前结点的前驱线索
    {
        current->leftChild = pre;
        current->ltag = 1;
    }
    if (pre != NULL && pre->rightChild == NULL) // 建立前驱线索的后继线索
    {
        pre->rightChild = current;
        pre->rtag = 1;
    }
    pre = current; // pre永远指向前驱结点
    createInThread(current->rightChild, pre); // 右子树线索化
};

// 在中序线索二叉树上实现前序遍历算法
template <class T>
void ThreadTree<T>::preOrder()
{
    ThreadNode<T>* p = root;
    while (p != NULL) {
        visit(p); // 访问根结点
        if (p->ltag == 0) // 有左子女
        {
            p = p->leftChild;
        } else if (p->rtag == 0) // 有有子女
        {
            p = p->rightChild;
        } else {
            while (p != NULL && p->rtag == 1) // 沿后继线索检测
            {
                p = p->rightChild; // 直到有右子女的结点
            }
            if (p != NULL) {
                p = p->rightChild; // 右子女即为后继
            }
        }
    }
};

// 在中序线索二叉树上实现后序遍历算法
template <class T>
void ThreadTree<T>::postOrder()
{
    ThreadNode<T>* t = root;
    while (t->ltag == 0 || t->rtag == 0) // 访问后继的第一个结点
    {
        if (t->ltag == 0) {
            t = t->leftChild;
        } else if (t->rtag == 0) {
            t = t->rightChild;
        }
    }
    visit(t); // 访问第一个结点
    ThreadNode<T>* p;
    while ((p = parent(t)) != NULL) {
        if (p->rightChild == t || p->rtag == 1) // t是p的后继或后驱
        // p->rtag == 1表明p无右子树，直接遍历p
        {
            t = p;
        } else // 为左子女
        {
            t = p->rightChild; // t提到p的右子树
            while (t->ltag == 0 || t->rtag == 0) {
                if (t->ltag == 0) {
                    t = t->leftChild;
                } else if (t->rtag == 0) {
                    t = t->rightChild;
                }
            }
        }
        vist(t);
    }
};

// 寻找结点t的父结点
template <class T>
ThreadNode<T>* ThreadTree<T>::parent(ThreadNode<T>* t)
{
    ThreadNode<T>* p;
    if (t == root) {
        return NULL; // 根节点无父结点
    }
    for (p = t; p->ltag == 0; p = p->leftChild)
        ;
    if (p->leftChild != NULL) // 未走到中序遍历的第一个结点
    {
        for (p = p->leftChild; p != NULL && p->leftChild != t && p->rightChild != t; p = p->rightChild)
            ;
    }
    if (p == NULL || p->leftChild == NULL) // 未走到中序遍历的最后一个结点
    {
        for (p = t; p->rtag == 0; p = p->rightChild)
            ;
        for (p = p->rightChild; p != NULL && p->leftChild != t && p->rightChild != t; p = p->leftChild)
            ;
    }
    return p;
};
