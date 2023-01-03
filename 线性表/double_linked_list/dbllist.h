/**
 * @file dbllist.h
 * @author Huang Z.Y.
 * @brief 双向链表(double linked list)的每个数据结点中都有两个指针，分别指向直接后继和直接前驱。
 * 可从双向链表中的任意一个结点开始，访问它的前驱结点和后继结点。
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
    DblNode<T>*pre, *next; // 前驱（左链），后继（右链）指针
    DblNode(DblNode<T>* left = nullptr, DblNode<T>* right = NULL)
        : pre(left)
        , next(right)
    {
    } // 构造函数
    DblNode(T value = -1, DblNode<T>* left = nullptr, DblNode<T>* right = nullptr)
        : data(value)
        , pre(left)
        , next(right)
    {
    } // 构造函数
    DblNode<T>& operator=(DblNode<T>& rhs); // = 重载
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
    DblList() { first = new DblNode<T>(); } // 构造函数，含头结点
    DblList(const T& x) { first = new DblNode<T>(x); } // 构造函数
    DblList(DblList<T>& L); // 拷贝构造函数
    ~DblList() { makeEmpty(); } // 析构函数
    void makeEmpty(); // 置空
    int length() const; // 获取长度
    int size() const; // 获取大小
    DblNode<T>* getHead() const { return first; } // 获取头结点
    DblNode<T>* search(T& x) const; // 查找
    DblNode<T>* locate(int i) const; // 定位
    T& getPreData(int i); // 获取前驱元素值
    T& getNextData(int i); // 获取后继元素值
    bool getData(int i, T& x) const; // 获取指定位元素值
    void setData(int i, const T& x); // 设置指定位元素值
    bool insert(int i, const T& x); // 在指定位后插入元素
    bool remove(int i, T& x); // 删除指定位元素
    bool isEmpty() const { return first->next == first; } // 判空
    bool isFull() const { return false; } // 判满
    void sort(); // 排序
    void input(); // 输入
    void output(); // 输出
    DblList<T>& operator=(DblList<T>& L); // 赋值运算符重载
protected:
    DblNode<T>* first;
};

// 拷贝构造
template <class T>
DblList<T>::DblList(DblList<T>& L)
{
    T value;
    DblNode<T>* srcptr = L.getHead(); // 获取 L 的头结点
    DblNode<T>* destptr = this->getHead(); // 获取头结点

    while (srcptr->next != nullptr) { // 未达到 L 尾部
        value = srcptr->next->data;
        destptr->next = new DblNode<T>(value);
        destptr->next->pre = destptr;
        srcptr = srcptr->next;
        destptr = destptr->next;
    }
    destptr->next = first; // 尾结点以nullptr结束
};

// 置空
template <class T>
void DblList<T>::makeEmpty()
{
    DblNode<T>* tempt; // 临时结点，用于依次删除
    while (first->next != first) // 头节点后无结点
    {
        tempt = first->next;
        first->next = tempt->next; // 头节点的下一个指向删除结点的下一个结点
        delete tempt; // 删除该结点
    }
};

// 获取长度
template <class T>
int DblList<T>::length() const
{
    int count = 0;
    DblNode<T>* current = first->next;

    while (current != first) // 当前结点非空
    {
        ++count;
        current = current->next;
    }
    return count;
};

// 获取大小
template <class T>
int DblList<T>::size() const
{
    return length();
};

// 查找
template <class T>
DblNode<T>* DblList<T>::search(T& x) const
{
    DblNode<T>* ptr = first->next;

    while (ptr != nullptr) {
        if (ptr->data == x) {
            break;
        } else {
            ptr = ptr->next; // 继续遍历
        }
    }
    return ptr; // 返回查找结点
};

// 定位
template <class T>
DblNode<T>* DblList<T>::locate(int i) const
{
    if (i < 0) { // 无效下标
        return nullptr;
    }
    int count = 0; // 用于计数，元素下标从0开始
    DblNode<T>* ptr = first;
    while (ptr->next != first && count < i) {
        ptr = ptr->next;
        ++count;
    }
    return ptr;
};

// 获取指定位元素值
template <class T>
bool DblList<T>::getData(int i, T& x) const
{
    if (i < 0) { // 无效下标
        return false;
    }
    DblNode<T>* ptr = locate(i); // 定位元素
    if (ptr != nullptr) // 为非空结点
    {
        x = ptr->data;
        return true;
    } else {
        return false;
    }
};

// 获取前驱元素值
template <class T>
T& DblList<T>::getPreData(int i)
{
    DblNode<T>* current = locate(i);
    return current->pre->data;
};

// 获取后继元素值
template <class T>
T& DblList<T>::getNextData(int i)
{
    DblNode<T>* current = locate(i);
    return current->next->data;
};

// 设置指定位元素值
template <class T>
void DblList<T>::setData(int i, const T& x)
{
    if (i < 0) { // 无效下标
        return;
    }
    DblNode<T>* ptr = locate(i); // 定位元素
    if (ptr != first) // 为非空结点
    {
        ptr->data = x;
    } else {
        return;
    }
};

// 在指定位后插入元素
template <class T>
bool DblList<T>::insert(int i, const T& x)
{
    if (i < 0) { // 无效下标
        return false;
    }
    DblNode<T>* ptr = locate(i);
    if (ptr == first) { // 为空结点
        return false;
    }
    DblNode<T>* newNode = new DblNode<T>(x);
    if (newNode == nullptr) {
        cerr << "内存分配失败" << endl;
        exit(1);
    } else {
        newNode->next = ptr->next; // 新节点的下一个结点为原结点的下一个结点
        ptr->next->pre = newNode;
        ptr->next = newNode;
        newNode->pre = ptr;
    }
    return true;
};

// 删除指定位元素
template <class T>
bool DblList<T>::remove(int i, T& x)
{
    if (i < 0) { // 无效下标
        return false;
    }
    DblNode<T>* current = locate(i - 1); // 定位需删除元素前一元素，注意由于下标与实际存储位置相差1
    // 故定位i而非i-1
    if (current == nullptr || current->next == nullptr) // 删除元素为头节点或尾结点
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
        for (int j = 1; j <= length() - i; j++) // 注意下标起始
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

// 输出
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

// 输入
template <class T>
void DblList<T>::input()
{
    int n;
    T x;
    cout << "开始创建双向链表，输入插入的元素数并依次输入元素：" << endl;
    cin >> n;
    DblNode<T>* current = first; // 当前结点指向头节点
    while (n--) {
        cin >> x;
        current->next = new DblNode<T>(x); // 构建链表
        current->next->pre = current;
        current = current->next;
    }
    current->next = first;
}

#endif