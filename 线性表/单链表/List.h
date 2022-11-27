#include <cstdlib>
#include <iostream>
#include "LinearList.h"
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
    LinkNode<T> &operator=(LinkNode<T> &rhs);
};

template <class T>
LinkNode<T> &LinkNode<T>::operator=(LinkNode<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    data = rhs.data;
    link = rhs.data;
    return *this;
};

template <class T>
class List : public LinearList<T>
{
public:
    List() { first = new LinkNode<T>(); }                // ���캯������ͷ���
    List(const T &x) { first = new LinkNode<T>(x); }     // ���캯��
    List(List<T> &L);                                    // �������캯��
    ~List() { makeEmpty(); }                             // ��������
    void makeEmpty();                                    // �ÿ�
    int length() const;                                  // ��ȡ����
    int size() const;                                    // ��ȡ��С
    LinkNode<T> *getHead() const { return first; }       // ��ȡͷ���
    LinkNode<T> *search(T &x);                           // ����
    LinkNode<T> *locate(int i) const;                    // ��λ
    bool getData(int i, T &x) const;                     // ��ȡָ��λԪ��ֵ
    void setData(int i, const T &x);                     // ����ָ��λԪ��ֵ
    bool insert(int i, const T &x);                      // ��ָ��λ�����Ԫ��
    bool remove(int i, T &x);                            // ɾ��ָ��λԪ��
    bool isEmpty() const { return first->link == NULL; } // �п�
    bool isFull() const { return false; }                // ����
    void sort();                                         // ����
    void input();                                        // ����
    void output();                                       // ���
    List<T> &operator=(List<T> &L);                      // ��ֵ���������
protected:
    LinkNode<T> *first;
};

// ��������
template <class T>
List<T>::List(List<T> &L)
{
    T value;
    LinkNode<T> *srcptr = L.getHead();      // ��ȡL��ͷ���
    LinkNode<T> *destptr = this->getHead(); // ��ȡͷ���

    while (srcptr->link != NULL) // δ�ﵽLβ��
    {
        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(value);
        srcptr = srcptr->link;
        destptr = destptr->link;
    }
    destptr->link = NULL; // β�����NULL����
};

// �ÿ�
template <class T>
void List<T>::makeEmpty()
{
    LinkNode<T> *tempt;         // ��ʱ��㣬��������ɾ��
    while (first->link != NULL) // ͷ�ڵ���޽��
    {
        tempt = first->link;
        first->link = tempt->link; // ͷ�ڵ����һ��ָ��ɾ��������һ�����
        delete tempt;              // ɾ���ý��
    }
};

// ��ȡ����
template <class T>
int List<T>::length() const
{
    int count = 0;
    LinkNode<T> *current = first->link;

    while (current != NULL) // ��ǰ���ǿ�
    {
        ++count;
        current = current->link;
    }
    return count;
};

// ��ȡ��С
template <class T>
int List<T>::size() const
{
    return length();
};

// ����
template <class T>
LinkNode<T> *List<T>::search(T &x)
{
    LinkNode<T> *ptr = first->link;

    while (ptr != NULL)
    {
        if (ptr->data == x)
        {
            break;
        }
        else
        {
            ptr = ptr->link; // ��������
        }
    }
    return ptr; // ���ز��ҽ��
};

// ��λ
template <class T>
LinkNode<T> *List<T>::locate(int i) const
{
    if (i < 0) // ��Ч�±�
    {
        return NULL;
    }
    int count = 0; // ���ڼ�����Ԫ���±��0��ʼ
    LinkNode<T> *ptr = first;
    while (ptr != NULL && count < i)
    {
        ptr = ptr->link;
        ++count;
    }
    return ptr;
};

// ��ȡָ��λԪ��ֵ
template <class T>
bool List<T>::getData(int i, T &x) const
{
    if (i < 0) // ��Ч�±�
    {
        return false;
    }
    LinkNode<T> *ptr = locate(i); // ��λԪ��
    if (ptr != NULL)              // Ϊ�ǿս��
    {
        x = ptr->data;
        return true;
    }
    else
    {
        return false;
    }
};

// ����ָ��λԪ��ֵ
template <class T>
void List<T>::setData(int i, const T &x)
{
    if (i < 0) // ��Ч�±�
    {
        return;
    }
    LinkNode<T> *ptr = locate(i); // ��λԪ��
    if (ptr != NULL)              // Ϊ�ǿս��
    {
        ptr->data = x;
    }
    else
    {
        return;
    }
};

// ��ָ��λ�����Ԫ��
template <class T>
bool List<T>::insert(int i, const T &x)
{
    if (i < 0) // ��Ч�±�
    {
        return false;
    }
    LinkNode<T> *ptr = locate(i);
    if (ptr == NULL) // Ϊ�ս��
    {
        return false;
    }
    LinkNode<T> *newNode = new LinkNode<T>(x);
    if (newNode == NULL)
    {
        cerr << "�ڴ����ʧ��" << endl;
        exit(1);
    }
    else
    {
        newNode->link = ptr->link; // �½ڵ����һ�����Ϊԭ������һ�����
        ptr->link = newNode;       //ԭ������һ�����Ϊ�½��
    }
    return true;
};

// ɾ��ָ��λԪ��
template <class T>
bool List<T>::remove(int i, T &x)
{
    if (i < 0) // ��Ч�±�
    {
        return false;
    }
    LinkNode<T> *current = locate(i - 1); // ��λ��ɾ��Ԫ��ǰһԪ�أ�ע�������±���ʵ�ʴ洢λ�����1
    // �ʶ�λi����i-1
    if (current == NULL || current->link == NULL) // ɾ��Ԫ��Ϊͷ�ڵ��β���
    {
        return false;
    }
    else
    {
        LinkNode<T> *delPtr = current->link;
        current->link = delPtr->link;
        x = delPtr->data;
        delete delPtr;
        return true;
    }
};

template <class T>
void List<T>::sort()
{
    for (int i = 1; i <= length(); i++)
    {
        for (int j = 1; j <= length() - i; j++) // ע���±���ʼ
        {
            LinkNode<T> *t1 = locate(j);
            LinkNode<T> *t2 = locate(j + 1);
            if (t1->data > t2->data)
            {
                T temp = t1->data;
                t1->data = t2->data;
                t2->data = temp;
            }
        }
    }
};

// ���
template <class T>
void List<T>::output()
{
    LinkNode<T> *current = first->link;

    while (current != NULL)
    {
        cout << current->data << " ";
        current = current->link;
    }
    cout << endl;
};

// ����
template <class T>
void List<T>::input()
{
    int n;
    T x;
    cout << "��ʼ����������������Ҫ�����Ԫ��������������Ԫ�أ�" << endl;
    cin >> n;
    LinkNode<T> *current = first; // ��ǰ���ָ��ͷ�ڵ�
    while (n--)
    {
        cin >> x;
        current->link = new LinkNode<T>(x); // ��������
        current = current->link;
    }
    current->link = NULL;
}
