/**
 * @file hashtable.h
 * @author Huang Z.Y.
 * @brief 散列表又名哈希表(Hash table)，是根据关键码值(Key value)而直接进行访问的数据结构。
 * 通过将关键码值映射到表中一个位置来访问记录，以加快查找的速度。本代码为闭散列–线性探测。
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
    HashTable(int sz = defaultSize) // 构造函数
        : hTable(sz)
        , availableSize(0)
        , hasher()
    {
    }
    bool put(K key, V value); // 插入
    HashNode<K, V>* find(const K& key); // 查找
    bool remove(const K& key); // 删除
    void update(HashTable<K, V>& ht); // 更新当前哈希表
    V& operator[](const K& index); // 方括号重载
    void output(); // 输出

private:
    std::vector<HashNode<K, V>>
        hTable;
    int availableSize;
    const float loadFactor = 0.75f;
    void resize(); // 闭散列增容
    const std::hash<K> hasher; // 将数据转换为一个标志
    size_t hash(K key); // 哈希函数
};

// 哈希函数
template <class K, class V>
size_t HashTable<K, V>::hash(K key)
{
    size_t h = hasher(key);
    return h % hTable.size();
};

// 插入
template <class K, class V>
bool HashTable<K, V>::put(K key, V value)
{
    resize(); // 检查当前容量
    size_t index = hash(key);
    // 判断 key 是否存在
    while (hTable[index].state != EMPTY) {
        // 如果当前位置数据有效，并且 key 相同，插入失败
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

// 闭散列增容
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

// 查找
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

// 删除
template <class K, class V>
bool HashTable<K, V>::remove(const K& key)
{
    HashNode<K, V>* node = find(key);
    if (node) { // 假删除
        --availableSize;
        node->state = DELETE;
        return true;
    }
    return false;
};

// [] 重载
template <class K, class V>
V& HashTable<K, V>::operator[](const K& key)
{
    HashNode<K, V>* target = find(key);
    return target->value;
};

// 输出
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