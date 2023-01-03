#include "..\..\linear_list\sequence_list\SeqList.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
using namespace std;

// ��������ඨ��
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
    int utype; // ��־��0��ʾ����ͷ��㣬1��ʾ�ӽڵ㣬2�����ӱ���
    GenListNode<T>* tlink;
    union // ʹ��������Ч�����ڴ�
    {
        int ref;
        T value;
        GenListNode<T>* hlink;
    } info; // ��Ϣ��utype = 0����Ϣ�������ü�����utype = 1�������ֵ��utype = 2�����һ������ĵ�ַ
};

template <class T>
struct Items // �ӱ���
{
    int utype; // ��־��0��ʾ����ͷ��㣬1��ʾ�ӽڵ㣬2�����ӱ���
    union {
        int ref;
        T value;
        GenListNode<T>* link;
    } info; // ��Ϣ��utype = 0����Ϣ����
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
    bool head(Items<T>& x); // ���ر�ͷ
    bool tail(GenList<T>& lt); // ���ر�β
    GenListNode<T>* getFirst(); // ���ص�һ��Ԫ��
    GenListNode<T>* next(GenListNode<T>* elem); // ����elem��ֱ�Ӻ��
    void copy(const GenList<T>& r); // �����ĸ���
    int length(); // ��ȡ��
    int depth(); // ��ȡ�ǵݹ������
    template <class U>
    friend istream& operator>>(istream& in, GenList<U>& l); // �������������

    // private:
    GenListNode<T>* first; // �����ͷָ��
    GenListNode<T>* copy(GenListNode<T>* ls); // ����һ��ls�ǹ���ǵݹ��
    int length(GenListNode<T>* ls); // ����lsָʾ�Ĺ������
    int depth(GenListNode<T>* ls); // // ����lsָʾ�Ĺ�������
    bool equal(GenListNode<T>* s, GenListNode<T>* t); // �ж���s��tΪ��ͷ�Ĺ�����Ƿ����
    void remove(GenListNode<T>* ls); // �ͷ���lsΪ����ͷ�ڵ�Ĺ����
    void createList(istream& in, GenListNode<T>*& ls, SeqList<T>& l1,
        SeqList<GenListNode<T>*>& l2); // ����������������������ַ�������������һ��������ͷ���Ĺ����ṹ
    // ע�⣺���������б�������һ����ӱ�������һ������ͷ��㣬�ձ�Ҳ������
};

// ���캯��
template <class T>
GenList<T>::GenList()
{
    first = new GenListNode<T>();
    if (first == NULL) {
        cerr << "�ڴ����ʧ��" << endl;
    }
};

// ���ر�ͷ
template <class T>
bool GenList<T>::head(Items<T>& x)
{
    if (first->tlink == NULL) // �ձ�
    {
        return false;
    } else {
        x.utype = first->tlink->utype;
        x.info = first->tlink->info;
        return true;
    }
};

// ���ر�β
template <class T>
bool GenList<T>::tail(GenList<T>& lt)
{
    if (first->tlink == NULL) {
        return false;
    } else // ���ǿգ����ع�����ͷԪ��֮������Ԫ����ɵı�
    {
        lt.first->utype = 0;
        lt.first->info.ref = 0;
        lt.first->tlink = copy(first->tlink->tlink); // ȥ��ͷԪ��
    }
};

// ��ȡ��һ��Ԫ��
template <class T>
GenListNode<T>* GenList<T>::getFirst()
{
    if (first->tlink == NULL) {
        return NULL;
    } else {
        return first->tlink;
    }
};

// ��ȡelemֱ�Ӻ��
template <class T>
GenListNode<T>* GenList<T>::next(GenListNode<T>* elem)
{
    if (elem->tlink == NULL) {
        return NULL;
    } else {
        return elem->tlink;
    }
};

// ����
template <class T>
void GenList<T>::copy(const GenList<T>& r)
{
    first = copy(r.first);
};

// ���ƣ�˽�к���������һ���޹����ӱ�ķǵݹ��
template <class T>
GenListNode<T>* GenList<T>::copy(GenListNode<T>* ls)
{
    GenList<T>* q = NULL;
    if (ls != NULL) {
        q = new GenListNode<T>();
        q->utype = ls->utype;
        switch (ls->utype) {
        case 0:
            q->info.ref = ls->info.ref; // ����ͷ���
            break;
        case 1:
            q->info.ref = ls->info.vale; // ԭ�ӽ��
            break;
        case 2:
            q->info.ref = copy(ls->info.hlink); // ����
            break;
        }
        q->tlink = copy(ls->tlink); // ����ͬһ����һ���
    }
    return q;
};

// ������ĳ���
template <class T>
int GenList<T>::length()
{
    return length(first);
};

// ��ǵݹ�����ĳ��ȣ�˽�У�
template <class T>
int GenList<T>::length(GenListNode<T>* ls)
{
    if (ls != NULL) {
        return 1 + length(ls->tlink);
    } else {
        return 0;
    }
};

// �������
template <class T>
int GenList<T>::depth()
{
    return depth(first);
};

// ����ǵݹ��������ȣ�˽�У�
template <class T>
int GenList<T>::depth(GenListNode<T>* ls)
{
    if (ls->tlink == NULL) {
        return 1; // �ձ����Ϊ1
    }
    GenListNode<T>* temp = ls->tlink;
    int m = 0, n;
    while (temp != NULL) {
        if (temp->utype == 2) {
            n = depth(temp->info.hlink); // �����Ըý��Ϊͷ�Ĺ�������
            if (m < n) {
                m = n;
            }
        }
        temp = temp->tlink;
    }
    return m + 1;
};

// �ж���s��tΪ��ͷ�Ĺ�����Ƿ���ȣ�˽�У�
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

// ���������
template <class T>
void GenList<T>::createList(istream& in, GenListNode<T>*& ls, SeqList<T>& l1, SeqList<GenListNode<T>*>& l2)
{
    T chr;
    in >> chr;
    if (isalpha(chr) && isupper(chr) || chr == '(') // ��д��ĸ��'('
    {
        ls = new GenListNode<T>();
        ls->utype = 2; // �����ӱ�
        if (isalpha(chr) && isupper(chr)) // ��������
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
                exit(1); // ������Ϊ(
            }
        }
        ls->info.hlink = new GenListNode<T>();
        ls->info.hlink.utype = 0;
        ls->info.hlink->ref = 1;
        createList(in, ls->hlink->tlink, l1, l2);
        createList(in, ls, l1, l2);
    } else if (isalpha(chr) && islower(chr)) // ����Ԫ�ؽ��
    {
        ls = new GenListNode<T>();
        ls->utype = 1;
        ls->info.value = chr;
        createList(in, ls, l1, l2);
    } else if (chr == ',') // �����������
    {
        createList(in, ls->tlink, l1, l2);
    } else if (chr == ')') // ����β
    {
        ls->tlink - NULL;
    } else if (chr == '#') // �ձ�����β
    {
        ls == NULL;
    }
};
