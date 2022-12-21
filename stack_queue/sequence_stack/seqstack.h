#include <cassert>
#include <iostream>
#include "Stack.h"
using namespace std;
const int stackIncreasement = 20; // Ĭ��ջ��ʱ�����ڴ�ռ�
template <class T>
class SeqStack;
template <class U>
ostream &operator<<(ostream &os, SeqStack<U> &S);
template <class T>
class SeqStack : public Stack<T>
{
public:
    SeqStack(int sz = 50);                     // ���캯��
    ~SeqStack() { delete[] elements; }         // ��������
    void push(const T &x);                     // ��ջ
    bool pop(T &x);                            // ��ջ
    bool getTop(T &x);                         // ��ȡջ��Ԫ��
    bool isEmpty() const { return top == -1; } // �п�
    bool isFull() const { return top == maxSize - 1; }
    // ����
    int size() const { return top + 1; } // ��ȡ��С
    void makeEmpty() { top = -1; }       // �ÿ�
    template <class U>
    friend ostream &operator<<(ostream &os, SeqStack<U> &S); // ������������
private:
    T *elements;            // Ԫ��
    int top;                // ջ��Ԫ���±�
    int maxSize;            // ������
    void overflowProcess(); // ջ���ʱ�Ĵ���
};

// ���캯��
template <class T>
SeqStack<T>::SeqStack(int sz) : top(-1), maxSize(sz)
{
    elements = new T[maxSize];
    assert(elements != NULL);
}

// ջ�������
template <class T>
void SeqStack<T>::overflowProcess()
{
    T *newArray = new T[maxSize + stackIncreasement];
    if (newArray == NULL)
    {
        cerr << "�ڴ�������" << endl;
    }
    else
    {
        for (int i = 0; i <= top; i++)
        {
            newArray[i] = elements[i];
        }
        maxSize += stackIncreasement;
        delete[] elements;
        elements = newArray;
    }
}

// ��ջ
template <class T>
void SeqStack<T>::push(const T &x)
{
    if (isFull()) // ջ��
    {
        overflowProcess();
    }
    elements[++top] = x;
}

// ��ջ
template <class T>
bool SeqStack<T>::pop(T &x)
{
    if (isEmpty())
    {
        return false;
    }
    else
    {
        x = elements[top--];
        return true;
    }
};

// ��ȡջ��Ԫ��
template <class T>
bool SeqStack<T>::getTop(T &x)
{
    if (isEmpty())
    {
        return false;
    }
    else
    {
        x = elements[top];
        return true;
    }
};

// ������������
template <class T>
ostream &operator<<(ostream &os, SeqStack<T> &S)
{
    os << "top = " << S.top << endl;
    for (int i = 0; i <= S.top; i++)
    {
        os << S.elements[i] << " ";
    }
    os << endl;
    return os;
};
