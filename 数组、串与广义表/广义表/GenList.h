#include <iostream>
#include <cassert>
#include <cstdlib>

template <class T>
struct Items
{
    int utype;
    union
    {
        int ref;
        T value;
        GneListNode<T> *link;
    } info;
    Items() : utype(0), info.ref(0) {}
    Items(Items<T> &rl)
    {
        utype = rl.utype;
        info = rl.info;
    }
};

// 广义表结点类定义
template <class T>
struct GenListNode
{
public:
    GenListNode() : utype(0), tlink(NULL), info.ref(0) {}
    GenListNode(GenListNode<T> &rl)
    {
        utype = rl.utype;
        tlink = rl.tlink;
        info = rl.info;
    }

private:
    int utype;
    GenListNode<T> *tlink;
    union
    {
        int ref;
        T value;
        GenListNode<T> *hlink;
    } info;
};

template <class T>
class GenList
{
public:
    GenList();
    ~GenList();
    bool head(Items &x);       // 返回表头
    bool tail(GenList<T> &lt); // 返回表尾
    GenListNode<T> *first();
    GenListNode<T> *next(GenListNode<T> *elem);
    void copy(const GenList<T> &r);
    int length();
    int depth();
    friend istream &operator>>(istream &in, GenList<T> &l);

private:
    GenListNode<T> *first;
    GenListNode<T> *copy(GenListNode<T> *ls);
    int length(GenListNode<T> *ls);
    int depth(GenListNode<T> *ls);
};