/**
 * @file linkedstack.h
 * @author Huang Z.Y.
 * @brief ��ʽջ(linked stack)��һ�����ݴ洢�ṹ������ͨ��������ķ�ʽ��ʵ�֣�ʹ����ʽջ���ŵ��������ܹ��˷�������ʵ�ֵ�˳��ջ�ռ������ʲ��ߵ��ص㣬
 * ����ҪΪÿ��ջԪ�ط�������ָ��ռ��������ָ����
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H
#include "Stack.h"
#include <cassert>
#include <iostream>
using namespace std;
template <class T>
struct LinkNode { // ջ�ڵ�
    T data;
    LinkNode<T>* link;
    LinkNode(LinkNode<T>* ptr = nullptr) { link = ptr; }
    LinkNode(const T& item, LinkNode* ptr = nullptr)
    {
        data = item;
        link = ptr;
    }
};

template <class T>
class LinkedStack;
template <class U>
ostream& operator<<(ostream& os, LinkedStack<U>& S);
template <class T>
class LinkedStack : public Stack<T> {
public:
    LinkedStack()
        : top(nullptr)
    {
    } // ���캯��
    ~LinkedStack() { makeEmpty(); } // ��������
    void push(const T& x); // ��ջ
    bool pop(T& x); // ��ջ
    bool getTop(T& x); // ��ȡջ��Ԫ��
    bool isEmpty() const { return top == nullptr; } // �п�
    bool isFull() const { return false; } // ����
    int size() const; // ��ȡջ��С
    void makeEmpty(); // �ÿ�
    template <class U>
    friend ostream& operator<<(ostream& os, LinkedStack<U>& S);
    // ������������
private:
    LinkNode<T>* top;
};

// �ÿ�
template <class T>
void LinkedStack<T>::makeEmpty()
{
    LinkNode<T>* p; // ����ָ��
    while (top != nullptr) {
        p = top;
        top = p->link;
        delete p; // ɾ��
    }
};

// ��ջ
template <class T>
void LinkedStack<T>::push(const T& x)
{
    top = new LinkNode<T>(x, top); // ��ջ
    assert(top != nullptr);
};

// ��ջ
template <class T>
bool LinkedStack<T>::pop(T& x)
{
    if (isEmpty()) // �п�
    {
        return false;
    }
    LinkNode<T>* p = top; // ��ȡջ��
    top = top->link;
    x = p->data;
    delete p; // 删除出栈元素
    return true;
};

// ��ȡջ��Ԫ��
template <class T>
bool LinkedStack<T>::getTop(T& x)
{
    if (isEmpty()) // �п�
    {
        return false;
    }
    x = top->data;
    return true;
};

// ��ȡջ��С
template <class T>
int LinkedStack<T>::size() const
{
    LinkNode<T>* p = top; // 用于遍历
    int count = 0;
    while (p != nullptr) {
        p = p->link;
        ++count;
    }
    return count;
};

// ������������
template <class T>
ostream& operator<<(ostream& os, LinkedStack<T>& s)
{
    LinkNode<T>* p = s.top;
    while (p != nullptr) {
        os << p->data << " ";
        p = p->link;
    }
    os << endl;
    return os;
};

#endif