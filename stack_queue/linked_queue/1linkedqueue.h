#include "Queue.h"
#include <iostream>
using namespace std;
template <class T>
struct LinkNode
{
    T data;
    LinkNode<T> *link;
    LinkNode(LinkNode<T> *ptr = NULL) { link = ptr; }
    LinkNode(const T &item, LinkNode *ptr = NULL)
    {
        data = item;
        link = ptr;
    }
};

template <class T>
class LinkedQueue;
template <class T>
ostream &operator<<(ostream &os, LinkedQueue<T> &Q);
template <class T>
class LinkedQueue : public Queue<T>
{
public:
    LinkedQueue() : rear(NULL), front(NULL) {}                       // 构造函数
    ~LinkedQueue() { makeEmpty(); }                                  // 析构函数
    bool enQueue(const T &x);                                        // 新元素x进对列
    bool deQueue(T &x);                                              // 新元素出队列
    bool getFront(T &x) const;                                       // 读取头节点元素值
    bool isEmpty() const { return (front == NULL) ? true : false; }; // 判空
    bool isFull() const { return false; }                            // 判满
    int size() const;                                                // 获取大小
    void makeEmpty();                                                // 置空
    template <class U>
    friend ostream &operator<<(ostream &os, LinkedQueue<U> &Q);

protected:
    LinkNode<T> *front, *rear;
};

// 置空
template <class T>
void LinkedQueue<T>::makeEmpty()
{
    LinkNode<T> *p;
    while (front != NULL)
    {
        p = front;
        front = front->link;
        delete p; // 逐个删除队列中的结点，从队首开始
    }
};

// 入队
template <class T>
bool LinkedQueue<T>::enQueue(const T &x)
{
    if (front == NULL) // 队列为空
    {
        front = rear = new LinkNode<T>(x);
        if (front == NULL)
        {
            return false;
        }
    }
    else
    {
        rear->link = new LinkNode<T>(x);
        if (rear->link == NULL)
        {
            return false;
        }
        rear = rear->link;
    }
    return true;
};

// 出队
template <class T>
bool LinkedQueue<T>::deQueue(T &x)
{
    if (isEmpty())
    {
        return false;
    }
    LinkNode<T> *p = front;
    x = front->data;
    front = front->link;
    delete p;
    return true;
};

// 获取队首元素
template <class T>
bool LinkedQueue<T>::getFront(T &x) const
{
    if (isEmpty())
    {
        return false;
    }
    x = front->data;
    return true;
};

// 获取大小
template <class T>
int LinkedQueue<T>::size() const
{
    LinkNode<T> *p = front;
    int count = 0;
    while (p != NULL)
    {
        ++count;
        p = p->link;
    }
    return count;
};

// 输出运算符重载
template <class T>
ostream &operator<<(ostream &os, LinkedQueue<T> &Q)
{
    LinkNode<T> *q = Q.front;
    while (q != NULL)
    {
        os << q->data << " ";
        q = q->link;
    }
    os << endl;
    return os;
};