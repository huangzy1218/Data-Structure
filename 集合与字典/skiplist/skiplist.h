/**
 * @file skiplist.h
 * @author Huang Z.Y.
 * @brief 跳表(skip list)是 key-value 的形式存储，对标的是平衡二叉树(AVL Tree)，是一种插入/删除/搜索均为O(logn)的数据结构，
 * 基本逻辑为建立多级链表(索引)
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
    SkipNode<T>* head; // 头结点
    int maxLevel; // 列表最大层数
    static const int MIN_INT = numeric_limits<int>::min();
    static const int MAX_INT = numeric_limits<int>::max();
    SkipList(int maxLevel, T intivalue); // 构造函数
    ~SkipList() // 析构函数
    {
        delete head;
        delete tail;
    }
    int randomLevel(); // 随机层数方法
    SkipNode<T>* insert(int key, T value); // 插入
    SkipNode<T>* find(int key); // 查找
    SkipNode<T>* remove(int key);
    void output(); // 层序输出
    int size() const { return head->next.size(); }

private:
    SkipNode<T>* tail;
    int nodeLevel(vector<SkipNode<T>*> p); // 找到当前跳表或者 node 的最大层数
};

template <class T>
SkipList<T>::SkipList(int maxLevel, T initValue)
    : maxLevel(maxLevel)
{
    head = new SkipNode<T>(MIN_INT, initValue, maxLevel);
    tail = new SkipNode<T>(MAX_INT, initValue, maxLevel);
    for (int i = 0; i < maxLevel; i++) { // 所有层次上的头结点指向尾节点
        head->next[i] = tail;
    }
};

// 新结点的随机层数算法
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

// 计算某个节点层次
template <class T>
int SkipList<T>::nodeLevel(vector<SkipNode<T>*> next)
{
    return next.size();
};

// 查找
template <class T>
SkipNode<T>* SkipList<T>::find(int key)
{
    SkipNode<T>* current = head;
    int currLevel = nodeLevel(current->next);

    for (int i = (currLevel - 1); i >= 0; i--) { // 往下走
        while (current->next[i] != nullptr && current->next[i]->key < key) {
            current = current->next[i]; // 向右走
        }
    }
    current = current->next[0]; // 再向右走一步
    if (current->key == key) {
        cout << "键 " << key << " 查找成功" << endl;
        return current;
    } else {
        cout << "键 " << key << "查找失败" << endl;
        return nullptr;
    }
};

// 插入
template <class T>
SkipNode<T>* SkipList<T>::insert(int key, T value)
{
    int newLevel = randomLevel();
    SkipNode<T>* newNode = nullptr;
    SkipNode<T>* current = head;
    newNode = find(key);

    if (newNode) {
        newNode->value = value;
        cout << "键 " << key << " 已经存在，值已被更新为 " << value << endl;
    }
    cout << "键为 " << key << " ,随机层数为 " << newLevel << endl;
    newNode = new SkipNode<T>(key, value, newLevel);
    for (int i = newLevel - 1; i >= 0; i--) {
        while (current->next[i] != nullptr && current->next[i]->key < key) {
            current = current->next[i];
        }
        // 此时 current 为第i层小于key的最近的结点，接下来完成连接即可
        newNode->next[i] = current->next[i];
        current->next[i] = newNode;
    }

    return head;
};

// 删除
template <class T>
SkipNode<T>* SkipList<T>::remove(int key)
{
    SkipNode<T>* target = find(key);
    if (!target) {
        cout << "键 " << key << " 不存在" << endl;
        return head;
    }
    SkipNode<T>* current = head;
    int level = target->next.size();
    cout << "键为 " << key << " ,随机层数为 " << level << endl;
    for (int i = level - 1; i >= 0; i--) {
        while (current->next[i] != nullptr && current->next[i]->key < key) {
            current = current->next[i];
        }
        current->next[i] = current->next[i]->next[i];
        cout << "键 " << key << " 已从层次 " << i << " 删除" << endl;
    }
    return head;
};

// 层序输出
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