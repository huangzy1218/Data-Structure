#include <algorithm>
#include <iostream>
using namespace std;
const int defaultSize = 100;
template <class T>
class LinearList {
public:
    LinearList() { } // ���캯��
    ~LinearList() { } // ��������
    virtual bool insert(int i, const T& x) = 0; // ����
    virtual bool remove(int i, T& x) = 0; // ɾ��
    virtual int search(T& x) const = 0; // ����
    virtual int locate(int i) const = 0; // ��λ
    virtual void sort() = 0; // ����
    virtual bool getData(int i, T& x) const = 0; // ��ȡָ��λԪ��ֵ
    virtual void setData(int i, const T& x) = 0; // ����ָ��λԪ��ֵ
    virtual int size() const = 0; // ��ȡ��С
    virtual int length() const = 0; // ��ȡ����
    virtual bool isEmpty() const = 0; // �п�
    virtual bool isFull() const = 0; // ����
    virtual void input() = 0; // ����
    virtual void output() = 0; // ���
};