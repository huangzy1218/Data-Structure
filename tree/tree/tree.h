#include <iostream>
#include <queue>
using namespace std;
// 树的结点类
template <class T>
struct TreeNode
{
    T data;                                // 结点数据
    TreeNode<T> *firstChild, *nextSibling; // 子女及兄弟指针
    TreeNode(T value, TreeNode<T> *fc = NULL, TreeNode<T> *ns = NULL)
        : data(value), firstChild(fc), nextSibling(ns) {} // 构造函数
};

// 树类
template <class T>
class Tree
{
private:
    TreeNode<T> *root, *current;        // 根指针及当前指针
    bool find(TreeNode<T> *p, T value); // 在以p为根的树中搜索value
    void removeSubTree(TreeNode<T> *p); // 删除以p为根的子树
    bool findParent(TreeNode<T> *t, TreeNode<T> *p);
    void visit(TreeNode<T> *t); // 遍历
    // 寻找当前结点的父结点

public:
    Tree() { root = current = NULL; }       // 构造函数，建立空树
    bool setRoot();                         // 寻找根，使其成为当前结点
    bool isEmpty() { return root == NULL; } // 判空树
    bool firstChild();                      // 寻找当前结点的第一个子女，使其成为当前结点
    bool nextSibling();                     // 寻找当前结点的下一个兄弟，使其成为当前结点
    bool setParent();                       // 寻找当前结点的双亲结点，使其成为当前结点
    bool find(T target);                    // 在树中搜索含有target的结点，使其成为当前结点
    void preOrder(TreeNode<T> *t);          // 先序遍历（深度优先）
    void postOrder(TreeNode<T> *t);         // 后序遍历（深度优先）
    void levelOrder(TreeNode<T> *t);        // 层次遍历（广度优先）
};

// 寻找根，使其成为当前结点
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

// 寻找当前结点的双亲结点，使其成为当前结点
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

// 在t树中寻找p的父结点，并使其成为当前结点
template <class T>
bool Tree<T>::findParent(TreeNode<T> *t, TreeNode<T> *p)
{
    TreeNode<T> *q = t->firstChild;
    bool succ;
    while (q != NULL && q != p)
    {
        if ((succ = findParent(q, p)) == true) // 找到
        {
            return succ;
        }
        q = q->nextSibling; // 转到下个兄弟结点
    }
    if (q != NULL && q == p)
    {
        current = t;
        return true;
    }
    else
    {
        current = NULL;
        return false; // 未找到父结点
    }
};

// 寻找当前结点的第一个子女，使其成为当前结点
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

// 寻找当前结点的下一个兄弟，使其成为当前结点
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

// 在树中搜索含有target的结点，使其成为当前结点，q为兄弟结点
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

// 在树中搜索含有target的结点，使其成为当前结点
template <class T>
bool Tree<T>::find(T target)
{
    return find(current, target);
};

// 先序遍历（深度优先）
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

// 后序遍历（深度优先）
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

// 先序遍历（广度优先）
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
