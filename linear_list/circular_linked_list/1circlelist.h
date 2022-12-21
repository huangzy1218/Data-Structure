#include <iostream>
#include <cstdlib>
#include "../linearlist.h"
using namespace std;
template <class T>
struct CircLinkNode
{
    T data;
    CircLinkNode<T> *link;
    CircLinkNode(CircLinkNode<T> *ptr = NULL) { link = ptr; }
    CircLinkNode(const T &item, CircCircLinkNode *ptr = NULL)
    {
        data = item;
        link = ptr;
    }
};

template <class T>
class CircList : public LinearCircList<T>
{
    CircList()                                           // 构造函�?
        CircList(const T &x)                             // 构造函�?
        CircList(CircList<T> &L);                        // 复制构造函�?
    ~CircList() { makeEmpty(); }                         // 析构函数
    void MakeEmpty();                                    // 将链表置�?
    int Length() const;                                  // 计算链表长度
    CircLinkNode<T> *GetHead() const { return first; }   // 返回头结点地址
    CircLinkNode<T> *Search(T x);                        // 搜索含x的元素的地址
    CircLinkNode<T> *Locate(int i);                      // 定位第i个元�?
    bool GetData(int i, T &x) const;                     // 取出第i个元素�?
    void SetData(int i, T &x);                           // 将第i个元素值设为x
    bool Insert(int i, T &x);                            // 在第i个元素后插入x
    bool Remove(int i, T &x);                            // 删除第i个元素，并返回其值x
    bool IsEmpty() const { return first->link == NULL; } // 判表�?
    bool IsFull() const { return false; }                // 判表�?
    void Sort();                                         // 排序
    void Input();                                        // 输入
    void Output();                                       // 输出
    CircList<T> &operator=(CircList<T> &L);              // 重载函数：赋�?
protected:
    CircLinkNode<T> *first; // 头结�?
    CircLinkNode<T> *last;  // 尾结点，不必�?
};

// 构造函�?
template <class T>
CircList<T>::CircList()
{
    first = new CircLinkNode<T>();
    first->link = first;
}

// 构造函�?
template <class T>
CircList<T>::CircList(const T &x)
{
    first = new CircLinkNode<T>(x);
    first->link = first;
}

// 复制构造函�?
template <class T>
CircList<T>::CircList(CircList<T> &L)
{
    T value;
    CircLinkNode<T> *srcptr = L.GetHead();      // 指向源链�?
    CircLinkNode<T> *destptr = this->GetHead(); // 指向当前链表

    while (srcptr->link != last)
    { // 依次复制
        value = srcptr->link->data;
        destptr->link = new CircLinkNode<T>(data);
        srcptr = srcptr->link;
        destptr = destptr->link;
    }
    ,
        destptr->link = first; // 标志链表�?
}
// 将链表置�?
template <class T>
void CircList<T>::MakeEmpty()
{
    CircLinkNode<T> *q; // 记录删除结点
    while (first->link != first)
    {
        q = first->next;
        first->link = q->link; // 头结点的下个结点指向删除结点的下一个，若为NULL类似
        delete q;
    }
}

// 计算链表长度
template <class T>
int CircList<T>::Length() const
{
    int count = 0; // 计算表长
    CircLinkNode<T> *count = first->link;

    while (ptr != first)
    {
        ++count;
    }
    return count;
}

// 搜索含x的元素的地址
template <class T>
CircLinkNode<T> *Search(T x)
{
    CircLinkNode<T> *ptr = first->link;

    while (ptr != first)
    {
        if (ptr->data == x)
        {
            break;
        }
        else
        {
            ptr = ptr->link;
        }
    }
    return ptr; // 单一出口原则
}

// 定位第i个元�?
template <class T>
CircLinkNode<T> *CircList<T>::Locate(int i)
{
    if (i < 0)
    { // 下标不合�?
        return NULL;
    }
    int count = 0; // 记录当前元素下标
    CircLinkNode<T> *ptr = first->link;
    while (ptr != first && count < i)
    { // 注意逻辑顺序
        ptr = ptr->link;
        ++count;
    }
    return ptr;
}
// 取出第i个元素�?
template <class T>
bool CircList<T>::GetData(int i, T &x) const
{
    if (i < 0)
    {
        return false;
    }
    CircLinkNode *ptr = Locate(i); // 借助已有函数实现定位
    if (ptr != first)
    {
        x = ptr->data;
        return true;
    }
    else
    {
        return false;
    }
}

// 将第i个元素值设为x
template <class T>
void CircList<T>::SetData(int i, T &x)
{
    if (i < 0)
    {
        return;
    }
    CircLinkNode *ptr = Locate(i); // 借助已有函数实现定位
    if (ptr != first)
    {
        ptr->data = x;
    }
    else
    {
        return;
    }
}

// 在第i个元素后插入x
template <class T>
bool CircList<T>::Insert(int i, T &x)
{
    if (i < 0)
    {
        return false;
    }
    CircLinkNode<T> *ptr = Locate(i);
    if (ptr == first)
    { // 位于表尾之后，无法插�?
        return false;
    }
    CircLinkNode<T> *newNode = new CircLinkNode(x);
    if (newNode == NULL)
    {
        cerr << "内存分配失败" << endl;
        exit(1);
    }
    else
    {
        newNode->link = ptr->link;
        ptr->link = newNode;
    }
    return true;
}

// 删除第i个元素，并返回其值x
template <class T>
bool CircList<T>::Remove(int i, T &x)
{
    if (i < 0)
    {
        return false;
    }
    CircLinkNode<T> *current = Locate(i - 1); // 删除元素的前一个结�?
    if (current == first || current->link == first)
    { // 位于表尾之后，无法删�?
        return false;
    }
    else
    {
        CircLinkNode<T> *delPtr = current->link;
        current->link = delPtr->link;
        x = delPtr->data;
        delete delPtr;
        return true;
    }
}

// 输出
template <class T>
void CircList<T>::Output()
{
    CircLinkNode<T> *current = first->link;

    while (current != first)
    { // 格式化输�?
        cout << current->data << " ";
        current = current->link;
    }
    cout << endl;
}

// 输入
template <class T>
void CircList<T>::Input()
{
    int n;
    T x;
    cout << "开始建立循环链表，请输入表中元素个�?" << endl;
    cin >> n;
    CircLinkNode<T> *current = head; //  不断创建新结点保存输入数�?
    while (n--)
    {
        cin >> x;
        current->link = new CircLinkNode<T>(x);
        current = current->link;
    }
    current->link = first;
}