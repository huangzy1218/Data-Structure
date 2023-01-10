/**
 * @file BST.h
 * @author Huang Z.Y.
 * @brief ���������(Binary Search Tree������������һ�ÿ����������Ǿ����������ʵĶ�������
 * ���������������գ��������������н���ֵ��С�����ĸ�����ֵ�� ���������������գ��������������н���ֵ���������ĸ�����ֵ�� ������������Ҳ�ֱ�Ϊ������������
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
    T value; // ������
    BSTNode<T>*left, *right; // ������Ů
    BSTNode()
        : left(nullptr)
        , right(nullptr)
    {
    }
    // ���캯��
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
    } // ���캯��
    BST(T value)
        : root(nullptr)
        , refValue(value)
    {
    }
    ~BST() { destory(root); } // ��������
    void input(); // ����
    void output(); // ���
    bool insert(const T& x) // ����
    {
        return insert(x, root);
    }
    bool remove(const T& x) // ɾ��
    {
        return remove(x, root);
    }
    bool search(const T& x) // ����
    {
        return (search(x, root) == nullptr ? true : false);
    }
    void inOrder() { inOrder(root); } // �������
    void preOrder() { preOrder(root); } // �������
    void postOrder() { postOrder(root); } // �������

protected:
    bool insert(const T& elem, BSTNode<T>*& ptr); // ����
    bool remove(const T& x, BSTNode<T>*& ptr); // ɾ��
    BSTNode<T>* search(const T& x, BSTNode<T>*& ptr); // ����
    void preOrder(BSTNode<T>* root); // ǰ�������
    void inOrder(BSTNode<T>* root); // �������
    void postOrder(BSTNode<T>* root); // �������
    void destory(BSTNode<T>*& root); // ����
private:
    BSTNode<T>* root; // �����
    T refValue; // ���������ʶ
};

// ����
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

// ���
template <class T>
void BST<T>::output()
{
    cout << "���������";
    preOrder();
    cout << endl;
    cout << "���������";
    inOrder();
    cout << endl;
    cout << "���������";
    postOrder();
    cout << endl;
};

// ����
template <class T>
bool BST<T>::insert(const T& elem, BSTNode<T>*& ptr)
{
    if (ptr == nullptr) {
        ptr = new BSTNode<T>(elem);
        if (ptr == nullptr) {
            cerr << "�ڴ�������" << endl;
            exit(1);
        }
        return true;
    } else if (elem < ptr->value) {
        insert(elem, ptr->left);
    } else if (elem > ptr->value) {
        insert(elem, ptr->right);
    } else { // �������У�������
        return false;
    }
    return true;
};

// ɾ��
template <class T>
bool BST<T>::remove(const T& x, BSTNode<T>*& ptr)
{
    BSTNode<T>* temp;
    if (ptr != nullptr) {
        if (x < ptr->value) {
            remove(x, ptr->left);
        } else if (x > ptr->value) {
            remove(x, ptr->right);
        } else if (ptr->left != nullptr && ptr->right != nullptr) { // Ҫɾ���Ľ��ͬʱ����������
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

// ����
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

// ǰ�����
template <class T>
void BST<T>::preOrder(BSTNode<T>* root)
{
    if (root != nullptr) {
        cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
};

// �������
template <class T>
void BST<T>::inOrder(BSTNode<T>* root)
{
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->value << " ";
        inOrder(root->right);
    }
};

// �������
template <class T>
void BST<T>::postOrder(BSTNode<T>* root)
{
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->value << " ";
    }
};

// ���ٶ�����
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