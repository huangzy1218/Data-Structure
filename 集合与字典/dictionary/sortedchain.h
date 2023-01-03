#include <cassert>
#include <iostream>
using namespace std;
template <class K, class E>
struct ChainNode {
    K index;
    E data;
    ChainNode<K, E>* link;
    ChainNode()
        : link(NULL) {}; // ���캯��
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
        first = new ChainNode<K, E>; // ���캯��
        assert(first != NULL);
    }
    ~SortedChain() { makeEmpty(); } // ��������
    ChainNode<K, E>* search(const K key) const; // ����
    void insert(const K key, E& elem); // ����
    bool remove(const K key, E& elem); // ɾ��
    ChainNode<K, E>* begin() // ��λ��һ��
    {
        return first->link;
    }
    ChainNode<K, E>* next(ChainNode<K, E>* current) const // ��λ��һ��
    {
        if (current != NULL) {
            return current->link;
        } else {
            return NULL;
        }
    }

private:
    ChainNode<K, E>* first;
    void makeEmpty(); // ���
};

// ���
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

// ����
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

// ����
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
        cerr << "�洢����ʧ��" << endl;
    }
    newNode->link = p;
    pre->link = newNode;
};

// ɾ��
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
