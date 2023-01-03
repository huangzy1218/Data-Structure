/**
 * @file staticlist.cpp
 * @author Huang Z.Y.
 * @brief ��̬����(static linked list)��һ�ָ�Ϊ�򵥵�����ṹ����ʹ��һά����������������
 * ������������������û��ָ�����͵ĸ߼��������������ʹ������ṹ��
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
const int maxSize = 100; // ��̬����Ĵ�С
template <class T>
struct SLinkNode {
    T data; // �������
    int link; // �������ָ��
};

template <class T>
class StaticList {
    SLinkNode<T>* elem;
    int avil; // ��ǰ�ɷ���ռ���׵�ַ
public:
    StaticList()
    {
        elem = new SLinkNode<T>[maxSize]();
        initList();
    }
    void initList(); // ��ʼ������
    int length() const; // ���㾲̬����ĳ���
    int search(T x); // ���Ҿ�����
    int locate(int i); // ���ҵ�i�����
    bool append(T x); // �ڱ�β׷��һ�����
    bool insert(int i, T x); // �ڵ�i����������½��
    bool remove(int i); // �ھ�̬����ɾ����i�����
    bool isEmpty(); // �п�
    void output(); // ���
};

// ��ʼ������
template <class T>
void StaticList<T>::initList()
{
    elem[0].link = -1; // ����ͷ���
    avil = 1; // ����׵�ַ��1��ʼ
    for (int i = 1; i < maxSize - 1; i++) {
        elem[i].link = i + 1; // ���ɿ��������±�+1Ϊ����ָ���ַ
    }
    elem[maxSize - 1].link = -1; // ������β
}

// ���㾲̬����ĳ���
template <class T>
int StaticList<T>::length() const
{
    int p = elem[0].link; // ָ��ͷ���
    int count = 0;
    while (p != -1) { // ����Ϊ�ջ�Ϊ��β
        p = elem[p].link;
        count++;
    }
    return count;
}

// �п�
template <class T>
bool StaticList<T>::isEmpty()
{
    return elem[0].link == -1;
}

// ���Ҿ�����
template <class T>
int StaticList<T>::search(T x)
{
    int p = elem[0].link;
    while (p != -1) {
        if (elem[p].data == x) {
            break;
        } else {
            p = elem[p].link; // ָ���¸����
        }
    }
    return p;
}

// ��λ�� i ��Ԫ��
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
        p = elem[p].link; // ���ڿ��ܴ��ڷǱ�β���룬���±� +1 ��һӦΪ�¸�Ԫ�صĵ�ַ
        j++;
    }
    return p;
}

// �ڱ�β׷��һ�����
template <class T>
bool StaticList<T>::append(T x)
{
    if (avil == -1) {
        return false;
    }
    int q = avil; // ָ��ǰԪ�صĵ�ַ 1 = elem[1].link = 2����һ������ĵ�ַ��
    avil = elem[avil].link; // ���µ�ǰ�ռ���׵�ַ
    elem[q].data = x; // elem[1].data = x
    elem[q].link = -1; // ��ǰΪ��β
    int p = 0;
    while (elem[p].link != -1) { // �ҵ�ԭ�ȱ�β
        p = elem[p].link;
    }
    elem[p].link = q; // ����

    return true;
}

// �ڵ� i ����������½��
template <class T>
bool StaticList<T>::insert(int i, T x)
{
    int p = locate(i);
    if (p == -1) {
        return false;
    }
    int q = avil; // �ɷ�����׽��
    avil = elem[avil].link; // ��ʱ��ַ������
    elem[q].data = x;
    elem[q].link = elem[p].link; // ����
    elem[p].link = q; // i ���¸����Ϊ������½ڵ�
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

// ���
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