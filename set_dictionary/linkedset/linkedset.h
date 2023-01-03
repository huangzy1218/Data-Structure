#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
template <class T>
class LinkedSet;
template <class T>
istream& operator>>(istream& in, LinkedSet<T>& r); // 输入
template <class T>
ostream& operator<<(ostream& in, LinkedSet<T>& r); // 输出
template <class T>
struct SetNode {
    T data; // 成员数据
    SetNode<T>* link; // 链接指针
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
        first = last = new SetNode<T>(); // 构造函数
    }
    LinkedSet(const LinkedSet<T>& r); // 复制构造函数
    ~LinkedSet() // 析构函数
    {
        makeEmpty();
        delete first;
    }
    void makeEmpty(); // 置空集合
    bool addMember(const T& x); // 加入 x
    bool deleteMember(const T& x); // 删除 x
    LinkedSet<T>& operator=(const LinkedSet<T>& r); // 赋值运算符重载
    LinkedSet<T> operator+(const LinkedSet<T>& r); // 并操作
    LinkedSet<T> operator*(const LinkedSet<T>& r); // 交操作
    LinkedSet<T> operator-(const LinkedSet<T>& r); // 差操作
    bool contains(const T x); // 判断 x 是否在集合中
    bool operator==(const LinkedSet<T>& r); // 判等
    bool min(T& x); // 返回集合最小值
    bool max(T& x); // 返回集合最大值
    bool subSet(LinkedSet<T>& r); // 判 r 是否为 this 的子集
    template <class U>
    friend istream& operator>>(istream& in, LinkedSet<U>& r); // 输入
    template <class U>
    friend ostream& operator<<(ostream& out, LinkedSet<T>& r); // 输出
    // private:
    SetNode<T>*first, *last; // 有序链表的头指针，结点指针
};

// 复制构造函数
template <class T>
LinkedSet<T>::LinkedSet(const LinkedSet<T>& r)
{
    SetNode<T>* srcptr = r.first->link;
    first = last = new SetNode<T>();
    while (srcptr != NULL) {
        last->link = new SetNode<T>(srcptr->data); // 逐个复制
        last = last->link;
        srcptr = srcptr->link;
    }
    last->link = NULL;
};

// 置空
template <class T>
void LinkedSet<T>::makeEmpty()
{
    SetNode<T>* tempt; // 临时结点，用于依次删除
    while (first->link != NULL) // 头节点后无结点
    {
        tempt = first->link;
        first->link = tempt->link; // 头节点的下一个指向删除结点的下一个结点
        delete tempt; // 删除该结点
    }
};

// 判断 x 是否在集合中
template <class T>
bool LinkedSet<T>::contains(const T x)
{
    SetNode<T>* temp = first->link; // 扫描指针
    while (temp != NULL && temp->data < x) { // 循链搜索
        temp = temp->link;
    }
    if (temp != NULL && temp->data == x)
        return true;
    else
        return false;
};

// 添加 x
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
    } // 链入
    return true;
};

// 删除 x
template <class T>
bool LinkedSet<T>::deleteMember(const T& x)
{
    SetNode<T>*p = first->link, *pre = first;
    while (p != NULL && p->data < x) {
        pre = p;
        p = p->link;
    }
    if (p != NULL && p->data == x) {
        pre->link = p->link; // 删除
        if (p == last) {
            last = pre;
        }
        delete p;
        return true;
    } else {
        return false;
    }
};

// 赋值
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

// 并操作
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

// 交操作
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

// 差操作
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

// 判等
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

// 输入
template <class T>
istream& operator>>(istream& in, LinkedSet<T>& r)
{
    int n;
    T member;
    cout << "开始创建链式集合，请输入元素个数并依次输入集合元素：" << endl;
    in >> n;
    for (int i = 0; i < n; i++) {
        in >> member;
        r.addMember(member);
    }
    return in;
};

// 输出
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