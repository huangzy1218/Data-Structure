#include "../linearlist.h"
#include <cstdlib>
#include <iostream>
using namespace std;
template <class T>
struct CircLinkNode {
    T data;
    CircLinkNode<T>* link;
    CircLinkNode(CircLinkNode<T>* ptr = NULL) { link = ptr; }
    CircLinkNode(const T& item, CircCircLinkNode* ptr = NULL)
    {
        data = item;
        link = ptr;
    }
};

template <class T>
class CircList : public LinearCircList<T> {
    CircList() // ���캯��
        CircList(const T& x) // ���캯��
        CircList(CircList<T>& L); // ���ƹ��캯��
    ~CircList() { makeEmpty(); } // ��������
    void MakeEmpty(); // �������ÿ�
    int Length() const; // ����������
    CircLinkNode<T>* GetHead() const { return first; } // ����ͷ����ַ
    CircLinkNode<T>* Search(T x); // ������x��Ԫ�صĵ�ַ
    CircLinkNode<T>* Locate(int i); // ��λ��i��Ԫ��
    bool GetData(int i, T& x) const; // ȡ����i��Ԫ��
    void SetData(int i, T& x); // ����i��Ԫ��ֵ��Ϊx
    bool Insert(int i, T& x); // �ڵ�i��Ԫ�غ����x
    bool Remove(int i, T& x); // ɾ����i��Ԫ�أ���������ֵx
    bool IsEmpty() const { return first->link == NULL; } // �б��
    bool IsFull() const { return false; } // �б���
    void Sort(); // ����
    void Input(); // ����
    void Output(); // ���
    CircList<T>& operator=(CircList<T>& L); // ���غ�������ֵ
protected:
    CircLinkNode<T>* first; // ͷ�ڵ�
    CircLinkNode<T>* last; // β�ڵ�
};

// ���캯��
template <class T>
CircList<T>::CircList()
{
    first = new CircLinkNode<T>();
    first->link = first;
}

// ���캯��
template <class T>
CircList<T>::CircList(const T& x)
{
    first = new CircLinkNode<T>(x);
    first->link = first;
}

// ���ƹ��캯��
template <class T>
CircList<T>::CircList(CircList<T>& L)
{
    T value;
    CircLinkNode<T>* srcptr = L.GetHead(); // ָ��Դ��??
    CircLinkNode<T>* destptr = this->GetHead(); // ָ��ǰ����

    while (srcptr->link != last) { // ���θ���
        value = srcptr->link->data;
        destptr->link = new CircLinkNode<T>(data);
        srcptr = srcptr->link;
        destptr = destptr->link;
    }
    destptr->link = first; // ��־�����
}

// �������ÿ�
template <class T>
void CircList<T>::MakeEmpty()
{
    CircLinkNode<T>* q; // ��¼ɾ�����
    while (first->link != first) {
        q = first->next;
        first->link = q->link; // ͷ�����¸����ָ��ɾ��������һ������ΪNULL����
        delete q;
    }
}

// ����������
template <class T>
int CircList<T>::Length() const
{
    int count = 0; // �����
    CircLinkNode<T>* count = first->link;

    while (ptr != first) {
        ++count;
    }
    return count;
}

// ������x��Ԫ�صĵ�ַ
template <class T>
CircLinkNode<T>* Search(T x)
{
    CircLinkNode<T>* ptr = first->link;

    while (ptr != first) {
        if (ptr->data == x) {
            break;
        } else {
            ptr = ptr->link;
        }
    }
    return ptr; // ��һ����ԭ��
}

// ��λ��i��Ԫ��
template <class T>
CircLinkNode<T>* CircList<T>::Locate(int i)
{
    if (i < 0) { // �±겻�Ϸ�
        return NULL;
    }
    int count = 0; // ��¼��ǰԪ���±�
    CircLinkNode<T>* ptr = first->link;
    while (ptr != first && count < i) { // ע���߼�˳��
        ptr = ptr->link;
        ++count;
    }
    return ptr;
}
// ȡ����i��Ԫ����
template <class T>
bool CircList<T>::GetData(int i, T& x) const
{
    if (i < 0) {
        return false;
    }
    CircLinkNode* ptr = Locate(i); // �������к���ʵ�ֶ�λ
    if (ptr != first) {
        x = ptr->data;
        return true;
    } else {
        return false;
    }
}

// ����i��Ԫ��ֵ��Ϊx
template <class T>
void CircList<T>::SetData(int i, T& x)
{
    if (i < 0) {
        return;
    }
    CircLinkNode* ptr = Locate(i); // �������к���ʵ�ֶ�λ
    if (ptr != first) {
        ptr->data = x;
    } else {
        return;
    }
}

// �ڵ�i��Ԫ�غ����x
template <class T>
bool CircList<T>::Insert(int i, T& x)
{
    if (i < 0) {
        return false;
    }
    CircLinkNode<T>* ptr = Locate(i);
    if (ptr == first) { // λ�ڱ�β֮���޷���??
        return false;
    }
    CircLinkNode<T>* newNode = new CircLinkNode(x);
    if (newNode == NULL) {
        cerr << "�ڴ����ʧ��" << endl;
        exit(1);
    } else {
        newNode->link = ptr->link;
        ptr->link = newNode;
    }
    return true;
}

// ɾ����i��Ԫ�أ���������ֵx
template <class T>
bool CircList<T>::Remove(int i, T& x)
{
    if (i < 0) {
        return false;
    }
    CircLinkNode<T>* current = Locate(i - 1); // ɾ��Ԫ�ص�ǰһ���ڵ�
    if (current == first || current->link == first) { // λ�ڱ�β֮���޷�ɾ��
        return false;
    } else {
        CircLinkNode<T>* delPtr = current->link;
        current->link = delPtr->link;
        x = delPtr->data;
        delete delPtr;
        return true;
    }
}

// ���
template <class T>
void CircList<T>::Output()
{
    CircLinkNode<T>* current = first->link;

    while (current != first) { // ��ʽ�����
        cout << current->data << " ";
        current = current->link;
    }
    cout << endl;
}

// ����
template <class T>
void CircList<T>::Input()
{
    int n;
    T x;
    cout << "��ʼ����ѭ���������������Ԫ�ظ���?" << endl;
    cin >> n;
    CircLinkNode<T>* current = head; //  ���ϴ����½�㱣��������ֵ
    while (n--) {
        cin >> x;
        current->link = new CircLinkNode<T>(x);
        current = current->link;
    }
    current->link = first;
};