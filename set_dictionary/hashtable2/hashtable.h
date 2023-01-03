#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
template <class K, class V>
struct Entry {
    K key;
    V value;
    Entry<K, V>* next;
    Entry(Entry<K, V>* next)
        : next(next)
    {
    }
    Entry(K key, V value, Entry<K, V>* next = nullptr)
        : key(key)
        , value(value)
        , next(next)
    {
    }
};

template <class K, class V>
class HashTable {
public:
    HashTable() // ���캯��
        : capacity(defautCapacity)
        , hasher()
    {
        hTable = new Entry<K, V>*[defautCapacity];
    }
    ~HashTable() { makeEmpty(); } // ��������
    void makeEmpty(); // �ÿ�
    void put(K key, V value); // ����
    bool remove(K key); // ɾ��
    bool find(const K& key);
    V& get(const K& key);
    V& operator[](const K& key);
    void output();

private:
    const float loadFactor
        = 0.75f; // װ�����ӵ���ֵ
    const int defautCapacity = 10; // ��ʼ����С
    Entry<K, V>** hTable;
    int availableSize;
    int capacity = defautCapacity;
    int usedIndexs = 0;
    void resize(); // ��ɢ������
    size_t hash(K key); // ��ϣ����
    const std::hash<K> hasher;
};

// �ÿ�
template <class K, class V>
void HashTable<K, V>::makeEmpty()
{
    for (int i = 0; i < capacity; i++) {
        if (hTable[i] == nullptr || hTable[i]->next == nullptr) {
            delete hTable[i];
            continue;
        }
        Entry<K, V>* item = hTable[i]->next;
        while (item != nullptr) {
            Entry<K, V>* temp = item;
            item = item->next;
            delete temp;
        }
    }
    delete[] hTable;
};

// ��ϣ����
template <class K, class V>
size_t HashTable<K, V>::hash(K key)
{
    size_t h = hasher(key);
    return h % capacity;
};

// ��ɢ������
template <class K, class V>
void HashTable<K, V>::resize()
{
    Entry<K, V>** oldTable = hTable;
    int oldCapacity = capacity;
    usedIndexs = 0;
    capacity *= 2;
    hTable = new Entry<K, V>*[capacity]();

    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable[i] == nullptr || oldTable[i]->next == nullptr) {
            continue;
        }
        Entry<K, V>* e = oldTable[i];
        while (e->next != nullptr) {
            e = e->next;
            size_t index = hash(e->key);
            if (hTable[index] == nullptr) {
                hTable[index] = new Entry<K, V>(nullptr);
                ++usedIndexs;
            }
            hTable[index]->next = new Entry<K, V>(e->key, e->value, hTable[index]->next);
        }
    }
};

// ����
template <class K, class V>
void HashTable<K, V>::put(K key, V value)
{
    size_t index = hash(key);
    if (hTable[index] == nullptr) {
        hTable[index] = new Entry<K, V>(nullptr);
    }

    if (hTable[index]->next == nullptr) {
        hTable[index]->next = new Entry<K, V>(key, value);
        ++availableSize;
        ++usedIndexs;
        if (usedIndexs >= loadFactor * capacity) { // װ�����Ӵ�����ֵ������
            resize();
        }
    } else {
        Entry<K, V>* temp = hTable[index]->next;
        while (temp != nullptr) {
            if (temp->key == key) {
                temp->value = value; // ��� key��ͬ������ value
                return;
            }
            temp = temp->next;
        }
        // ��ɢ�г�ͻ
        temp = hTable[index]->next;
        hTable[index]->next = new Entry<K, V>(key, value, temp); // �ŵ���ǰ
    }
};

// ɾ��
template <class K, class V>
bool HashTable<K, V>::remove(K key)
{
    size_t index = hash(key);
    Entry<K, V>* e = hTable[index];
    if (e == nullptr || e->next == nullptr) {
        return false;
    }
    Entry<K, V>* pre;
    while (e->next != nullptr) {
        pre = e;
        e = e->next;
        if (e->key == key) {
            pre->next = e->next;
            --availableSize;
            if (hTable[index]->next == nullptr) {
                --usedIndexs;
            }
            delete e;
            return true;
        }
    }
    return true;
};

// ��ȡ
template <class K, class V>
V& HashTable<K, V>::get(const K& key)
{
    size_t index = hash(key);
    Entry<K, V>* e = hTable[index];

    if (e == nullptr || e->next == nullptr) {
        throw "��Ч��";
    }
    while (e->next != nullptr) {
        e = e->next;
        if (e->key == key) {
            return e->value;
        }
    }
    throw "��Ч��";
};

// [] ���������
template <class K, class V>
V& HashTable<K, V>::operator[](const K& key)
{
    size_t index = hash(key);
    Entry<K, V>* e = hTable[index];
    if (e == nullptr || e->next == nullptr) {
        put(key, V()); // �Ҳ���������
        return get(key);
    }
    while (e->next != nullptr) {
        e = e->next;
        if (e->key == key) {
            return e->value;
        }
    }
    put(key, V());
    return get(key);
};

// ����
template <class K, class V>
bool HashTable<K, V>::find(const K& key)
{
    size_t index = hash(key);
    Entry<K, V>* e = hTable[index];
    if (e == nullptr || e->next == nullptr) {
        return false;
    }
    while (e->next != nullptr) {
        e = e->next;
        if (e->key == key) {
            return true;
        }
    }
    return false;
};

// ���
template <class K, class V>
void HashTable<K, V>::output()
{
    for (int i = 0; i < capacity; i++) {
        std::cout << i << ": ";
        if (hTable[i] == nullptr || hTable[i]->next == nullptr) {
            std::cout << std::endl;
            continue;
        }
        Entry<K, V>* n = hTable[i]->next;
        while (n != nullptr) {
            std::cout << "< " << n->key << ", "
                      << n->value << " >  ";
            n = n->next;
        }
        std::cout << std::endl;
    }
}
#endif