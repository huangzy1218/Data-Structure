#include <cassert>
#include <iostream>
using namespace std;

const int defaultSize = 50;
template <class T>
class BitSet;
template <class T>
istream& operator>>(istream& in, BitSet<T>& r); // ����
template <class T>
ostream& operator<<(ostream& in, BitSet<T>& r); // ���
template <class T>
class BitSet {
public:
    BitSet(int sz = defaultSize); // ���캯��
    BitSet(const BitSet<T>& r); // ���ƹ��캯��
    ~BitSet() { delete[] bitVector; } // ��������
    void makeEmpty() // �ÿռ���
    {
        for (int i = 0; i < vectorSize; i++)
            bitVector[i] = 0;
    }
    unsigned short getMember(const T& x); // ��ȡ����Ԫ�� x
    void putMember(const T x, unsigned short v); // ��ֵ v ���뼯��Ԫ�� x
    bool addMember(const T x); // ���� x
    bool deleteMember(const T x); // ɾ�� x
    BitSet<T>& operator=(const BitSet<T>& r); // ��ֵ
    BitSet<T> operator+(const BitSet<T>& r); // ������
    BitSet<T> operator*(const BitSet<T>& r); // ������
    BitSet<T> operator-(const BitSet<T>& r); // �����
    bool contains(const T x); // �ж��Ƿ���Ԫ�� x
    bool subSet(BitSet<T>& r); // �ж��Ƿ�Ϊ�Ӽ�
    bool operator==(const BitSet<T>& r); // �жϼ����Ƿ����
    template <class U>
    friend istream& operator>>(istream& in, BitSet<U>& r); // ����
    template <class U>
    friend ostream& operator<<(ostream& out, BitSet<T>& r); // ���
    int size() const { return setSize; }

private:
    int setSize; // ���ϴ�С
    int vectorSize; // λ�����С
    unsigned short* bitVector; // �洢����Ԫ�ص�����
};

// ���캯��
template <class T>
BitSet<T>::BitSet(int sz)
    : setSize(sz)
{
    assert(setSize > 0);
    vectorSize = (setSize + 15) >> 4; // ������������
    bitVector = new unsigned short[vectorSize];
    assert(bitVector != NULL);
    for (int i = 0; i < vectorSize; i++) // ��ʼ��
        bitVector[i] = 0;
};

// ���ƹ��캯��
template <class T>
BitSet<T>::BitSet(const BitSet<T>& r)
{
    setSize = r.setSize;
    vectorSize = r.vectorSize;
    bitVector = new unsigned short[vectorSize];
    assert(bitVector != NULL);
    for (int i = 0; i < vectorSize; i++)
        bitVector[i] = r.bitVector[i];
};

// ��ֵ���������
template <class T>
BitSet<T>& BitSet<T>::operator=(const BitSet<T>& r)
{
    if (this == &r)
        return *this;
    setSize = r.setSize;
    vectorSize = r.vectorSize;
    bitVector = new unsigned short[vectorSize];
    assert(bitVector != NULL);
    for (int i = 0; i < vectorSize; i++)
        bitVector[i] = r.bitVector[i];
    return *this;
};

// ��ȡ����Ԫ�� x, x �� 0 ��ʼ
template <class T>
unsigned short BitSet<T>::getMember(const T& x)
{
    int ad = x / 16, id = x % 16; // ����Ԫ���±�
    unsigned short elem = bitVector[ad]; // ȡ x ���ڵ�����Ԫ��
    return ((elem >> (15 - id)) % 2); // ȡ�� id λ��ֵ
};

// ��ֵ v ���뼯��Ԫ�� x
template <class T>
void BitSet<T>::putMember(const T x, unsigned short v)
{
    int ad = x / 16, id = x % 16;
    unsigned short elem = bitVector[ad];
    unsigned short temp = elem >> (15 - id);
    elem = elem << (id + 1);
    if (temp % 2 == 0 && v == 1) {
        temp = temp + 1; // ��λ��Ϊ 1
    } else if (temp % 2 == 1 && v == 0) {
        temp = temp - 1; // ��λ��Ϊ 0
    }
    bitVector[ad] = (temp << (15 - id)) | (elem >> (id + 1)); // �ͻ�
};

// ���
template <class T>
bool BitSet<T>::addMember(const T x)
{
    assert(x >= 0 && x < setSize); // ��� x �ĺ�����
    if (getMember(x) == 0) {
        putMember(x, 1); // 1 ��ʾ�ڼ���
        return true;
    }
    return false;
};

// ɾ��
template <class T>
bool BitSet<T>::deleteMember(const T x)
{
    assert(x >= 0 && x < setSize); // ��� x �ĺ�����
    if (getMember(x) == 1) {
        putMember(x, 0); // 0 ��ʾ���ڼ���
        return true;
    }
    return false;
};

// ������
template <class T>
BitSet<T> BitSet<T>::operator+(const BitSet<T>& r)
{
    assert(vectorSize == r.vectorSize); // �����ϴ�С���
    BitSet<T> temp(setSize);
    for (int i = 0; i < vectorSize; i++) {
        temp.bitVector[i] = bitVector[i] | r.bitVector[i];
    }
    return temp;
};

// ������
template <class T>
BitSet<T> BitSet<T>::operator*(const BitSet<T>& r)
{
    assert(vectorSize == r.vectorSize); // �����ϴ�С���
    BitSet<T> temp(setSize);
    for (int i = 0; i < vectorSize; i++) {
        temp.bitVector[i] = bitVector[i] & r.bitVector[i];
    }
    return temp;
};

// �����
template <class T>
BitSet<T> BitSet<T>::operator-(const BitSet<T>& r)
{
    assert(vectorSize == r.vectorSize); // �����ϴ�С���
    BitSet<T> temp(setSize);
    for (int i = 0; i < vectorSize; i++) {
        temp.bitVector[i] = bitVector[i] & !r.bitVector[i];
    }
    return temp;
};

// �ж��Ƿ���Ԫ�� x
template <class T>
bool BitSet<T>::contains(const T x)
{
    assert(x >= 0 && x <= setSize);
    return (getMember(x) == 1) ? true : false;
};

// �ж��Ƿ�Ϊ�Ӽ�
template <class T>
bool BitSet<T>::subSet(BitSet<T>& r)
{
    assert(setSize == r.setSize);
    for (int i = 0; i < vectorSize; i++) {
        if (bitVector[i] & !r.bitVector[i])
            return false;
    }
    return true;
};

// �жϼ����Ƿ����
template <class T>
bool BitSet<T>::operator==(const BitSet<T>& r)
{
    if (vectorSize != r.vectorSize)
        return false;
    for (int i = 0; i < vectorSize; i++) {
        if (bitVector[i] != r.bitVector[i])
            return false;
    }
    return true;
};

// ����
template <class T>
istream& operator>>(istream& in, BitSet<T>& r)
{
    int n;
    T member;
    cout << "��ʼ����λͼ��������Ԫ�ظ������������뼯��Ԫ�أ�" << endl;
    in >> n;
    for (int i = 0; i < n; i++) {
        in >> member;
        r.addMember(member);
    }
    return in;
};

// ���
template <class T>
ostream& operator<<(ostream& out, BitSet<T>& r)
{
    int n;
    T member;
    int count = 0;
    cout << "{";
    for (int i = 0; i < r.size(); i++) {
        if (r.getMember(i) == 1) {
            if (count != 0)
                out << ", ";
            out << i;
            ++count;
        }
    }
    out << "}" << endl;
    return out;
};