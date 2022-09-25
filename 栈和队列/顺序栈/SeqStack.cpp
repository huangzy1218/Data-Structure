#include <cassert>
#include <iostream>
#include "stack.h"
const int stackIncreasement = 20;           // 栈溢出时扩展空间的增量
template <class T>
class SeqStack: public Stack<T> {
public:
    SeqStack(int sz = 50);                  // 建立空栈
    ~SeqStack()  { delete[] elements; }     // 析构函数
    void Push(const T& x);                  // 若IsFull()，则溢出处理，否则将x插入栈顶
    bool Pop(T &x);                         // 若IsEmpty()，不执行退栈，否则退掉栈顶元素
    bool GetTop(T &x);                      // 若IsEmpty()，返回false，否则通过引用得到栈顶元素值
    bool IsEmpty() const { return top == -1; }
    // 判栈空
    bool IsFull() const { return top == MaxSize - 1; }
    // 判栈满
    int GetSize() const { return top + 1; } // 返回栈中元素个数
    void MakeEmpty() { top = -1; }          // 清空栈
    friend ostream& operator << (ostream& os, SeqStack<T>& s);
    // 输出栈中元素的重载操作<<
private:
    T* elements;                            // 存放栈中元素的栈数组
    int top;                                // 栈顶指针
    int MaxSize;                            // 栈的最大容量
    void OverflowProcess();                 // 栈溢出的处理
};

// 构造函数
template <class T>
SeqStack<T>::SeqStack(int sz): top(-1), MaxSize(sz)
{
    elements = new T[MaxSize];
    assert(elements != NULL);
}

// 栈溢出处理
template <class T>
void SeqStack<T>::OverflowProcess()
{
    T* newArray = new T[MaxSize + stackIncreasement];
    if (newArray == NULL) {
        cerr << "内存分配失败" << endl;
    } else {
        for (int i = 0; i <= top; i++) {
            newArray[i] = elements[i];
        }
        MaxSize += stackIncreasement;
        delete[] elements;
        elements = newArray;
    }
}

// 若IsFull()，则溢出处理，否则将x插入栈顶
template <class T>
void SeqStack<T>::Push(const T& x)
{
    if (IsFull) {
        OverflowProcess();
    }
    elements[++top] = x;
}

// 若IsEmpty()，不执行退栈，否则退掉栈顶元素
template <class T>
bool SeqStack<T>::Pop(T &x)
{
    if (IsEmpty()) {
        return false;
    } else {
        x = elements[top--];
        return true;
    }
}

// 若IsEmpty()，返回false，否则通过引用得到栈顶元素值
template <class T>::GetTop(T &x)
{
    if (IsEmpty()) {
        return false;
    } else {
        x = elements[top];
        return true;
    }
}

// 输出栈中元素的重载操作<<
template <class T>
ostream& operator << (ostream& os, SeqStack<T>& s)
{
    os << "top = " << s.top << endl;
    for (int i = 0; i <= top; i++) {
        os << i << ": " << s.elements[i] << endl;
    }
}

