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
    List() { first = new LinkNode<T>(); }                // 构造函数，含头结点
    List(const T &x) { first = new LinkNode<T>(x); }     // 构造函数
    List(List<T> &L);                                    // 拷贝构造函数
    ~List() { makeEmpty(); }                             // 析构函数
    void makeEmpty();                                    // 置空
    int length() const;                                  // 获取长度
    int size() const;                                    // 获取大小
    LinkNode<T> *getHead() const { return first; }       // 获取头结点
    LinkNode<T> *search(T &x);                           // 查找
    LinkNode<T> *locate(int i) const;                    // 定位
    bool getData(int i, T &x) const;                     // 获取指定位元素值
    void setData(int i, const T &x);                     // 设置指定位元素值
    bool insert(int i, const T &x);                      // 在指定位后插入元素
    bool remove(int i, T &x);                            // 删除指定位元素
    bool isEmpty() const { return first->link == NULL; } // 判空
    bool isFull() const { return false; }                // 判满
    void sort();                                         // 排序
    void input();                                        // 输入
    void output();                                       // 输出
    List<T> &operator=(List<T> &L);                      // 赋值运算符重载
protected:
    LinkNode<T> *first;
};

// 拷贝构造
template <class T>
List<T>::List(List<T> &L)
{
    T value;
    LinkNode<T> *srcptr = L.getHead();      // 获取L的头结点
    LinkNode<T> *destptr = this->getHead(); // 获取头结点

    while (srcptr->link != NULL) // 未达到L尾部
    {
        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(value);
        srcptr = srcptr->link;
        destptr = destptr->link;
    }
    destptr->link = NULL; // 尾结点以NULL结束
};

// 置空
template <class T>
void List<T>::makeEmpty()
{
    LinkNode<T> *tempt;         // 临时结点，用于依次删除
    while (first->link != NULL) // 头节点后无结点
    {
        tempt = first->link;
        first->link = tempt->link; // 头节点的下一个指向删除结点的下一个结点
        delete tempt;              // 删除该结点
    }
};

// 获取长度
template <class T>
int List<T>::length() const
{
    int count = 0;
    LinkNode<T> *current = first->link;

    while (current != NULL) // 当前结点非空
    {
        ++count;
        current = current->link;
    }
    return count;
};

// 获取大小
template <class T>
int List<T>::size() const
{
    return length();
};

// 查找
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
            ptr = ptr->link; // 继续遍历
        }
    }
    return ptr; // 返回查找结点
};

// 定位
template <class T>
LinkNode<T> *List<T>::locate(int i) const
{
    if (i < 0) // 无效下标
    {
        return NULL;
    }
    int count = 0; // 用于计数，元素下标从0开始
    LinkNode<T> *ptr = first;
    while (ptr != NULL && count < i)
    {
        ptr = ptr->link;
        ++count;
    }
    return ptr;
};

// 获取指定位元素值
template <class T>
bool List<T>::getData(int i, T &x) const
{
    if (i < 0) // 无效下标
    {
        return false;
    }
    LinkNode<T> *ptr = locate(i); // 定位元素
    if (ptr != NULL)              // 为非空结点
    {
        x = ptr->data;
        return true;
    }
    else
    {
        return false;
    }
};

// 设置指定位元素值
template <class T>
void List<T>::setData(int i, const T &x)
{
    if (i < 0) // 无效下标
    {
        return;
    }
    LinkNode<T> *ptr = locate(i); // 定位元素
    if (ptr != NULL)              // 为非空结点
    {
        ptr->data = x;
    }
    else
    {
        return;
    }
};

// 在指定位后插入元素
template <class T>
bool List<T>::insert(int i, const T &x)
{
    if (i < 0) // 无效下标
    {
        return false;
    }
    LinkNode<T> *ptr = locate(i);
    if (ptr == NULL) // 为空结点
    {
        return false;
    }
    LinkNode<T> *newNode = new LinkNode<T>(x);
    if (newNode == NULL)
    {
        cerr << "内存分配失败" << endl;
        exit(1);
    }
    else
    {
        newNode->link = ptr->link; // 新节点的下一个结点为原结点的下一个结点
        ptr->link = newNode;       //原结点的下一个结点为新结点
    }
    return true;
};

// 删除指定位元素
template <class T>
bool List<T>::remove(int i, T &x)
{
    if (i < 0) // 无效下标
    {
        return false;
    }
    LinkNode<T> *current = locate(i - 1); // 定位需删除元素前一元素，注意由于下标与实际存储位置相差1
    // 故定位i而非i-1
    if (current == NULL || current->link == NULL) // 删除元素为头节点或尾结点
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
        for (int j = 1; j <= length() - i; j++) // 注意下标起始
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

// 输出
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

// 输入
template <class T>
void List<T>::input()
{
    int n;
    T x;
    cout << "开始创建单链表，请输入要插入的元素数并依次输入元素：" << endl;
    cin >> n;
    LinkNode<T> *current = first; // 当前结点指向头节点
    while (n--)
    {
        cin >> x;
        current->link = new LinkNode<T>(x); // 构建链表
        current = current->link;
    }
    current->link = NULL;
}
