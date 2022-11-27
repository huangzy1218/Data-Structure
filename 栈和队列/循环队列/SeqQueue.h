#include <cassert>
#include <iostream>
#include "Queue.h"
using namespace std;
template <class T>
class SeqQueue;
template <class T>
ostream &operator<<(ostream &os, SeqQueue<T> &Q);
template <class T>
class SeqQueue : public Queue<T>
{
public:
    SeqQueue(int size = SIZE);                                       // 构造函数
    ~SeqQueue() { delete[] elements; }                               // 析构函数
    bool enQueue(const T &x);                                        // 新元素x进对列
    bool deQueue(T &x);                                              // 新元素出队列
    bool getFront(T &x) const;                                       // 读取头节点元素值
    bool isEmpty() const { return (front == rear) ? true : false; }; // 判空
    bool isFull() const                                              // 判满
    {
        return ((rear + 1) % maxSize == front) ? true : false;
    }
    int size() const // 获取大小
    {
        return (rear - front + maxSize) % maxSize;
    }
    void makeEmpty() { front = rear = 0; } // 置空
    template <class U>
    friend ostream &operator<<(ostream &os, SeqQueue<U> &Q);

protected:
    int rear, front;
    T *elements;
    int maxSize;
};

// 构造函数
template <class T>
SeqQueue<T>::SeqQueue(int size) : front(0), rear(0), maxSize(size)
{
    elements = new T[maxSize];
    assert(elements != NULL);
};

// 入队
template <class T>
bool SeqQueue<T>::enQueue(const T &x)
{
    if (isFull()) // 队满
    {
        return false;
    }
    elements[rear] = x;
    rear = (rear + 1) % maxSize;
    return true;
};

// 获取队头元素
template <class T>
bool SeqQueue<T>::getFront(T &x) const
{
    if (isEmpty())
    {
        return false;
    }
    x = elements[front];
    return true;
};

// 出队列
template <class T>
bool SeqQueue<T>::deQueue(T &x)
{
    if (isEmpty())
    {
        return false;
    }
    x = elements[front];
    front = (front + 1) % maxSize;
    return true;
};

// 输出运算符重载
template <class T>
ostream &operator<<(ostream &os, SeqQueue<T> &Q)
{
    os << "front = " << Q.front << ", rear = " << Q.rear << endl;
    for (int i = Q.front; i != Q.rear; i = (i + 1) % Q.maxSize)
    {
        os << Q.elements[i] << " ";
    }
    os << endl;
    return os;
};