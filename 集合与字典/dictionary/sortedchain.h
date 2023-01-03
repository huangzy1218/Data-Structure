#include <cassert>
#include <iostream>
using namespace std;
template <class K, class E>
struct ChainNode {
    K index;
    E data;
    ChainNode<K, E>* link;
    ChainNode()
        : link(NULL) {}; // 构造函数
    ChainNode(K& i, E& elem, ChainNode<K, E>* next = NULL)
        : index(i)
        , data(elem)
        , link(next) {};
};

template <class K, class E>
class SortedChain {
public:
    SortedChain()
    {
        first = new ChainNode<K, E>; // 构造函数
        assert(first != NULL);
    }
    ~SortedChain() { makeEmpty(); } // 析构函数
    ChainNode<K, E>* search(const K key) const; // 搜索
    void insert(const K key, E& elem); // 插入
    bool remove(const K key, E& elem); // 删除
    ChainNode<K, E>* begin() // 定位第一个
    {
        return first->link;
    }
    ChainNode<K, E>* next(ChainNode<K, E>* current) const // 定位下一个
    {
        if (current != NULL) {
            return current->link;
        } else {
            return NULL;
        }
    }

private:
    ChainNode<K, E>* first;
    void makeEmpty(); // 清空
};

// 清空
template <class K, class E>
void SortedChain<K, E>::makeEmpty()
{
    ChainNode<K, E> current;
    while (first->link != NULL) {
        current = first->link;
        first->link = current->link;
        delete current;
    }
};

// 搜索
template <class K, class E>
ChainNode<K, E>* SortedChain<K, E>::search(const K key) const
{
    ChainNode<K, E>* p = first->link;
    while (p != NULL && p->index < key) {
        p = p->link;
    }
    if (p != NULL && p->index == key) {
        return p;
    } else {
        return NULL;
    }
};

// 插入
template <class K, class E>
void SortedChain<K, E>::insert(const K key, E& elem)
{
    ChainNode<K, E>*p = first->link, *pre = first, *newNode;
    while (p != NULL && p->index < key) {
        pre = p;
        p = p->link;
    }
    if (p != NULL && p->index == key) {
        p->data = elem;
        return;
    }
    newNode = new ChainNode<E, K>(key, elem);
    if (newNode == NULL) {
        cerr << "存储分配失败" << endl;
    }
    newNode->link = p;
    pre->link = newNode;
};

// 删除
template <class K, class E>
bool SortedChain<K, E>::remove(const K key, E& elem)
{
    ChainNode<K, E>*p = first, *pre = first;
    while (p != NULL && p->index < key) {
        pre = p;
        p = p->link;
    }
    if (p != NULL && p->data == key) {
        pre->link = p->link;
        elem = p->data;
        delete p;
        return true;
    }
    return false;
};
