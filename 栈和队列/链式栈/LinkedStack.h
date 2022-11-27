#include <iostream>
#include "List.h"
#include "Stack.h"

template <class T>
class LinkedStack: public Stack<T> {
public:
    LinkedStack(): top(NULL) {}                 // 构造函数，置空栈
    ~LinkedStack() { MakeEmpty(); }             // 析构函数
    void Push(const T& x);                      // 进栈
    void Pop(T &x);                             // 出栈
    bool GetTop(T& x);                          // 读取栈顶元素
    bool IsEmpty() const { return top == NULL; }// 判空
    int GetSize() const;                        // 求栈的元素个数
    friend ostream& operator<<(ostream& os, LinkedStack<T>& s);
    // 运算符重载：输出
private:
    LinkNode<T>* top;
};

// 置空栈
template <class T>
LinkedStack<T>::MakeEmpty()
{
    LinkedStack<T>* p;              // 记录删除的结点
    while (top != NULL) {
        p = top;
        top = p->link;
        delete p;                   // 释放结点
    }
};

template <class T>
void LinkedStack<T>::Push(const T& x)
{
    top = new LinkNode<T>(x, top);  // 在原top结点后插入新结点，头插法
    assert(top != NULL);            // 断言
};

template <class T>
bool LinkedStack<T>::Pop(T& x) 
{
    if (IsEmpty()) {                // 若链表为空，则无法出栈
        return false;
    }
    LinkNode<T>* p = top;           // 暂存栈顶元素
    top = top->link;
    x = p->data;                    // 保存栈顶结点的值
    delete p;                       // 释放栈顶元素
    return true;
};

// 获取头结点
template <class T>
bool LinkedStack<T>::GetTop(T& x) const 
{
    if (IsEmpty()) {
        return false;
    }
    x = top->data;
    retur true;
};

// 求栈的元素个数
template <class T>
int LinkedStack<T>::GetSize() const
{
    LinkNode<T>* p = top;          // 实现链表遍历
    int k = 0;
    while (p != NULL) {             
        p = p->link;
        k++;
    }
    return k;
}

// 运算符重构：输出
template <class T>
ostream& operator << (ostream& os, LinkedStack<T>& s)
{
    os << "栈中元素个数：" << s.GetSize << endl;

    LinkNode<T>* p = s.top;
    int i = 0;
    while (p != NULL) {
        os << ++i << ": " << p->data << endl;
        p = p->link; 
    }
    return os;

} 
