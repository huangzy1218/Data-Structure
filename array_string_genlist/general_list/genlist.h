#include "..\..\linear_list\sequence_list\SeqList.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
using namespace std;

// 广义表结点类定义
template <class T>
struct GenListNode {
public:
    GenListNode()
    {
        utype = 0;
        tlink = NULL;
        info.ref = 0;
    }
    GenListNode(GenListNode<T>& rl)
    {
        utype = rl.utype;
        tlink = rl.tlink;
        info = rl.info;
    }

    // private:
    int utype; // 标志域：0表示附加头结点，1表示子节点，2代表子表结点
    GenListNode<T>* tlink;
    union // 使用联合有效减少内存
    {
        int ref;
        T value;
        GenListNode<T>* hlink;
    } info; // 信息域：utype = 0，信息域存放引用计数，utype = 1，存放数值，utype = 2存放下一个表结点的地址
};

template <class T>
struct Items // 子表结点
{
    int utype; // 标志域：0表示附加头结点，1表示子节点，2代表子表结点
    union {
        int ref;
        T value;
        GenListNode<T>* link;
    } info; // 信息域：utype = 0，信息域存放
    Items()
    {
        utype = 0;
        info.ref = 0;
    }
    Items(Items<T>& rl)
    {
        utype = rl.utype;
        info = rl.info;
    }
};

template <class T>
class GenList {
public:
    GenList();
    ~GenList();
    bool head(Items<T>& x); // 返回表头
    bool tail(GenList<T>& lt); // 返回表尾
    GenListNode<T>* getFirst(); // 返回第一个元素
    GenListNode<T>* next(GenListNode<T>* elem); // 返回elem的直接后继
    void copy(const GenList<T>& r); // 广义表的复制
    int length(); // 获取表长
    int depth(); // 获取非递归表的深度
    template <class U>
    friend istream& operator>>(istream& in, GenList<U>& l); // 输入运算符重载

    // private:
    GenListNode<T>* first; // 广义表头指针
    GenListNode<T>* copy(GenListNode<T>* ls); // 复制一个ls非共享非递归表
    int length(GenListNode<T>* ls); // 求以ls指示的广义表长度
    int depth(GenListNode<T>* ls); // // 求以ls指示的广义表深度
    bool equal(GenListNode<T>* s, GenListNode<T>* t); // 判断以s和t为表头的广义表是否相等
    void remove(GenListNode<T>* ls); // 释放以ls为附加头节点的广义表
    void createList(istream& in, GenListNode<T>*& ls, SeqList<T>& l1,
        SeqList<GenListNode<T>*>& l2); // 从输入流对象输入广义表的字符串描述，建立一个带附加头结点的广义表结构
    // 注意：广义表的所有表，无论那一层的子表，都带有一个附加头结点，空表也不例外
};

// 构造函数
template <class T>
GenList<T>::GenList()
{
    first = new GenListNode<T>();
    if (first == NULL) {
        cerr << "内存分配失败" << endl;
    }
};

// 返回表头
template <class T>
bool GenList<T>::head(Items<T>& x)
{
    if (first->tlink == NULL) // 空表
    {
        return false;
    } else {
        x.utype = first->tlink->utype;
        x.info = first->tlink->info;
        return true;
    }
};

// 返回表尾
template <class T>
bool GenList<T>::tail(GenList<T>& lt)
{
    if (first->tlink == NULL) {
        return false;
    } else // 若非空，返回广义表除头元素之外其他元素组成的表
    {
        lt.first->utype = 0;
        lt.first->info.ref = 0;
        lt.first->tlink = copy(first->tlink->tlink); // 去除头元素
    }
};

// 获取第一个元素
template <class T>
GenListNode<T>* GenList<T>::getFirst()
{
    if (first->tlink == NULL) {
        return NULL;
    } else {
        return first->tlink;
    }
};

// 获取elem直接后继
template <class T>
GenListNode<T>* GenList<T>::next(GenListNode<T>* elem)
{
    if (elem->tlink == NULL) {
        return NULL;
    } else {
        return elem->tlink;
    }
};

// 复制
template <class T>
void GenList<T>::copy(const GenList<T>& r)
{
    first = copy(r.first);
};

// 复制，私有函数，复制一个无共享子表的非递归表
template <class T>
GenListNode<T>* GenList<T>::copy(GenListNode<T>* ls)
{
    GenList<T>* q = NULL;
    if (ls != NULL) {
        q = new GenListNode<T>();
        q->utype = ls->utype;
        switch (ls->utype) {
        case 0:
            q->info.ref = ls->info.ref; // 附加头结点
            break;
        case 1:
            q->info.ref = ls->info.vale; // 原子结点
            break;
        case 2:
            q->info.ref = copy(ls->info.hlink); // 表结点
            break;
        }
        q->tlink = copy(ls->tlink); // 处理同一层下一结点
    }
    return q;
};

// 求广义表的长度
template <class T>
int GenList<T>::length()
{
    return length(first);
};

// 求非递归广义表的长度（私有）
template <class T>
int GenList<T>::length(GenListNode<T>* ls)
{
    if (ls != NULL) {
        return 1 + length(ls->tlink);
    } else {
        return 0;
    }
};

// 求表的深度
template <class T>
int GenList<T>::depth()
{
    return depth(first);
};

// 计算非递归广义表的深度（私有）
template <class T>
int GenList<T>::depth(GenListNode<T>* ls)
{
    if (ls->tlink == NULL) {
        return 1; // 空表深度为1
    }
    GenListNode<T>* temp = ls->tlink;
    int m = 0, n;
    while (temp != NULL) {
        if (temp->utype == 2) {
            n = depth(temp->info.hlink); // 计算以该结点为头的广义表深度
            if (m < n) {
                m = n;
            }
        }
        temp = temp->tlink;
    }
    return m + 1;
};

// 判断以s和t为表头的广义表是否相等（私有）
template <class T>
bool equal(GenListNode<T>* s, GenListNode<T>* t)
{
    bool flag;
    if (s->tlink == NULL && t->tlink == NULL) {
        return true;
    }
    if (s->tlink != NULL && t->tlink != NULL && s->tlink->utype == t->tlink->utype) {
        if (s->tlink->utype == 1) {
            flag = (s->tlink->info.value == t->tlink->info.value);
        } else if (s->tlink->utype == 2) {
            flag = equal(s->tlink->info.hlink, t->tlink->info.hlink);
        }
        if (flag) {
            return equal(s->tlink, t->tlink);
        }
    }
};

// 建立广义表
template <class T>
void GenList<T>::createList(istream& in, GenListNode<T>*& ls, SeqList<T>& l1, SeqList<GenListNode<T>*>& l2)
{
    T chr;
    in >> chr;
    if (isalpha(chr) && isupper(chr) || chr == '(') // 大写字母或'('
    {
        ls = new GenListNode<T>();
        ls->utype = 2; // 建立子表
        if (isalpha(chr) && isupper(chr)) // 表名处理
        {
            int n = l1.length();
            int m = l1.search(chr);
            if (m != -1) {
                GenListNode<T>* p = l2.locate(m);
                p->ref++;
            } else {
                l1.insert(n, chr);
                l2.insert(n, ls);
            }
            in >> chr;
            if (chr != '(') {
                exit(1); // 表名后为(
            }
        }
        ls->info.hlink = new GenListNode<T>();
        ls->info.hlink.utype = 0;
        ls->info.hlink->ref = 1;
        createList(in, ls->hlink->tlink, l1, l2);
        createList(in, ls, l1, l2);
    } else if (isalpha(chr) && islower(chr)) // 建立元素结点
    {
        ls = new GenListNode<T>();
        ls->utype = 1;
        ls->info.value = chr;
        createList(in, ls, l1, l2);
    } else if (chr == ',') // 建立后续结点
    {
        createList(in, ls->tlink, l1, l2);
    } else if (chr == ')') // 链收尾
    {
        ls->tlink - NULL;
    } else if (chr == '#') // 空表，链收尾
    {
        ls == NULL;
    }
};
