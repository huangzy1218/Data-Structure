/**
 * @file BST.h
 * @author Huang Z.Y.
 * @brief 二叉查找树(Binary Search Tree），它或者是一棵空树，或者是具有下列性质的二叉树：
 * 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值； 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值； 它的左、右子树也分别为二叉排序树。
 * @version 0.1
 * @date 2023-01-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;
template <class T>
struct BSTNode {
    T value; // 数据域
    BSTNode<T>*left, *right; // 左、右子女
    BSTNode()
        : left(nullptr)
        , right(nullptr)
    {
    }
    // 构造函数
    BSTNode(const T val, BSTNode<T>* l = nullptr, BSTNode<T>* r = nullptr)
        : value(val)
        , left(l)
        , right(r)
    {
    }
};

template <class T>
class BST {
public:
    BST()
        : root(nullptr)
    {
    } // 构造函数
    BST(T value)
        : root(nullptr)
        , refValue(value)
    {
    }
    ~BST() { destory(root); } // 析构函数
    void input(); // 输入
    void output(); // 输出
    bool insert(const T& x) // 插入
    {
        return insert(x, root);
    }
    bool remove(const T& x) // 删除
    {
        return remove(x, root);
    }
    bool search(const T& x) // 搜索
    {
        return (search(x, root) == nullptr ? true : false);
    }
    void inOrder() { inOrder(root); } // 中序遍历
    void preOrder() { preOrder(root); } // 先序遍历
    void postOrder() { postOrder(root); } // 后序遍历

protected:
    bool insert(const T& elem, BSTNode<T>*& ptr); // 插入
    bool remove(const T& x, BSTNode<T>*& ptr); // 删除
    BSTNode<T>* search(const T& x, BSTNode<T>*& ptr); // 查找
    void preOrder(BSTNode<T>* root); // 前序序遍历
    void inOrder(BSTNode<T>* root); // 中序遍历
    void postOrder(BSTNode<T>* root); // 后序遍历
    void destory(BSTNode<T>*& root); // 销毁
private:
    BSTNode<T>* root; // 根结点
    T refValue; // 输入结束标识
};

// 输入
template <class T>
void BST<T>::input()
{
    T x;
    cin >> x;
    while (x != refValue) {
        insert(x, root);
        cin >> x;
    }
};

// 输出
template <class T>
void BST<T>::output()
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

// 插入
template <class T>
bool BST<T>::insert(const T& elem, BSTNode<T>*& ptr)
{
    if (ptr == nullptr) {
        ptr = new BSTNode<T>(elem);
        if (ptr == nullptr) {
            cerr << "内存分配错误" << endl;
            exit(1);
        }
        return true;
    } else if (elem < ptr->value) {
        insert(elem, ptr->left);
    } else if (elem > ptr->value) {
        insert(elem, ptr->right);
    } else { // 已在树中，不插入
        return false;
    }
    return true;
};

// 删除
template <class T>
bool BST<T>::remove(const T& x, BSTNode<T>*& ptr)
{
    BSTNode<T>* temp;
    if (ptr != nullptr) {
        if (x < ptr->value) {
            remove(x, ptr->left);
        } else if (x > ptr->value) {
            remove(x, ptr->right);
        } else if (ptr->left != nullptr && ptr->right != nullptr) { // 要删除的结点同时有左右子树
            temp = ptr->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            ptr->value = temp->value;
            remove(ptr->value, ptr->right);
        } else {
            temp = ptr;
            if (ptr->left == nullptr) {
                ptr = ptr->right;
            } else {
                ptr = ptr->left;
            }
            delete temp;
            temp = nullptr;
            return true;
        }
    } else {
        return false;
    }
    return true;
};

// 搜索
template <class T>
BSTNode<T>* BST<T>::search(const T& x, BSTNode<T>*& ptr)
{
    if (ptr == nullptr)
        return nullptr;
    else if (x < ptr->value)
        return search(x, ptr->left);
    else if (x > ptr->value)
        return search(x, ptr->right);
    else
        return ptr;
};

// 前序遍历
template <class T>
void BST<T>::preOrder(BSTNode<T>* root)
{
    if (root != nullptr) {
        cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
};

// 中序遍历
template <class T>
void BST<T>::inOrder(BSTNode<T>* root)
{
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->value << " ";
        inOrder(root->right);
    }
};

// 后序遍历
template <class T>
void BST<T>::postOrder(BSTNode<T>* root)
{
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->value << " ";
    }
};

// 销毁二叉树
template <class T>
void BST<T>::destory(BSTNode<T>*& root)
{
    if (root == nullptr)
        return;
    if (root->left != nullptr)
        destory(root->left);
    if (root->right != nullptr)
        destory(root->right);
    delete root;
    root = nullptr;
};

#endif