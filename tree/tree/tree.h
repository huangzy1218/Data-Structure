#include <iostream>
#include <queue>
using namespace std;
// ���Ľ����
template <class T>
struct TreeNode
{
    T data;                                // �������
    TreeNode<T> *firstChild, *nextSibling; // ��Ů���ֵ�ָ��
    TreeNode(T value, TreeNode<T> *fc = NULL, TreeNode<T> *ns = NULL)
        : data(value), firstChild(fc), nextSibling(ns) {} // ���캯��
};

// ����
template <class T>
class Tree
{
private:
    TreeNode<T> *root, *current;        // ��ָ�뼰��ǰָ��
    bool find(TreeNode<T> *p, T value); // ����pΪ������������value
    void removeSubTree(TreeNode<T> *p); // ɾ����pΪ��������
    bool findParent(TreeNode<T> *t, TreeNode<T> *p);
    void visit(TreeNode<T> *t); // ����
    // Ѱ�ҵ�ǰ���ĸ����

public:
    Tree() { root = current = NULL; }       // ���캯������������
    bool setRoot();                         // Ѱ�Ҹ���ʹ���Ϊ��ǰ���
    bool isEmpty() { return root == NULL; } // �п���
    bool firstChild();                      // Ѱ�ҵ�ǰ���ĵ�һ����Ů��ʹ���Ϊ��ǰ���
    bool nextSibling();                     // Ѱ�ҵ�ǰ������һ���ֵܣ�ʹ���Ϊ��ǰ���
    bool setParent();                       // Ѱ�ҵ�ǰ����˫�׽�㣬ʹ���Ϊ��ǰ���
    bool find(T target);                    // ��������������target�Ľ�㣬ʹ���Ϊ��ǰ���
    void preOrder(TreeNode<T> *t);          // ���������������ȣ�
    void postOrder(TreeNode<T> *t);         // ���������������ȣ�
    void levelOrder(TreeNode<T> *t);        // ��α�����������ȣ�
};

// Ѱ�Ҹ���ʹ���Ϊ��ǰ���
template <class T>
bool Tree<T>::setRoot()
{
    if (root == NULL)
    {
        current = NULL;
        return false;
    }
    else
    {
        current = root;
        return true;
    }
};

// Ѱ�ҵ�ǰ����˫�׽�㣬ʹ���Ϊ��ǰ���
template <class T>
bool Tree<T>::setParent()
{
    TreeNode<T> *p = current;
    if (current == NULL || current == root)
    {
        current = NULL;
        return false;
    }
    return findParent(root, p);
};

// ��t����Ѱ��p�ĸ���㣬��ʹ���Ϊ��ǰ���
template <class T>
bool Tree<T>::findParent(TreeNode<T> *t, TreeNode<T> *p)
{
    TreeNode<T> *q = t->firstChild;
    bool succ;
    while (q != NULL && q != p)
    {
        if ((succ = findParent(q, p)) == true) // �ҵ�
        {
            return succ;
        }
        q = q->nextSibling; // ת���¸��ֵܽ��
    }
    if (q != NULL && q == p)
    {
        current = t;
        return true;
    }
    else
    {
        current = NULL;
        return false; // δ�ҵ������
    }
};

// Ѱ�ҵ�ǰ���ĵ�һ����Ů��ʹ���Ϊ��ǰ���
template <class T>
bool Tree<T>::firstChild()
{
    if (current != NULL && current->firstChild != NULL)
    {
        current = current->firstChild;
        return true;
    }
    return false;
};

// Ѱ�ҵ�ǰ������һ���ֵܣ�ʹ���Ϊ��ǰ���
template <class T>
bool Tree<T>::nextSibling()
{
    if (current != NULL && current->nextSibling != NULL)
    {
        current = current->nextSibling;
        return true;
    }
    current = NULL;
    return false;
};

// ��������������target�Ľ�㣬ʹ���Ϊ��ǰ��㣬qΪ�ֵܽ��
template <class T>
bool Tree<T>::find(TreeNode<T> *p, T target)
{
    bool succ = false;
    if (p->data == target)
    {
        succ = true;
        current = p;
    }
    else
    {
        TreeNode<T> *q = p->firstChild;
        while (q != NULL && !(succ = find(q, target)))
        {
            q = q->nextSibling;
        }
    }
    return succ;
};

// ��������������target�Ľ�㣬ʹ���Ϊ��ǰ���
template <class T>
bool Tree<T>::find(T target)
{
    return find(current, target);
};

// ���������������ȣ�
template <class T>
void Tree<T>::preOrder(TreeNode<T> *t)
{
    if (t == NULL)
    {
        return;
    }
    visit(t);
    preOrder(t->firstChild, visit);
    preOrder(t->nextSibling);
};

// ���������������ȣ�
template <class T>
void Tree<T>::postOrder(TreeNode<T> *t)
{
    if (t == NULL)
    {
        return;
    }
    postOrder(t->firstChild);
    postOrder(t->nextSibling);
    visit(t);
};

// ���������������ȣ�
template <class T>
void Tree<T>::levelOrder(TreeNode<T> *p)
{
    queue<TreeNode<T> *> q;
    if (p != NULL)
    {
        q.push(p);
        while (!q.empty())
        {
            p = q.front();
            cout << p->data;
            for (p = p->firstChild; p != NULL; p = p->nextSibling)
            {
                q.push(p);
            }
        }
    }
};
