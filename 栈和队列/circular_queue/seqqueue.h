/**
 * @file seqqueue.h
 * @author Huang Z.Y.
 * @brief 循环队列(sequence queue)将顺序队列首尾相连，把存储队列元素的表从逻辑上看成一个环，成为循环队列。
 * 其克服了循环队列假溢出的问题，有效提高了空间利用率。
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SEQQUEUE_H
#define SEQQUEUE_H
#include "Queue.h"
#include <cassert>
#include <iostream>
using namespace std;
template <class T>
class SeqQueue;
template <class T>
ostream& operator<<(ostream& os, SeqQueue<T>& Q);
template <class T>
class SeqQueue : public Queue<T> {
public:
    SeqQueue(int size = SIZE); // 构造函数
    ~SeqQueue() { delete[] elements; } // 析构函数
    bool enQueue(const T& x); // 新元素x进对列
    bool deQueue(T& x); // 新元素出队列
    bool getFront(T& x) const; // 读取头节点元素值
    bool isEmpty() const { return (front == rear) ? true : false; }; // 判空
    bool isFull() const // 判满
    {
        return ((rear + 1) % maxSize == front) ? true : false;
    }
    int size() const // 获取大小
    {
        return (rear - front + maxSize) % maxSize;
    }
    void makeEmpty() { front = rear = 0; } // 置空
    template <class U>
    friend ostream& operator<<(ostream& os, SeqQueue<U>& Q);

protected:
    int rear, front; // 头尾指针
    T* elements;
    int maxSize;
};

// 构造函数
template <class T>
SeqQueue<T>::SeqQueue(int size)
    : front(0)
    , rear(0)
    , maxSize(size)
{
    elements = new T[maxSize];
    assert(elements != NULL);
};

// 入队
template <class T>
bool SeqQueue<T>::enQueue(const T& x)
{
    if (isFull()) { // 队满
        return false;
    }
    elements[rear] = x;
    rear = (rear + 1) % maxSize;
    return true;
};

// 获取队头元素
template <class T>
bool SeqQueue<T>::getFront(T& x) const
{
    if (isEmpty()) {
        return false;
    }
    x = elements[front];
    return true;
};

// 出队列
template <class T>
bool SeqQueue<T>::deQueue(T& x)
{
    if (isEmpty()) {
        return false;
    }
    x = elements[front];
    front = (front + 1) % maxSize;
    return true;
};

// 输出运算符重载
template <class T>
ostream& operator<<(ostream& os, SeqQueue<T>& Q)
{
    os << "front = " << Q.front << ", rear = " << Q.rear << endl;
    for (int i = Q.front; i != Q.rear; i = (i + 1) % Q.maxSize) {
        os << Q.elements[i] << " ";
    }
    os << endl;
    return os;
};

#endif