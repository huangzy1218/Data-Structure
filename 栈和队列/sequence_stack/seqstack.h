/**
 * @file seqstack.h
 * @author Huang Z.Y.
 * @brief 顺序栈(sequence stack)是指利用顺序存储结构实现的栈。采用地址连续的存储空间依次存储栈中数据元素，
 * 由于入栈和出栈运算都是在栈顶进行，而栈底位置是固定不变的，故需要使用 top 记录栈顶位置。
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SEQSTACK_H
#define SEQSTACK_H
#include "Stack.h"
#include <cassert>
#include <iostream>
using namespace std;
const int stackIncreasement = 20; // 默认栈满时新增内存空间
template <class T>
class SeqStack;
template <class U>
ostream& operator<<(ostream& os, SeqStack<U>& S);
template <class T>
class SeqStack : public Stack<T> {
public:
    SeqStack(int sz = 50); // 构造函数
    ~SeqStack() { delete[] elements; } // 析构函数
    void push(const T& x); // 入栈
    bool pop(T& x); // 出栈
    bool getTop(T& x); // 获取栈顶元素
    bool isEmpty() const { return top == -1; } // 判空
    bool isFull() const { return top == maxSize - 1; }
    // 判满
    int size() const { return top + 1; } // 获取大小
    void makeEmpty() { top = -1; } // 置空
    template <class U>
    friend ostream& operator<<(ostream& os, SeqStack<U>& S); // 输出运算符重载
private:
    T* elements; // 元素
    int top; // 栈顶元素下标
    int maxSize; // 最大个数
    void overflowProcess(); // 栈溢出时的处理
};

// 构造函数
template <class T>
SeqStack<T>::SeqStack(int sz)
    : top(-1)
    , maxSize(sz)
{
    elements = new T[maxSize];
    assert(elements != NULL);
}

// 栈溢出处理
template <class T>
void SeqStack<T>::overflowProcess()
{
    T* newArray = new T[maxSize + stackIncreasement];
    if (newArray == NULL) {
        cerr << "内存分配出错" << endl;
    } else {
        for (int i = 0; i <= top; i++) {
            newArray[i] = elements[i];
        }
        maxSize += stackIncreasement;
        delete[] elements;
        elements = newArray;
    }
}

// 入栈
template <class T>
void SeqStack<T>::push(const T& x)
{
    if (isFull()) // 栈满
    {
        overflowProcess();
    }
    elements[++top] = x;
}

// 出栈
template <class T>
bool SeqStack<T>::pop(T& x)
{
    if (isEmpty()) {
        return false;
    } else {
        x = elements[top--];
        return true;
    }
};

// 获取栈顶元素
template <class T>
bool SeqStack<T>::getTop(T& x)
{
    if (isEmpty()) {
        return false;
    } else {
        x = elements[top];
        return true;
    }
};

// 输出运算符重载
template <class T>
ostream& operator<<(ostream& os, SeqStack<T>& S)
{
    os << "top = " << S.top << endl;
    for (int i = 0; i <= S.top; i++) {
        os << S.elements[i] << " ";
    }
    os << endl;
    return os;
};

#endif
