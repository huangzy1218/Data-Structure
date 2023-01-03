/**
 * @file skiplist.h
 * @author Huang Z.Y.
 * @brief ����(skip list)�� key-value ����ʽ�洢���Ա����ƽ�������(AVL Tree)����һ�ֲ���/ɾ��/������ΪO(logn)�����ݽṹ��
 * �����߼�Ϊ�����༶����(����)
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <iostream>
#include <random>
#include <time.h>
#include <vector>
using namespace std;
template <class T>
class SkipNode {
public:
    int key;
    T value;
    vector<SkipNode*> next;
    SkipNode(int key, T value, int level);
};

template <class T>
SkipNode<T>::SkipNode(int key, T value, int level)
    : key(key)
    , value(value)
{
    for (int i = 0; i < level; i++) {
        next.push_back(nullptr);
    }
};

template <class T>
class SkipList {
public:
    SkipNode<T>* head; // ͷ���
    int maxLevel; // �б�������
    static const int MIN_INT = numeric_limits<int>::min();
    static const int MAX_INT = numeric_limits<int>::max();
    SkipList(int maxLevel, T intivalue); // ���캯��
    ~SkipList() // ��������
    {
        delete head;
        delete tail;
    }
    int randomLevel(); // �����������
    SkipNode<T>* insert(int key, T value); // ����
    SkipNode<T>* find(int key); // ����
    SkipNode<T>* remove(int key);
    void output(); // �������
    int size() const { return head->next.size(); }

private:
    SkipNode<T>* tail;
    int nodeLevel(vector<SkipNode<T>*> p); // �ҵ���ǰ������� node ��������
};

template <class T>
SkipList<T>::SkipList(int maxLevel, T initValue)
    : maxLevel(maxLevel)
{
    head = new SkipNode<T>(MIN_INT, initValue, maxLevel);
    tail = new SkipNode<T>(MAX_INT, initValue, maxLevel);
    for (int i = 0; i < maxLevel; i++) { // ���в���ϵ�ͷ���ָ��β�ڵ�
        head->next[i] = tail;
    }
};

// �½�����������㷨
template <class T>
int SkipList<T>::randomLevel()
{
    int randLevel = 1;
    int seed = time(NULL);
    static default_random_engine e(seed);
    static uniform_int_distribution<int> u(0, 1);
    while (u(e) && randLevel < maxLevel) {
        randLevel++;
    }
    return randLevel;
};

// ����ĳ���ڵ���
template <class T>
int SkipList<T>::nodeLevel(vector<SkipNode<T>*> next)
{
    return next.size();
};

// ����
template <class T>
SkipNode<T>* SkipList<T>::find(int key)
{
    SkipNode<T>* current = head;
    int currLevel = nodeLevel(current->next);

    for (int i = (currLevel - 1); i >= 0; i--) { // ������
        while (current->next[i] != nullptr && current->next[i]->key < key) {
            current = current->next[i]; // ������
        }
    }
    current = current->next[0]; // ��������һ��
    if (current->key == key) {
        cout << "�� " << key << " ���ҳɹ�" << endl;
        return current;
    } else {
        cout << "�� " << key << "����ʧ��" << endl;
        return nullptr;
    }
};

// ����
template <class T>
SkipNode<T>* SkipList<T>::insert(int key, T value)
{
    int newLevel = randomLevel();
    SkipNode<T>* newNode = nullptr;
    SkipNode<T>* current = head;
    newNode = find(key);

    if (newNode) {
        newNode->value = value;
        cout << "�� " << key << " �Ѿ����ڣ�ֵ�ѱ�����Ϊ " << value << endl;
    }
    cout << "��Ϊ " << key << " ,�������Ϊ " << newLevel << endl;
    newNode = new SkipNode<T>(key, value, newLevel);
    for (int i = newLevel - 1; i >= 0; i--) {
        while (current->next[i] != nullptr && current->next[i]->key < key) {
            current = current->next[i];
        }
        // ��ʱ current Ϊ��i��С��key������Ľ�㣬������������Ӽ���
        newNode->next[i] = current->next[i];
        current->next[i] = newNode;
    }

    return head;
};

// ɾ��
template <class T>
SkipNode<T>* SkipList<T>::remove(int key)
{
    SkipNode<T>* target = find(key);
    if (!target) {
        cout << "�� " << key << " ������" << endl;
        return head;
    }
    SkipNode<T>* current = head;
    int level = target->next.size();
    cout << "��Ϊ " << key << " ,�������Ϊ " << level << endl;
    for (int i = level - 1; i >= 0; i--) {
        while (current->next[i] != nullptr && current->next[i]->key < key) {
            current = current->next[i];
        }
        current->next[i] = current->next[i]->next[i];
        cout << "�� " << key << " �ѴӲ�� " << i << " ɾ��" << endl;
    }
    return head;
};

// �������
template <class T>
void SkipList<T>::output()
{
    for (int i = maxLevel - 1; i >= 0; i--) {
        cout << "head"
             << "-->";
        SkipNode<T>* current = head->next[i];
        while (current != nullptr) {
            if (current != nullptr && current->key != SkipList<int>::MAX_INT) {
                cout << current->key << "-->";
            } else {
                cout << "tail";
                break;
            }
            current = current->next[i];
        }
        cout << endl;
    }
};
#endif