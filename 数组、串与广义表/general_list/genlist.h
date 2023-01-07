/**
 * @file genlist.h
 * @author Huang Z.Y.
 * @brief �����(General Lists)��һ�ַ������Ե����ݽṹ�������Ա��һ���ƹ㡣
 * ��������з��ɶԱ�Ԫ�ص�ԭ�����ƣ��������Ǿ���������ṹ�������㷺��Ӧ�����˹����ܵ�����ı�������LISP�����С�
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

// ��������ඨ��
template <class T>
struct GenListNode {
    int utype; // ��־��0 ��ʾԭ�ӽ�㣬1 �����ӱ���
    GenListNode<T>* tlink;
    union // ʹ��������Ч�����ڴ�
    {
        T value; // �������
        GenListNode<T>* hlink; // ����¸����ָ��
    }; // ��Ϣ��
};

template <class T>
class GenList {
public:
    GenList() // ���캯��
        : first(nullptr)
    {
    }
    void createGenList() { createGenList(first); } // ���������
    void createGenList(GenListNode<T>*& gNode); // ���������
    void traverse() // ���������
    {
        traverse(first);
        cout << ";" << endl;
    }
    void traverse(GenListNode<T>* gNode); // ���������
    GenList<T> copy(); // ����
    void copy(GenListNode<T>*& dest, GenListNode<T>* src); // ����
    bool find(T value); // ����
    bool find(GenListNode<T>* gNode, T value, int& tag);
    void output(); // ���
    void outputLevels(GenListNode<T>* gnode, int level); // ������

private:
    GenListNode<T>* first;
};

// ���������
template <class T>
void GenList<T>::createGenList(GenListNode<T>*& gNode)
{
    char ch;
    cin >> ch;
    if (ch == '#') {
        gNode = nullptr;
    } else if (ch == '(') { // �ӱ�
        gNode = new GenListNode<T>();
        gNode->utype = 1;
        createGenList(gNode->hlink);
    } else { // ��ͨ���
        gNode = new GenListNode<T>();
        gNode->utype = 0;
        gNode->value = ch;
    }
    cin >> ch; // �ݹ�������ܽ��к����Ķ���
    if (gNode == nullptr)
        ;
    else if (ch == ',') {
        createGenList(gNode->tlink);
    } else if ((ch == ')') || (ch == ';')) {
        gNode->tlink = nullptr;
    }
};

// ����ʽ��������
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

// ����
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

// ����
template <class T>
GenList<T> GenList<T>::copy()
{
    GenList<T> ret;
    copy(ret.first, first);
    return ret;
};

// ����
template <class T>
bool GenList<T>::find(T value)
{
    int tag = 0;
    return find(first, value, tag);
};

// ����
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

// ���
template <class T>
void GenList<T>::output()
{
    outputLevels(first, 1);
};

// ������
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