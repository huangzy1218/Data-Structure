#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
template <class T>
class LinkedSet;
template <class T>
istream& operator>>(istream& in, LinkedSet<T>& r); // ����
template <class T>
ostream& operator<<(ostream& in, LinkedSet<T>& r); // ���
template <class T>
struct SetNode {
    T data; // ��Ա����
    SetNode<T>* link; // ����ָ��
    SetNode()
        : link(NULL) {};
    SetNode(const T& x, SetNode<T>* next = NULL)
        : data(x)
        , link(next) {};
};

template <class T>
class LinkedSet {
public:
    LinkedSet()
    {
        first = last = new SetNode<T>(); // ���캯��
    }
    LinkedSet(const LinkedSet<T>& r); // ���ƹ��캯��
    ~LinkedSet() // ��������
    {
        makeEmpty();
        delete first;
    }
    void makeEmpty(); // �ÿռ���
    bool addMember(const T& x); // ���� x
    bool deleteMember(const T& x); // ɾ�� x
    LinkedSet<T>& operator=(const LinkedSet<T>& r); // ��ֵ���������
    LinkedSet<T> operator+(const LinkedSet<T>& r); // ������
    LinkedSet<T> operator*(const LinkedSet<T>& r); // ������
    LinkedSet<T> operator-(const LinkedSet<T>& r); // �����
    bool contains(const T x); // �ж� x �Ƿ��ڼ�����
    bool operator==(const LinkedSet<T>& r); // �е�
    bool min(T& x); // ���ؼ�����Сֵ
    bool max(T& x); // ���ؼ������ֵ
    bool subSet(LinkedSet<T>& r); // �� r �Ƿ�Ϊ this ���Ӽ�
    template <class U>
    friend istream& operator>>(istream& in, LinkedSet<U>& r); // ����
    template <class U>
    friend ostream& operator<<(ostream& out, LinkedSet<T>& r); // ���
    // private:
    SetNode<T>*first, *last; // ���������ͷָ�룬���ָ��
};

// ���ƹ��캯��
template <class T>
LinkedSet<T>::LinkedSet(const LinkedSet<T>& r)
{
    SetNode<T>* srcptr = r.first->link;
    first = last = new SetNode<T>();
    while (srcptr != NULL) {
        last->link = new SetNode<T>(srcptr->data); // �������
        last = last->link;
        srcptr = srcptr->link;
    }
    last->link = NULL;
};

// �ÿ�
template <class T>
void LinkedSet<T>::makeEmpty()
{
    SetNode<T>* tempt; // ��ʱ��㣬��������ɾ��
    while (first->link != NULL) // ͷ�ڵ���޽��
    {
        tempt = first->link;
        first->link = tempt->link; // ͷ�ڵ����һ��ָ��ɾ��������һ�����
        delete tempt; // ɾ���ý��
    }
};

// �ж� x �Ƿ��ڼ�����
template <class T>
bool LinkedSet<T>::contains(const T x)
{
    SetNode<T>* temp = first->link; // ɨ��ָ��
    while (temp != NULL && temp->data < x) { // ѭ������
        temp = temp->link;
    }
    if (temp != NULL && temp->data == x)
        return true;
    else
        return false;
};

// ��� x
template <class T>
bool LinkedSet<T>::addMember(const T& x)
{
    SetNode<T>*p = first->link, *pre = first;
    while (p != NULL && p->data < x) {
        pre = p;
        p = p->link;
    }
    if (p != NULL && p->data == x)
        return false;
    SetNode<T>* s = new SetNode<T>(x);
    s->link = p;
    pre->link = s;
    if (p == NULL) {
        last = s;
    } // ����
    return true;
};

// ɾ�� x
template <class T>
bool LinkedSet<T>::deleteMember(const T& x)
{
    SetNode<T>*p = first->link, *pre = first;
    while (p != NULL && p->data < x) {
        pre = p;
        p = p->link;
    }
    if (p != NULL && p->data == x) {
        pre->link = p->link; // ɾ��
        if (p == last) {
            last = pre;
        }
        delete p;
        return true;
    } else {
        return false;
    }
};

// ��ֵ
template <class T>
LinkedSet<T>& LinkedSet<T>::operator=(const LinkedSet<T>& r)
{
    SetNode<T>* pb = r.first->link;
    SetNode<T>* pa = first = new SetNode<T>();
    while (pb != NULL) {
        pa->link = new SetNode<T>(pb->data);
        pa = pa->link;
        pb = pb->link;
    }
    pa->link = NULL;
    last = pa;
    return *this;
};

// ������
template <class T>
LinkedSet<T> LinkedSet<T>::operator+(const LinkedSet<T>& r)
{
    SetNode<T>* pa = first->link;
    SetNode<T>* pb = r.first->link;
    LinkedSet<T> temp;
    SetNode<T>*p, *pc = temp.first;
    while (pa != NULL && pb != NULL) {
        if (pa->data == pb->data) {
            pc->link = new SetNode<T>(pa->data);
            pa = pa->link;
            pb = pb->link;
        } else if (pa->data < pb->data) {
            pc->link = new SetNode<T>(pa->data);
            pa = pa->link;
        } else {
            pc->link = new SetNode<T>(pb->data);
            pb = pb->link;
        }
        pc = pc->link;
    }
    if (pa != NULL)
        p = pa;
    else
        p = pb;
    while (p != NULL) {
        pc->link = new SetNode<T>(p->data);
        pc = pc->link;
        p = p->link;
    }
    pc->link = NULL;
    temp.last = pc;
    return temp;
};

// ������
template <class T>
LinkedSet<T> LinkedSet<T>::operator*(const LinkedSet<T>& r)
{
    SetNode<T>* pa = first->link;
    SetNode<T>* pb = r.first->link;
    LinkedSet<T> temp;
    SetNode<T>* pc = temp.first;
    while (pa != NULL && pb != NULL) {
        if (pa->data == pb->data) {
            pc->link = new SetNode<T>(pa->data);
            pa = pa->link;
            pb = pb->link;
            pc = pc->link;
        } else if (pa->data < pb->data) {
            pa = pa->link;
        } else {
            pb = pb->link;
        }
    }
    pc->link = NULL;
    temp.last = pc;
    return temp;
};

// �����
template <class T>
LinkedSet<T> LinkedSet<T>::operator-(const LinkedSet<T>& r)
{
    SetNode<T>* pa = first->link;
    SetNode<T>* pb = r.first->link;
    LinkedSet<T> temp;
    SetNode<T>* pc = temp.first;
    while (pa != NULL && pb != NULL) {
        if (pa->data == pb->data) {
            pa = pa->link;
            pb = pb->link;
        } else if (pa->data < pb->data) {
            pc->link = new SetNode<T>(pa->data);
            pa = pa->link;
            pc = pc->link;
        } else {
            pb = pb->link;
        }
    }
    while (pa != NULL) {
        pc->link = new SetNode<T>(pa->data);
        pc = pc->link;
        pa = pa->link;
    }
    pc->link = NULL;
    temp.last = pc;
    return temp;
};

// �е�
template <class T>
bool LinkedSet<T>::operator==(const LinkedSet<T>& r)
{
    SetNode<T>* pa = first->link;
    SetNode<T>* pb = r.first->link;
    LinkedSet<T> temp;
    SetNode<T>*p, *pc = temp.first;
    while (pa != NULL && pb != NULL) {
        if (pa->data == pb->data) {
            pa = pa->link;
            pb = pb->link;
        } else {
            return false;
        }
    }
    if (pa != NULL || pb != NULL) {
        return false;
    }
};

// ����
template <class T>
istream& operator>>(istream& in, LinkedSet<T>& r)
{
    int n;
    T member;
    cout << "��ʼ������ʽ���ϣ�������Ԫ�ظ������������뼯��Ԫ�أ�" << endl;
    in >> n;
    for (int i = 0; i < n; i++) {
        in >> member;
        r.addMember(member);
    }
    return in;
};

// ���
template <class T>
ostream& operator<<(ostream& out, LinkedSet<T>& r)
{
    int n;
    T member;
    int count = 0;
    cout << "{";
    SetNode<T>* ptr = r.first->link;
    while (ptr != NULL) {
        if (count != 0)
            cout << ", ";
        out << ptr->data;
        ptr = ptr->link;
        ++count;
    }
    out << "}" << endl;
    return out;
};