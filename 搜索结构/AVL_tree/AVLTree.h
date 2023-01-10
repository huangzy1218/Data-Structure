/**
 * @file AVLTree.h
 * @author Huang Z.Y.
 * @brief AVL树(AVL tree)是最先发明的自平衡二叉查找树。在AVL树中任何节点的两个子树的高度最大差别为 1，
 * 所以它也被称为高度平衡树。增加和删除可能需要通过一次或多次树旋转来重新平衡这个树。
 * @version 0.1
 * @date 2023-01-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
using namespace std;

template <class T>
struct AVLTreeNode {
    T value; // 数据域
    int height; // 高度
    AVLTreeNode<T>* left; // 左子树
    AVLTreeNode<T>* right; // 右子树
    AVLTreeNode(T val, AVLTreeNode* l = nullptr, AVLTreeNode* r = nullptr) // 构造函数
        : value(val)
        , height(0)
        , left(l)
        , right(r)
    {
    }
};

template <class T>
class AVLTree {
public:
    AVLTree() // 构造函数
        : root(nullptr)
    {
    }
    ~AVLTree() { destroy(root); } // 析构函数
    void inOrder() { inOrder(root); } // 中序遍历
    void preOrder() { preOrder(root); } // 先序遍历
    void postOrder() { postOrder(root); } // 后序遍历
    void input(); // 输入
    void output(); // 输出
    int height() { return height(root); } // 树高
    bool search(const T& value) // 搜索
    {
        return search(root, value) == nullptr ? false : true;
    }
    bool iterativeSearch(const T& value) // 非递归搜索
    {
        return iterativeSearch(root, value) == nullptr ? false : true;
    }
    T minimum(); // 查找最小结点
    T maximum(); // 查找最大结点
    void insert(const T& value) // 插入
    {
        insert(root, value);
    }
    void remove(const T& value); // 删除
    void destroy() { destroy(root); } // 销毁
protected:
    void preOrder(AVLTreeNode<T>* node); // 先序遍历
    void inOrder(AVLTreeNode<T>* node); // 中序遍历
    void postOrder(AVLTreeNode<T>* node); // 后序遍历
    int height(AVLTreeNode<T>* node) // 求以 root 为根的树高
    {
        return node != nullptr ? node->height : 0;
    }
    void destroy(AVLTreeNode<T>*& tree); // 销毁 tree
    AVLTreeNode<T>* search(AVLTreeNode<T>* node, const T& value); // 查找
    AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* node, const T& value); // 非递归查找
    AVLTreeNode<T>* minimum(AVLTreeNode<T>* node); // 获取最小结点
    AVLTreeNode<T>* maximum(AVLTreeNode<T>* node); // 获取最大结点
    AVLTreeNode<T>* insert(AVLTreeNode<T>*& node, const T& value); // 插入
    AVLTreeNode<T>* remove(AVLTreeNode<T>*& node, AVLTreeNode<T>* p); // 删除

private:
    AVLTreeNode<T>* root; // 根结点
    AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>*& k2); // 左子树的左边失去平衡(左单旋转)
    AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>*& k2); // 右子树的右边失去平衡(右单旋转)
    AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>*& k2); // 左子树的右边失去平衡(左双旋转)
    AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>*& k2); // 右子树的左边失去平衡(右双旋转)
};

// 查找最小结点
template <class T>
T AVLTree<T>::minimum()
{
    AVLTreeNode<T>* p = minimum(root);
    if (p != nullptr)
        return p->value;
    return (T) nullptr;
};

// 查找最大结点
template <class T>
T AVLTree<T>::maximum()
{
    AVLTreeNode<T>* p = maximum(root);
    if (p != nullptr)
        return p->value;
    return (T) nullptr;
};

// 删除
template <class T>
void AVLTree<T>::remove(const T& value)
{
    AVLTreeNode<T>* p = search(root, value);
    if (p != nullptr)
        root = remove(root, p);
};

// 先序遍历
template <class T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* node)
{
    if (node != nullptr) {
        cout << node->value << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
};

// 中序遍历
template <class T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* node)
{
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->value << " ";
        inOrder(node->right);
    }
};

// 后序遍历
template <class T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* node)
{
    if (node != nullptr) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->value << " ";
    }
};

// 输出
template <class T>
void AVLTree<T>::output()
{
    cout << "先序输出：";
    preOrder();
    cout << endl;
    cout << "中序输出：";
    inOrder();
    cout << endl;
    cout << "后序输出：";
    postOrder();
    cout << endl;
};

// 销毁 tree
template <class T>
void AVLTree<T>::destroy(AVLTreeNode<T>*& tree)
{
    if (tree == nullptr)
        return;
    if (tree->left != nullptr)
        destroy(tree->left);
    if (tree->right != nullptr)
        destroy(tree->right);
    delete tree;
};

// 搜索
template <class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* node, const T& value)
{
    if (node == nullptr || node->value == value)
        return node;
    if (value < node->value)
        return search(node->left, value);
    else
        return search(node->right, value);
};

// 非递归搜索
template <class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(AVLTreeNode<T>* node, const T& value)
{
    while ((node != nullptr) && (node->value != value)) {
        if (value < node->value)
            node = node->left;
        else
            node = node->right;
    }
    return node;
};

// 获取最小结点
template <class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* node)
{
    if (node == nullptr)
        return nullptr;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
};

// 获取最大结点
template <class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* node)
{
    if (node == nullptr)
        return nullptr;
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
};

// 插入
// 常规二叉搜索树插入 + 沿路径回溯检查
template <class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>*& node, const T& value)
{
    if (node == nullptr) {
        node = new AVLTreeNode<T>(value);
    } else if (value < node->value) { // value 插入左子树
        node->left = insert(node->left, value);
        // AVL 树失衡（平衡因子 > 2），进行调节
        if (height(node->left) - height(node->right) == 2) {
            if (value < node->left->value) // 在左子树的左子树(1 号结点)
                node = leftLeftRotation(node);
            else // 在左子树的右子树(2 号结点)
                node = leftRightRotation(node);
        }
    } else if (value > node->value) { // // value 插入右子树
        node->right = insert(node->right, value);
        // AVL 树失衡（平衡因子 > 2），进行调节
        if (height(node->right) - height(node->left) == 2) {
            if (value > node->right->value) // 在右子树的右子树(4 号结点)
                node = rightRightRotation(node);
            else // 在右子树的左子树(3 号结点)
                node = rightLeftRotation(node);
        }
    } else {
        cerr << "添加失败" << endl;
        return nullptr;
    }
    node->height = max(height(node->left), height(node->right)) + 1; // 更新树高
    return node;
};

// 删除
template <class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>*& node, AVLTreeNode<T>* p)
{
    if (node == nullptr || p == nullptr)
        return nullptr;
    if (p->value < node->value) { // 在左子树删除
        node->left = remove(node->left, p);
        // AVL 树失衡（平衡因子 > 2），进行调节
        if (height(node->right) - height(node->left) == 2) {
            AVLTreeNode<T>* r = node->right;
            if (height(r->left) > height(r->left)) // 结点 3 引起的失衡
                node = rightLeftRotation(node);
            else // 结点 4 引起的失衡
                node = rightRightRotation(node);
        }
    } else if (p->value > node->value) {
        node->right = remove(node->right, p);
        if (height(node->left) - height(node->right) == 2) {
            AVLTreeNode<T>* l = node->left;
            if (height(l->right) > height(l->left)) // 结点 2 引起的失衡
                node = leftRightRotation(node);
            else // 结点 1 引起的失衡
                node = leftLeftRotation(node);
        }
    } else { // 当前 node 就是要删除的结点
        if ((node->left != nullptr) && (node->right != nullptr)) {
            if (height(node->left) > height(node->right)) {
                AVLTreeNode<T>* max = maximum(node->left); // 左子树的最大结点
                node->value = max->value;
                node->left = remove(node->left, max);
            } else {
                AVLTreeNode<T>* min = minimum(node->right); // 右子树的最小结点
                node->value = min->value;
                node->right = remove(node->right, min);
            }
        } else {
            AVLTreeNode<T>* temp = node;
            node = node->left != nullptr ? node->left : node->right;
            delete temp;
        }
    }
    return node;
};

// 左子树的左边失去平衡(右旋)：位于 1 号子树
/*
 *       k2              k1
 *      /  \            /  \
 *     k1   z   ===>   x    k2
 *    /  \                 /  \
 *   x    y               y    z
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>*& k2)
{
    AVLTreeNode<T>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    return k1;
};

// 右子树的右边失去平衡(左旋)：位于 4 号子树
/*
 *       k1              k2
 *      /  \            /  \
 *     x   k2   ===>   k1   z
 *        /  \        /  \
 *       y    z      x    y
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>*& k1)
{
    AVLTreeNode<T>* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    return k2;
};

// 左子树的右边失去平衡(左双旋转)：位于 2 号子树
/*
 *       k3               k3               k2
 *      /  \     RR      /  \     LL      /  \
 *     k1   D   ===>   k2    D   ===>   k1    k3
 *    /  \            /  \             /  \  /  \
 *   A    K2         k1   C           A    B C   D
 *       /  \       /  \
 *      B    C     A    B
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>*& k3)
{
    k3->left = rightRightRotation(k3->left);
    return leftLeftRotation(k3);
};

// 右子树的左边失去平衡(右双旋转)：位于 3 号子树
/*
 *     k1               k1                K2
 *    /  \      LL     /  \      RR      /  \
 *   A    k3   ===>   A    k2   ===>   k1    K3
 *       /  \             /  \        /  \  /  \
 *      k2   D           B    k3     A    B C   D
 *     /  \                  /   \
 *    B    D                C     D
 */

template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>*& k1)
{
    k1->right = leftLeftRotation(k1->right);
    return rightRightRotation(k1);
};

#endif