#include <iostream>
using namespace std;

template <class T>
struct DblNode {
    T data;
    DblNode<T>*lLink, rLink; // ǰ��������������̣�������ָ��
    DblNode(DblNode<T>* left = NULL, DblNode<T>* right = NULL)
        : lLink(left)
        , rLink(r)
    {
    } // ���캯��
    DblNode(T value, DblNode<T>* left = NULL, DblNode<T>* right = NULL)
        : data(T)
        , lLink(left)
        , rLink(r)
    {
    } // ���캯��
};

template <class T>
class DblList : public LinearList<T> {
public:
    DblList(T uniqueVal); // ���캯������������ͷ���
    ~DblList(); // ��������
    int Length() const; // ����������
    bool IsEmpty();
    {
        return first->rlink == first;
    } // �пգ�ͷ������һ�������Ϊͷ���
    DblNode<T>* GetHead() const { return first; } // ȡ����ͷ����ַ
    void SetHead(DblNode<T>* ptr);
    {
        first = ptr;
    } // ����ͷ����ַ
    DblNode<T>* Search(const T& x); // �������̷������Ѱ��x
    DblNode<T>* Locate(int i, int d); // ������λ���Ϊi�Ľ�㣬d=0ǰ�����򣬷����̷���
    bool Insert(int i, const T& x, int d); // �ڵ�i��ֵ������½�㣬d=0ǰ�����򣬷����̷���
    bool Remove(int i, T& x, int d); // ɾ����i����㣬d=0ǰ�����򣬷����̷���
private:
    DblNode<T>* first;
};

// ���캯������������ͷ���
template <class T>
DblList<T>::DblList(T uniqueVal)
{
    first = new DblNode<T>(uniqueVal);
    if (first == NULL) {
        cerr << "�ڴ����ʧ��" << endl;
        exit(1);
    }
    first->rLink = first->lLink = first; // ǰ����̾�Ϊ�䱾��������ѭ������
}

// ����������
template <class T>
int DblList<T>::Length() const
{
    DblNode<T>* current = first->rLink;
    int count = 0;
    while (current != first) {
        current = current->rLink; // ������ѭ����������������rLink��Ϊ�������е�link
        ++count;
    }
    return count;
}

// ������λ���Ϊi�Ľ�㣬d=0ǰ�����򣬷����̷���
template <class T>
DblNode<T>* DblList<T>::Locate(int i, int d)
{
    if (first->rLink == first || i == 0) { // ��Ѱ��ͷ��������Ϊ��
        return first;
    }
    DblNode<T>* current;
    if (d == 0) { // ��ǰ���ָ��ͷ����ǰ�����
        current = first->lLink;
    } else {
        current = first->rLink; // ��ǰ���ָ��ͷ���ĺ�̽��
    }
    for (int j = 1; j < i; j++) {
        if (current == first) { // ����������Χ
            break;
        } else if (d == 0) {
            current = current->lLink; // ǰ��Ѱ��
        } else {
            current = current->rLink; // ���Ѱ��
        }
    }

    if (current != first) {
        return current;
    } else {
        return NULL;
    }
}

// �ڵ�i��ֵ������½�㣬d=0ǰ�����򣬷����̷���
template <class T>
bool* DblList<T>::Insert(int i, const T& x, int d)
{
    DblNode<T>* current = Locate(i, d); // ��λ��ǰ���
    if (current == NULL) {
        return false;
    }
    DblNode<T>* newNode = DblNode<T>(x);
    if (newNode == NULL) {
        cerr << "�ڴ����ʧ��" << endl;
        exit(0);
    }
    if (d == 0) { // ǰ������
        newNode->lLink = current->lLink; // �½���ǰ�����Ϊ��ǰ����ǰ�����
        current->lLink = newNode; // ��ǰ����ǰ�����Ϊ�½ڵ�
        newNode->lLink->rLink = newNode; // �½ڵ��ǰ�����ĺ�̽��Ϊ�䱾��
        newNode->rLink = current; // �½ڵ�ĺ�̽��Ϊ��ǰ���
    } else { // ��̲���
        newNode->rLink = current->rLink; // �½��ĺ�̽��Ϊ��ǰ���ĺ�̽��
        current->rLink = newNode; // �½��ĺ�̽��Ϊ��ǰ���ĺ�̽��
        newNode->rLink->lLink = newNode; // �½��ĺ�̽���ǰ�����Ϊ�䱾��
        newNode->lLink = current; // �½ڵ��ǰ�����Ϊ��ǰ��㣨��β��Ӧ��
    }
    return true;
}

// ɾ����i����㣬d=0ǰ�����򣬷����̷���
template <class T>
bool DblList<T>::Remove(int i, T& x, int d)
{
    DblNode<T>* current = Locate(i, d);
    if (current == NULL) {
        return false;
    }
    current->rLink->lLink = current->lLink;
    current->lLink->rLink = current->rLink;
    x = current->data;
    delete current;
    return true;
}