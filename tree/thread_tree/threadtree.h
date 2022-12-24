#include <iostream>
// ������������Ľ��
template <class T>
struct ThreadNode {
    int ltag, rtag; // ������ǩ
    // tag == 0��ʾ���ָ������Ů��ָ��
    // tga == 1��ʾ���ָ��ý��ǰ��������
    ThreadNode<T>*leftChild, *rightChild; // ��������Ůָ��
    T data; // ����а���������
    ThreadNode(const T item)
        : data(item)
        , leftChild(NULL)
        , rightChild(NULL)
        , ltag(0)
        , rtag(0)
    {
    }
};

// ������������
template <class T>
class ThreadTree {
protected:
    ThreadNode<T>* root; // ���ĸ����
    void createInThread(ThreadNode<T>* current, ThreadNode<T>*& pre);
    // ������������
    ThreadNode<T>* parent(ThreadNode<T>* t); // Ѱ�ҽ��t�ĸ����
    void vist(ThreadNode<T>* p) // ����
    {
        std::cout << p->data << ' ';
    }

public:
    ThreadTree()
        : root(NULL)
    {
    } // ���캯�����������
    void createInThread(); // ������������������
    ThreadNode<T>* first(ThreadNode<T>* current); // Ѱ�������µĵ�һ�����
    ThreadNode<T>* last(ThreadNode<T>* current); // Ѱ�������µ����һ�����
    ThreadNode<T>* next(ThreadNode<T>* current); // Ѱ�������µ���һ�����
    ThreadNode<T>* prior(ThreadNode<T>* current); // Ѱ�������µ�ǰ�����
    void inOrder(); // �������
    void preOrder(); // ǰ�����
    void postOrder(); // �������
};

// Ѱ�������µĵ�һ�����
template <class T>
ThreadNode<T>* ThreadTree<T>::first(ThreadNode<T>* current)
{
    ThreadNode<T>* p = current;
    while (p->ltag == 0) {
        p = p->leftChild;
    }
    return p;
};

// Ѱ�������µ���һ�����
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

// Ѱ�������µ����һ�����
template <class T>
ThreadNode<T>* ThreadTree<T>::last(ThreadNode<T>* current)
{
    ThreadNode<T>* p = current;
    while (p->rtag == 0) {
        p = p->rightChild;
    }
    return p;
};

// Ѱ�������µ�ǰ�����
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

// �������
template <class T>
void ThreadTree<T>::inOrder()
{
    ThreadNode<T>* p;
    for (p = first(root); p != NULL; p = next(p)) {
        visit(p);
    }
};

// ������������Զ�������������������
template <class T>
void ThreadTree<T>::createInThread()
{
    ThreadNode<T>* pre = NULL;
    if (root != NULL) {
        createInThread(root, pre);
        pre->rightChild = NULL;
        pre->rtag = 1; // ������������һ�����
    }
};

// ͨ������������Զ�����������
// current��ʾ��ǰ��㣬pre��ʾǰ�����
template <class T>
void ThreadTree<T>::createInThread(ThreadNode<T>* current, ThreadNode<T>*& pre)
{
    if (current == NULL) {
        return;
    }
    createInThread(current->leftChild, pre); // ������������
    if (current->leftChild == NULL) // �����ӣ�������ǰ����ǰ������
    {
        current->leftChild = pre;
        current->ltag = 1;
    }
    if (pre != NULL && pre->rightChild == NULL) // ����ǰ�������ĺ������
    {
        pre->rightChild = current;
        pre->rtag = 1;
    }
    pre = current; // pre��Զָ��ǰ�����
    createInThread(current->rightChild, pre); // ������������
};

// ������������������ʵ��ǰ������㷨
template <class T>
void ThreadTree<T>::preOrder()
{
    ThreadNode<T>* p = root;
    while (p != NULL) {
        visit(p); // ���ʸ����
        if (p->ltag == 0) // ������Ů
        {
            p = p->leftChild;
        } else if (p->rtag == 0) // ������Ů
        {
            p = p->rightChild;
        } else {
            while (p != NULL && p->rtag == 1) // �غ���������
            {
                p = p->rightChild; // ֱ��������Ů�Ľ��
            }
            if (p != NULL) {
                p = p->rightChild; // ����Ů��Ϊ���
            }
        }
    }
};

// ������������������ʵ�ֺ�������㷨
template <class T>
void ThreadTree<T>::postOrder()
{
    ThreadNode<T>* t = root;
    while (t->ltag == 0 || t->rtag == 0) // ���ʺ�̵ĵ�һ�����
    {
        if (t->ltag == 0) {
            t = t->leftChild;
        } else if (t->rtag == 0) {
            t = t->rightChild;
        }
    }
    visit(t); // ���ʵ�һ�����
    ThreadNode<T>* p;
    while ((p = parent(t)) != NULL) {
        if (p->rightChild == t || p->rtag == 1) // t��p�ĺ�̻����
        // p->rtag == 1����p����������ֱ�ӱ���p
        {
            t = p;
        } else // Ϊ����Ů
        {
            t = p->rightChild; // t�ᵽp��������
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

// Ѱ�ҽ��t�ĸ����
template <class T>
ThreadNode<T>* ThreadTree<T>::parent(ThreadNode<T>* t)
{
    ThreadNode<T>* p;
    if (t == root) {
        return NULL; // ���ڵ��޸����
    }
    for (p = t; p->ltag == 0; p = p->leftChild)
        ;
    if (p->leftChild != NULL) // δ�ߵ���������ĵ�һ�����
    {
        for (p = p->leftChild; p != NULL && p->leftChild != t && p->rightChild != t; p = p->rightChild)
            ;
    }
    if (p == NULL || p->leftChild == NULL) // δ�ߵ�������������һ�����
    {
        for (p = t; p->rtag == 0; p = p->rightChild)
            ;
        for (p = p->rightChild; p != NULL && p->leftChild != t && p->rightChild != t; p = p->leftChild)
            ;
    }
    return p;
};
