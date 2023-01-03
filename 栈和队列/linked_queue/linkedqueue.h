/**
 * @file linkedqueue.h
 * @author Huang Z.Y.
 * @brief ��ʽ����(linked queue)Ϊ������ʽ�洢�ṹ�Ķ��С��ܹ��˷�������ʵ�ֵ�˳����пռ������ʲ��ߵ��ص㣬
 * ����ҪΪÿ��ջԪ�ط�������ָ��ռ��������ָ����
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include "Queue.h"
#include <iostream>
using namespace std;
template <class T>
struct LinkNode {
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
class LinkedQueue;
template <class T>
ostream& operator<<(ostream& os, LinkedQueue<T>& Q);
template <class T>
class LinkedQueue : public Queue<T> {
public:
    LinkedQueue()
        : rear(nullptr)
        , front(nullptr)
    {
    } // ���캯��
    ~LinkedQueue() { makeEmpty(); } // ��������
    bool enQueue(const T& x); // ��Ԫ��x������
    bool deQueue(T& x); // ��Ԫ�س�����
    bool getFront(T& x) const; // ��ȡͷ�ڵ�Ԫ��ֵ
    bool isEmpty() const { return (front == nullptr) ? true : false; }; // �п�
    bool isFull() const { return false; } // ����
    int size() const; // ��ȡ��С
    void makeEmpty(); // �ÿ�
    template <class U>
    friend ostream& operator<<(ostream& os, LinkedQueue<U>& Q);

protected:
    LinkNode<T>*front, *rear;
};

// �ÿ�
template <class T>
void LinkedQueue<T>::makeEmpty()
{
    LinkNode<T>* p;
    while (front != nullptr) {
        p = front;
        front = front->link;
        delete p; // ���ɾ�������еĽ�㣬�Ӷ��׿�ʼ
    }
};

// ���
template <class T>
bool LinkedQueue<T>::enQueue(const T& x)
{
    if (front == nullptr) // ����Ϊ��
    {
        front = rear = new LinkNode<T>(x);
        if (front == nullptr) {
            return false;
        }
    } else {
        rear->link = new LinkNode<T>(x);
        if (rear->link == nullptr) {
            return false;
        }
        rear = rear->link;
    }
    return true;
};

// ����
template <class T>
bool LinkedQueue<T>::deQueue(T& x)
{
    if (isEmpty()) {
        return false;
    }
    LinkNode<T>* p = front;
    x = front->data;
    front = front->link;
    delete p;
    return true;
};

// ��ȡ����Ԫ��
template <class T>
bool LinkedQueue<T>::getFront(T& x) const
{
    if (isEmpty()) {
        return false;
    }
    x = front->data;
    return true;
};

// ��ȡ��С
template <class T>
int LinkedQueue<T>::size() const
{
    LinkNode<T>* p = front;
    int count = 0;
    while (p != nullptr) {
        ++count;
        p = p->link;
    }
    return count;
};

// ������������
template <class T>
ostream& operator<<(ostream& os, LinkedQueue<T>& Q)
{
    LinkNode<T>* q = Q.front;
    while (q != nullptr) {
        os << q->data << " ";
        q = q->link;
    }
    os << endl;
    return os;
};

#endif