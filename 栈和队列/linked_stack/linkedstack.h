/**
 * @file linkedstack.h
 * @author Huang Z.Y.
 * @brief 链式栈(linked stack)是一种数据存储结构，可以通过单链表的方式来实现，使用链式栈的优点在于它能够克服用数组实现的顺序栈空间利用率不高的特点，
 * 但需要为每个栈元素分配额外的指针空间用来存放指针域。
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
struct LinkNode { // 栈节点
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
    } // 构造函数
    ~LinkedStack() { makeEmpty(); } // 析构函数
    void push(const T& x); // 入栈
    bool pop(T& x); // 出栈
    bool getTop(T& x); // 获取栈顶元素
    bool isEmpty() const { return top == nullptr; } // 判空
    bool isFull() const { return false; } // 判满
    int size() const; // 获取栈大小
    void makeEmpty(); // 置空
    template <class U>
    friend ostream& operator<<(ostream& os, LinkedStack<U>& S);
    // 输出运算符重载
private:
    LinkNode<T>* top;
};

// 置空
template <class T>
void LinkedStack<T>::makeEmpty()
{
    LinkNode<T>* p; // 遍历指针
    while (top != nullptr) {
        p = top;
        top = p->link;
        delete p; // 删除
    }
};

// 入栈
template <class T>
void LinkedStack<T>::push(const T& x)
{
    top = new LinkNode<T>(x, top); // 入栈
    assert(top != nullptr);
};

// 出栈
template <class T>
bool LinkedStack<T>::pop(T& x)
{
    if (isEmpty()) // 判空
    {
        return false;
    }
    LinkNode<T>* p = top; // 获取栈顶
    top = top->link;
    x = p->data;
    delete p; // 鍒犻櫎鍑烘爤鍏冪礌
    return true;
};

// 获取栈顶元素
template <class T>
bool LinkedStack<T>::getTop(T& x)
{
    if (isEmpty()) // 判空
    {
        return false;
    }
    x = top->data;
    return true;
};

// 获取栈大小
template <class T>
int LinkedStack<T>::size() const
{
    LinkNode<T>* p = top; // 鐢ㄤ簬閬嶅巻
    int count = 0;
    while (p != nullptr) {
        p = p->link;
        ++count;
    }
    return count;
};

// 输出运算符重载
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