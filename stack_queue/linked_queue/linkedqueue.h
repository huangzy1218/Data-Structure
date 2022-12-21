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
    LinkedQueue() : rear(NULL), front(NULL) {}                       // ���캯��
    ~LinkedQueue() { makeEmpty(); }                                  // ��������
    bool enQueue(const T &x);                                        // ��Ԫ��x������
    bool deQueue(T &x);                                              // ��Ԫ�س�����
    bool getFront(T &x) const;                                       // ��ȡͷ�ڵ�Ԫ��ֵ
    bool isEmpty() const { return (front == NULL) ? true : false; }; // �п�
    bool isFull() const { return false; }                            // ����
    int size() const;                                                // ��ȡ��С
    void makeEmpty();                                                // �ÿ�
    template <class U>
    friend ostream &operator<<(ostream &os, LinkedQueue<U> &Q);

protected:
    LinkNode<T> *front, *rear;
};

// �ÿ�
template <class T>
void LinkedQueue<T>::makeEmpty()
{
    LinkNode<T> *p;
    while (front != NULL)
    {
        p = front;
        front = front->link;
        delete p; // ���ɾ�������еĽ�㣬�Ӷ��׿�ʼ
    }
};

// ���
template <class T>
bool LinkedQueue<T>::enQueue(const T &x)
{
    if (front == NULL) // ����Ϊ��
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

// ����
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

// ��ȡ����Ԫ��
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

// ��ȡ��С
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

// ������������
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