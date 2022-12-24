#include "Stack.h"
#include <cassert>
#include <iostream>
using namespace std;
template <class T>
struct LinkNode {
    T data;
    LinkNode<T>* link;
    LinkNode(LinkNode<T>* ptr = NULL) { link = ptr; }
    LinkNode(const T& item, LinkNode* ptr = NULL)
    {
        data = item;
        link = ptr;
    }
};

template <class T>
class LinkedStack;
template <class U>
ostream& operator<<(ostream& os, LinkedStack<U>& S);
template <class T>
class LinkedStack : public Stack<T> {
public:
    LinkedStack()
        : top(NULL)
    {
    } // 构造函�?
    ~LinkedStack() { makeEmpty(); } // 析构函数
    void push(const T& x); // 入栈
    bool pop(T& x); // 出栈
    bool getTop(T& x); // 获取栈顶元素
    bool isEmpty() const { return top == NULL; } // 判空
    bool isFull() const { return false; } // 判满
    int size() const; // 获取大小
    void makeEmpty(); // 置空
    template <class U>
    friend ostream& operator<<(ostream& os, LinkedStack<U>& S);
    // 输出运算符重�?
private:
    LinkNode<T>* top;
};

// 置空
template <class T>
void LinkedStack<T>::makeEmpty()
{
    LinkNode<T>* p; // 遍历各结�?
    while (top != NULL) {
        p = top;
        top = p->link;
        delete p; // 依次删除各结�?
    }
};

// 入栈
template <class T>
void LinkedStack<T>::push(const T& x)
{
    top = new LinkNode<T>(x, top); // 入栈
    assert(top != NULL);
};

// 出栈
template <class T>
bool LinkedStack<T>::pop(T& x)
{
    if (isEmpty()) // 栈空
    {
        return false;
    }
    LinkNode<T>* p = top; // 出栈元素
    top = top->link;
    x = p->data;
    delete p; // 删除出栈元素
    return true;
};

// 获取栈顶元素
template <class T>
bool LinkedStack<T>::getTop(T& x)
{
    if (isEmpty()) // 判空
    {
        return false;
    }
    x = top->data;
    return true;
};

// 获取大小
template <class T>
int LinkedStack<T>::size() const
{
    LinkNode<T>* p = top; // 用于遍历
    int count = 0;
    while (p != NULL) {
        p = p->link;
        ++count;
    }
    return count;
};

// 输出运算符重�?
template <class T>
ostream& operator<<(ostream& os, LinkedStack<T>& s)
{
    LinkNode<T>* p = s.top;
    while (p != NULL) {
        os << p->data << " ";
        p = p->link;
    }
    os << endl;
    return os;
};
