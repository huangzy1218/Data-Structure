/**
 * @file genlist.h
 * @author Huang Z.Y.
 * @brief 广义表(General Lists)是一种非连续性的数据结构，是线性表的一种推广。
 * 即广义表中放松对表元素的原子限制，容许它们具有其自身结构。它被广泛的应用于人工智能等领域的表处理语言LISP语言中。
 * @version 0.1
 * @date 2023-01-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef GENLIST_H
#define GENLIST_H
#include <cassert>
#include <cstdlib>
#include <iostream>
using namespace std;

// 广义表结点类定义
template <class T>
struct GenListNode {
    int utype; // 标志域：0 表示原子结点，1 代表子表结点
    GenListNode<T>* tlink;
    union // 使用联合有效减少内存
    {
        T value; // 存放数据
        GenListNode<T>* hlink; // 存放下个结点指针
    }; // 信息域
};

template <class T>
class GenList {
public:
    GenList() // 构造函数
        : first(nullptr)
    {
    }
    void createGenList() { createGenList(first); } // 创建广义表
    void createGenList(GenListNode<T>*& gNode); // 创建广义表
    void traverse() // 遍历广义表
    {
        traverse(first);
        cout << ";" << endl;
    }
    void traverse(GenListNode<T>* gNode); // 遍历广义表
    GenList<T> copy(); // 拷贝
    void copy(GenListNode<T>*& dest, GenListNode<T>* src); // 拷贝
    bool find(T value); // 查找
    bool find(GenListNode<T>* gNode, T value, int& tag);
    void output(); // 输出
    void outputLevels(GenListNode<T>* gnode, int level); // 层次输出

private:
    GenListNode<T>* first;
};

// 建立广义表
template <class T>
void GenList<T>::createGenList(GenListNode<T>*& gNode)
{
    char ch;
    cin >> ch;
    if (ch == '#') {
        gNode = nullptr;
    } else if (ch == '(') { // 子表
        gNode = new GenListNode<T>();
        gNode->utype = 1;
        createGenList(gNode->hlink);
    } else { // 普通结点
        gNode = new GenListNode<T>();
        gNode->utype = 0;
        gNode->value = ch;
    }
    cin >> ch; // 递归回来后能进行后续的读入
    if (gNode == nullptr)
        ;
    else if (ch == ',') {
        createGenList(gNode->tlink);
    } else if ((ch == ')') || (ch == ';')) {
        gNode->tlink = nullptr;
    }
};

// 按格式输出广义表
template <class T>
void GenList<T>::traverse(GenListNode<T>* gNode)
{
    if (gNode->utype == 1) {
        cout << "(";
        if (gNode->hlink == nullptr) {
            cout << "#";
        } else {
            traverse(gNode->hlink);
        }
        cout << ")";
    } else {
        cout << gNode->value;
    }
    if (gNode->tlink != nullptr) {
        cout << ",";
        traverse(gNode->tlink);
    }
};

// 复制
template <class T>
void GenList<T>::copy(GenListNode<T>*& dest, GenListNode<T>* src)
{
    if (src->utype == 1) {
        dest = new GenListNode<T>();
        dest->utype = 1;
        if (src->hlink == nullptr) {
            dest->hlink = nullptr;
        } else {
            copy(dest->hlink, src->hlink);
        }
    } else {
        dest = new GenListNode<T>();
        dest->utype = 0;
        dest->value = src->value;
    }
    if (src->tlink == nullptr) {
        dest->tlink = nullptr;
    } else {
        copy(dest->tlink, src->tlink);
    }
};

// 拷贝
template <class T>
GenList<T> GenList<T>::copy()
{
    GenList<T> ret;
    copy(ret.first, first);
    return ret;
};

// 查找
template <class T>
bool GenList<T>::find(T value)
{
    int tag = 0;
    return find(first, value, tag);
};

// 查找
template <class T>
bool GenList<T>::find(GenListNode<T>* gNode, T value, int& tag)
{
    if (gNode->utype == 1) {
        if (gNode->hlink != nullptr) {
            find(gNode->hlink, value, tag);
        }
    } else {
        if (gNode->value == value) {
            tag = 1;
        }
    }
    if (gNode->tlink != nullptr) {
        find(gNode->tlink, value, tag);
    }
    return tag == 1;
};

// 输出
template <class T>
void GenList<T>::output()
{
    outputLevels(first, 1);
};

// 输出层次
template <class T>
void GenList<T>::outputLevels(GenListNode<T>* gNode, int level)
{
    if (gNode->utype == 1) {
        if (gNode->hlink != nullptr) {
            outputLevels(gNode->hlink, level + 1);
        }
    } else {
        cout << gNode->value << " " << level << endl;
    }
    if (gNode->tlink != nullptr) {
        outputLevels(gNode->tlink, level);
    }
};

#endif