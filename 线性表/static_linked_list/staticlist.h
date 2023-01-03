/**
 * @file staticlist.cpp
 * @author Huang Z.Y.
 * @brief 静态链表(static linked list)是一种更为简单的链表结构，其使用一维数组来进行描述。
 * 这种描述方法便于在没有指针类型的高级程序设计语言中使用链表结构。
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef STATICLIST_H
#define STATICLIST_H
#include <iostream>
using namespace std;
const int maxSize = 100; // 静态链表的大小
template <class T>
struct SLinkNode {
    T data; // 结点数据
    int link; // 结点链接指针
};

template <class T>
class StaticList {
    SLinkNode<T>* elem;
    int avil; // 当前可分配空间的首地址
public:
    StaticList()
    {
        elem = new SLinkNode<T>[maxSize]();
        initList();
    }
    void initList(); // 初始化链表
    int length() const; // 计算静态链表的长度
    int search(T x); // 查找具体结点
    int locate(int i); // 查找第i个结点
    bool append(T x); // 在表尾追加一个结点
    bool insert(int i, T x); // 在第i个结点后插入新结点
    bool remove(int i); // 在静态链表删除第i个结点
    bool isEmpty(); // 判空
    void output(); // 输出
};

// 初始化链表
template <class T>
void StaticList<T>::initList()
{
    elem[0].link = -1; // 设置头结点
    avil = 1; // 结点首地址从1开始
    for (int i = 1; i < maxSize - 1; i++) {
        elem[i].link = i + 1; // 构成空闲链表，下标+1为链接指针地址
    }
    elem[maxSize - 1].link = -1; // 链表收尾
}

// 计算静态链表的长度
template <class T>
int StaticList<T>::length() const
{
    int p = elem[0].link; // 指向头结点
    int count = 0;
    while (p != -1) { // 链表不为空或不为表尾
        p = elem[p].link;
        count++;
    }
    return count;
}

// 判空
template <class T>
bool StaticList<T>::isEmpty()
{
    return elem[0].link == -1;
}

// 查找具体结点
template <class T>
int StaticList<T>::search(T x)
{
    int p = elem[0].link;
    while (p != -1) {
        if (elem[p].data == x) {
            break;
        } else {
            p = elem[p].link; // 指向下个结点
        }
    }
    return p;
}

// 定位第 i 个元素
template <class T>
int StaticList<T>::locate(int i)
{
    if (i < 0) {
        return -1;
    }
    if (i == 0) {
        return 0;
    }
    int j = 1, p = elem[0].link;
    while (p != -1 && j < i) {
        p = elem[p].link; // 由于可能存在非表尾插入，故下标 +1 不一应为下个元素的地址
        j++;
    }
    return p;
}

// 在表尾追加一个结点
template <class T>
bool StaticList<T>::append(T x)
{
    if (avil == -1) {
        return false;
    }
    int q = avil; // 指向当前元素的地址 1 = elem[1].link = 2（下一个分配的地址）
    avil = elem[avil].link; // 更新当前空间的首地址
    elem[q].data = x; // elem[1].data = x
    elem[q].link = -1; // 当前为表尾
    int p = 0;
    while (elem[p].link != -1) { // 找到原先表尾
        p = elem[p].link;
    }
    elem[p].link = q; // 链入

    return true;
}

// 在第 i 个结点后插入新结点
template <class T>
bool StaticList<T>::insert(int i, T x)
{
    int p = locate(i);
    if (p == -1) {
        return false;
    }
    int q = avil; // 可分配的首结点
    avil = elem[avil].link; // 此时地址不连续
    elem[q].data = x;
    elem[q].link = elem[p].link; // 链入
    elem[p].link = q; // i 的下个结点为插入的新节点
    return true;
};

template <class T>
bool StaticList<T>::remove(int i)
{
    int p = locate(i - 1);
    if (p == -1) {
        return false;
    }
    int q = elem[p].link;
    elem[p].link = elem[q].link;
    elem[q].link = avil;
    avil = q;
    return true;
};

// 输出
template <class T>
void StaticList<T>::output()
{
    int p = elem[0].link;

    while (p != -1) {
        cout << elem[p].data << " ";
        p = elem[p].link;
    }
    cout << endl;
};

#endif