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
    SeqQueue(int size = SIZE);                                       // ���캯��
    ~SeqQueue() { delete[] elements; }                               // ��������
    bool enQueue(const T &x);                                        // ��Ԫ��x������
    bool deQueue(T &x);                                              // ��Ԫ�س�����
    bool getFront(T &x) const;                                       // ��ȡͷ�ڵ�Ԫ��ֵ
    bool isEmpty() const { return (front == rear) ? true : false; }; // �п�
    bool isFull() const                                              // ����
    {
        return ((rear + 1) % maxSize == front) ? true : false;
    }
    int size() const // ��ȡ��С
    {
        return (rear - front + maxSize) % maxSize;
    }
    void makeEmpty() { front = rear = 0; } // �ÿ�
    template <class U>
    friend ostream &operator<<(ostream &os, SeqQueue<U> &Q);

protected:
    int rear, front;
    T *elements;
    int maxSize;
};

// ���캯��
template <class T>
SeqQueue<T>::SeqQueue(int size) : front(0), rear(0), maxSize(size)
{
    elements = new T[maxSize];
    assert(elements != NULL);
};

// ���
template <class T>
bool SeqQueue<T>::enQueue(const T &x)
{
    if (isFull()) // ����
    {
        return false;
    }
    elements[rear] = x;
    rear = (rear + 1) % maxSize;
    return true;
};

// ��ȡ��ͷԪ��
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

// ������
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

// ������������
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