/**
 * @file AVLTree.h
 * @author Huang Z.Y.
 * @brief AVL��(AVL tree)�����ȷ�������ƽ��������������AVL�����κνڵ�����������ĸ߶������Ϊ 1��
 * ������Ҳ����Ϊ�߶�ƽ���������Ӻ�ɾ��������Ҫͨ��һ�λ�������ת������ƽ���������
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
    T value; // ������
    int height; // �߶�
    AVLTreeNode<T>* left; // ������
    AVLTreeNode<T>* right; // ������
    AVLTreeNode(T val, AVLTreeNode* l = nullptr, AVLTreeNode* r = nullptr) // ���캯��
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
    AVLTree() // ���캯��
        : root(nullptr)
    {
    }
    ~AVLTree() { destroy(root); } // ��������
    void inOrder() { inOrder(root); } // �������
    void preOrder() { preOrder(root); } // �������
    void postOrder() { postOrder(root); } // �������
    void input(); // ����
    void output(); // ���
    int height() { return height(root); } // ����
    bool search(const T& value) // ����
    {
        return search(root, value) == nullptr ? false : true;
    }
    bool iterativeSearch(const T& value) // �ǵݹ�����
    {
        return iterativeSearch(root, value) == nullptr ? false : true;
    }
    T minimum(); // ������С���
    T maximum(); // ���������
    void insert(const T& value) // ����
    {
        insert(root, value);
    }
    void remove(const T& value); // ɾ��
    void destroy() { destroy(root); } // ����
protected:
    void preOrder(AVLTreeNode<T>* node); // �������
    void inOrder(AVLTreeNode<T>* node); // �������
    void postOrder(AVLTreeNode<T>* node); // �������
    int height(AVLTreeNode<T>* node) // ���� root Ϊ��������
    {
        return node != nullptr ? node->height : 0;
    }
    void destroy(AVLTreeNode<T>*& tree); // ���� tree
    AVLTreeNode<T>* search(AVLTreeNode<T>* node, const T& value); // ����
    AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* node, const T& value); // �ǵݹ����
    AVLTreeNode<T>* minimum(AVLTreeNode<T>* node); // ��ȡ��С���
    AVLTreeNode<T>* maximum(AVLTreeNode<T>* node); // ��ȡ�����
    AVLTreeNode<T>* insert(AVLTreeNode<T>*& node, const T& value); // ����
    AVLTreeNode<T>* remove(AVLTreeNode<T>*& node, AVLTreeNode<T>* p); // ɾ��

private:
    AVLTreeNode<T>* root; // �����
    AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>*& k2); // �����������ʧȥƽ��(����ת)
    AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>*& k2); // ���������ұ�ʧȥƽ��(�ҵ���ת)
    AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>*& k2); // ���������ұ�ʧȥƽ��(��˫��ת)
    AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>*& k2); // �����������ʧȥƽ��(��˫��ת)
};

// ������С���
template <class T>
T AVLTree<T>::minimum()
{
    AVLTreeNode<T>* p = minimum(root);
    if (p != nullptr)
        return p->value;
    return (T) nullptr;
};

// ���������
template <class T>
T AVLTree<T>::maximum()
{
    AVLTreeNode<T>* p = maximum(root);
    if (p != nullptr)
        return p->value;
    return (T) nullptr;
};

// ɾ��
template <class T>
void AVLTree<T>::remove(const T& value)
{
    AVLTreeNode<T>* p = search(root, value);
    if (p != nullptr)
        root = remove(root, p);
};

// �������
template <class T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* node)
{
    if (node != nullptr) {
        cout << node->value << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
};

// �������
template <class T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* node)
{
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->value << " ";
        inOrder(node->right);
    }
};

// �������
template <class T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* node)
{
    if (node != nullptr) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->value << " ";
    }
};

// ���
template <class T>
void AVLTree<T>::output()
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

// ���� tree
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

// ����
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

// �ǵݹ�����
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

// ��ȡ��С���
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

// ��ȡ�����
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

// ����
// ����������������� + ��·�����ݼ��
template <class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>*& node, const T& value)
{
    if (node == nullptr) {
        node = new AVLTreeNode<T>(value);
    } else if (value < node->value) { // value ����������
        node->left = insert(node->left, value);
        // AVL ��ʧ�⣨ƽ������ > 2�������е���
        if (height(node->left) - height(node->right) == 2) {
            if (value < node->left->value) // ����������������(1 �Ž��)
                node = leftLeftRotation(node);
            else // ����������������(2 �Ž��)
                node = leftRightRotation(node);
        }
    } else if (value > node->value) { // // value ����������
        node->right = insert(node->right, value);
        // AVL ��ʧ�⣨ƽ������ > 2�������е���
        if (height(node->right) - height(node->left) == 2) {
            if (value > node->right->value) // ����������������(4 �Ž��)
                node = rightRightRotation(node);
            else // ����������������(3 �Ž��)
                node = rightLeftRotation(node);
        }
    } else {
        cerr << "���ʧ��" << endl;
        return nullptr;
    }
    node->height = max(height(node->left), height(node->right)) + 1; // ��������
    return node;
};

// ɾ��
template <class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>*& node, AVLTreeNode<T>* p)
{
    if (node == nullptr || p == nullptr)
        return nullptr;
    if (p->value < node->value) { // ��������ɾ��
        node->left = remove(node->left, p);
        // AVL ��ʧ�⣨ƽ������ > 2�������е���
        if (height(node->right) - height(node->left) == 2) {
            AVLTreeNode<T>* r = node->right;
            if (height(r->left) > height(r->left)) // ��� 3 �����ʧ��
                node = rightLeftRotation(node);
            else // ��� 4 �����ʧ��
                node = rightRightRotation(node);
        }
    } else if (p->value > node->value) {
        node->right = remove(node->right, p);
        if (height(node->left) - height(node->right) == 2) {
            AVLTreeNode<T>* l = node->left;
            if (height(l->right) > height(l->left)) // ��� 2 �����ʧ��
                node = leftRightRotation(node);
            else // ��� 1 �����ʧ��
                node = leftLeftRotation(node);
        }
    } else { // ��ǰ node ����Ҫɾ���Ľ��
        if ((node->left != nullptr) && (node->right != nullptr)) {
            if (height(node->left) > height(node->right)) {
                AVLTreeNode<T>* max = maximum(node->left); // �������������
                node->value = max->value;
                node->left = remove(node->left, max);
            } else {
                AVLTreeNode<T>* min = minimum(node->right); // ����������С���
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

// �����������ʧȥƽ��(����)��λ�� 1 ������
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

// ���������ұ�ʧȥƽ��(����)��λ�� 4 ������
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

// ���������ұ�ʧȥƽ��(��˫��ת)��λ�� 2 ������
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

// �����������ʧȥƽ��(��˫��ת)��λ�� 3 ������
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