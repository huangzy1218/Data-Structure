/**
 * @file dbllist.h
 * @author Huang Z.Y.
 * @brief ˫������(double linked list)��ÿ�����ݽ���ж�������ָ�룬�ֱ�ָ��ֱ�Ӻ�̺�ֱ��ǰ����
 * �ɴ�˫�������е�����һ����㿪ʼ����������ǰ�����ͺ�̽�㡣
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DBLLIST_H
#define DBLLIST_H
#include <iostream>
using namespace std;

template <class T>
struct DblNode {
    T data;
    DblNode<T>*pre, *next; // ǰ��������������̣�������ָ��
    DblNode(DblNode<T>* left = nullptr, DblNode<T>* right = NULL)
        : pre(left)
        , next(right)
    {
    } // ���캯��
    DblNode(T value = -1, DblNode<T>* left = nullptr, DblNode<T>* right = nullptr)
        : data(value)
        , pre(left)
        , next(right)
    {
    } // ���캯��
    DblNode<T>& operator=(DblNode<T>& rhs); // = ����
};

template <class T>
DblNode<T>& DblNode<T>::operator=(DblNode<T>& rhs)
{
    if (this == &rhs) {
        return *this;
    }
    data = rhs.data;
    pre = rhs.pre;
    next = rhs.next;
    return *this;
};

template <class T>
class DblList {
public:
    DblList() { first = new DblNode<T>(); } // ���캯������ͷ���
    DblList(const T& x) { first = new DblNode<T>(x); } // ���캯��
    DblList(DblList<T>& L); // �������캯��
    ~DblList() { makeEmpty(); } // ��������
    void makeEmpty(); // �ÿ�
    int length() const; // ��ȡ����
    int size() const; // ��ȡ��С
    DblNode<T>* getHead() const { return first; } // ��ȡͷ���
    DblNode<T>* search(T& x) const; // ����
    DblNode<T>* locate(int i) const; // ��λ
    T& getPreData(int i); // ��ȡǰ��Ԫ��ֵ
    T& getNextData(int i); // ��ȡ���Ԫ��ֵ
    bool getData(int i, T& x) const; // ��ȡָ��λԪ��ֵ
    void setData(int i, const T& x); // ����ָ��λԪ��ֵ
    bool insert(int i, const T& x); // ��ָ��λ�����Ԫ��
    bool remove(int i, T& x); // ɾ��ָ��λԪ��
    bool isEmpty() const { return first->next == first; } // �п�
    bool isFull() const { return false; } // ����
    void sort(); // ����
    void input(); // ����
    void output(); // ���
    DblList<T>& operator=(DblList<T>& L); // ��ֵ���������
protected:
    DblNode<T>* first;
};

// ��������
template <class T>
DblList<T>::DblList(DblList<T>& L)
{
    T value;
    DblNode<T>* srcptr = L.getHead(); // ��ȡ L ��ͷ���
    DblNode<T>* destptr = this->getHead(); // ��ȡͷ���

    while (srcptr->next != nullptr) { // δ�ﵽ L β��
        value = srcptr->next->data;
        destptr->next = new DblNode<T>(value);
        destptr->next->pre = destptr;
        srcptr = srcptr->next;
        destptr = destptr->next;
    }
    destptr->next = first; // β�����nullptr����
};

// �ÿ�
template <class T>
void DblList<T>::makeEmpty()
{
    DblNode<T>* tempt; // ��ʱ��㣬��������ɾ��
    while (first->next != first) // ͷ�ڵ���޽��
    {
        tempt = first->next;
        first->next = tempt->next; // ͷ�ڵ����һ��ָ��ɾ��������һ�����
        delete tempt; // ɾ���ý��
    }
};

// ��ȡ����
template <class T>
int DblList<T>::length() const
{
    int count = 0;
    DblNode<T>* current = first->next;

    while (current != first) // ��ǰ���ǿ�
    {
        ++count;
        current = current->next;
    }
    return count;
};

// ��ȡ��С
template <class T>
int DblList<T>::size() const
{
    return length();
};

// ����
template <class T>
DblNode<T>* DblList<T>::search(T& x) const
{
    DblNode<T>* ptr = first->next;

    while (ptr != nullptr) {
        if (ptr->data == x) {
            break;
        } else {
            ptr = ptr->next; // ��������
        }
    }
    return ptr; // ���ز��ҽ��
};

// ��λ
template <class T>
DblNode<T>* DblList<T>::locate(int i) const
{
    if (i < 0) { // ��Ч�±�
        return nullptr;
    }
    int count = 0; // ���ڼ�����Ԫ���±��0��ʼ
    DblNode<T>* ptr = first;
    while (ptr->next != first && count < i) {
        ptr = ptr->next;
        ++count;
    }
    return ptr;
};

// ��ȡָ��λԪ��ֵ
template <class T>
bool DblList<T>::getData(int i, T& x) const
{
    if (i < 0) { // ��Ч�±�
        return false;
    }
    DblNode<T>* ptr = locate(i); // ��λԪ��
    if (ptr != nullptr) // Ϊ�ǿս��
    {
        x = ptr->data;
        return true;
    } else {
        return false;
    }
};

// ��ȡǰ��Ԫ��ֵ
template <class T>
T& DblList<T>::getPreData(int i)
{
    DblNode<T>* current = locate(i);
    return current->pre->data;
};

// ��ȡ���Ԫ��ֵ
template <class T>
T& DblList<T>::getNextData(int i)
{
    DblNode<T>* current = locate(i);
    return current->next->data;
};

// ����ָ��λԪ��ֵ
template <class T>
void DblList<T>::setData(int i, const T& x)
{
    if (i < 0) { // ��Ч�±�
        return;
    }
    DblNode<T>* ptr = locate(i); // ��λԪ��
    if (ptr != first) // Ϊ�ǿս��
    {
        ptr->data = x;
    } else {
        return;
    }
};

// ��ָ��λ�����Ԫ��
template <class T>
bool DblList<T>::insert(int i, const T& x)
{
    if (i < 0) { // ��Ч�±�
        return false;
    }
    DblNode<T>* ptr = locate(i);
    if (ptr == first) { // Ϊ�ս��
        return false;
    }
    DblNode<T>* newNode = new DblNode<T>(x);
    if (newNode == nullptr) {
        cerr << "�ڴ����ʧ��" << endl;
        exit(1);
    } else {
        newNode->next = ptr->next; // �½ڵ����һ�����Ϊԭ������һ�����
        ptr->next->pre = newNode;
        ptr->next = newNode;
        newNode->pre = ptr;
    }
    return true;
};

// ɾ��ָ��λԪ��
template <class T>
bool DblList<T>::remove(int i, T& x)
{
    if (i < 0) { // ��Ч�±�
        return false;
    }
    DblNode<T>* current = locate(i - 1); // ��λ��ɾ��Ԫ��ǰһԪ�أ�ע�������±���ʵ�ʴ洢λ�����1
    // �ʶ�λi����i-1
    if (current == nullptr || current->next == nullptr) // ɾ��Ԫ��Ϊͷ�ڵ��β���
    {
        return false;
    } else {
        DblNode<T>* delPtr = current->next;
        current->next = delPtr->next;
        delPtr->next->pre = current;
        x = delPtr->data;
        delete delPtr;
        return true;
    }
};

template <class T>
void DblList<T>::sort()
{
    for (int i = 1; i <= length(); i++) {
        for (int j = 1; j <= length() - i; j++) // ע���±���ʼ
        {
            DblNode<T>* t1 = locate(j);
            DblNode<T>* t2 = locate(j + 1);
            if (t1->data > t2->data) {
                T temp = t1->data;
                t1->data = t2->data;
                t2->data = temp;
            }
        }
    }
};

// ���
template <class T>
void DblList<T>::output()
{
    DblNode<T>* current = first->next;

    while (current != first) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
};

// ����
template <class T>
void DblList<T>::input()
{
    int n;
    T x;
    cout << "��ʼ����˫��������������Ԫ��������������Ԫ�أ�" << endl;
    cin >> n;
    DblNode<T>* current = first; // ��ǰ���ָ��ͷ�ڵ�
    while (n--) {
        cin >> x;
        current->next = new DblNode<T>(x); // ��������
        current->next->pre = current;
        current = current->next;
    }
    current->next = first;
}

#endif