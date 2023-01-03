/**
 * @file hashtable.h
 * @author Huang Z.Y.
 * @brief ɢ�б�������ϣ��(Hash table)���Ǹ��ݹؼ���ֵ(Key value)��ֱ�ӽ��з��ʵ����ݽṹ��
 * ͨ�����ؼ���ֵӳ�䵽����һ��λ�������ʼ�¼���Լӿ���ҵ��ٶȡ�������Ϊ��ɢ�ШC����̽�⡣
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <vector>
#ifndef HASHTABLE_H
#define HASHTABLe_H
using std::cout;
using std::endl;
using std::string;
const int defaultSize = 10;
enum STATE {
    EXIST,
    DELETE,
    EMPTY,
};
template <class K, class V>
struct HashNode {
    K key;
    V value;
    STATE state = EMPTY;
};

template <class K, class V>
class HashTable {
public:
    typedef HashNode<K, V> Entry;
    HashTable(int sz = defaultSize) // ���캯��
        : hTable(sz)
        , availableSize(0)
        , hasher()
    {
    }
    bool put(K key, V value); // ����
    HashNode<K, V>* find(const K& key); // ����
    bool remove(const K& key); // ɾ��
    void update(HashTable<K, V>& ht); // ���µ�ǰ��ϣ��
    V& operator[](const K& index); // ����������
    void output(); // ���

private:
    std::vector<HashNode<K, V>>
        hTable;
    int availableSize;
    const float loadFactor = 0.75f;
    void resize(); // ��ɢ������
    const std::hash<K> hasher; // ������ת��Ϊһ����־
    size_t hash(K key); // ��ϣ����
};

// ��ϣ����
template <class K, class V>
size_t HashTable<K, V>::hash(K key)
{
    size_t h = hasher(key);
    return h % hTable.size();
};

// ����
template <class K, class V>
bool HashTable<K, V>::put(K key, V value)
{
    resize(); // ��鵱ǰ����
    size_t index = hash(key);
    // �ж� key �Ƿ����
    while (hTable[index].state != EMPTY) {
        // �����ǰλ��������Ч������ key ��ͬ������ʧ��
        if (hTable[index].state == EXIST && key == hTable[index].key) {
            return false;
        }
        ++index;
        if (index == hTable.size()) {
            index = 0;
        }
    }
    cout << index << ": " << key << endl;
    hTable[index].key = key;
    hTable[index].value = value;
    hTable[index].state = EXIST;
    ++availableSize;

    return true;
};

// ��ɢ������
template <class K, class V>
void HashTable<K, V>::resize()
{
    if (hTable.size() == 0 || availableSize / hTable.size() >= loadFactor) {
        int newCapacity = hTable.size() == 0 ? 10 : 2 * hTable.size();
        HashTable<K, V> newHTable(newCapacity);
        for (int i = 0; i < hTable.size(); i++) {
            if (hTable[i].state == EXIST) {
                newHTable.put(hTable[i].key, hTable[i].value);
            }
        }
        update(newHTable);
    }
};

template <class K, class V>
void HashTable<K, V>::update(HashTable<K, V>& ht)
{
    std::swap(hTable, ht.hTable);
    std::swap(availableSize, ht.availableSize);
};

// ����
template <class K, class V>
HashNode<K, V>* HashTable<K, V>::find(const K& key)
{
    int index = hash(key) % hTable.size();
    while (hTable[index].state != EMPTY) {
        if (hTable[index].state == EXIST && key == hTable[index].key) {
            return &hTable[index];
        }
        ++index;
        if (index == hTable.size()) {
            index = 0;
        }
    }
    return nullptr;
};

// ɾ��
template <class K, class V>
bool HashTable<K, V>::remove(const K& key)
{
    HashNode<K, V>* node = find(key);
    if (node) { // ��ɾ��
        --availableSize;
        node->state = DELETE;
        return true;
    }
    return false;
};

// [] ����
template <class K, class V>
V& HashTable<K, V>::operator[](const K& key)
{
    HashNode<K, V>* target = find(key);
    return target->value;
};

// ���
template <class K, class V>
void HashTable<K, V>::output()
{
    for (int i = 0; i < hTable.size(); i++) {
        std::cout << i << ": ";
        if (hTable[i].state == EXIST) {
            std::cout << "< " << hTable[i].key << ", "
                      << hTable[i].value << " >  " << std::endl;
        } else {
            std::cout << std::endl;
        }
    }
}

#endif