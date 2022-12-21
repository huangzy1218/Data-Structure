#include "../LinearList.h"

template <class T>
class SeqList : public LinearList<T>
{
public:
    SeqList(int = defaultSize);                          // ���캯��
    SeqList<T> &operator=(const SeqList<T> &);           // ���غ�������ֵ
    SeqList(SeqList<T> &);                               // ���ƹ���
    ~SeqList() { delete[] data; }                        // ��������
    bool insert(int i, const T &x);                      // ����
    bool remove(int i, T &x);                            // ɾ��
    int search(T &x) const;                              // ����
    int locate(int i) const;                             // ��λ
    void sort();                                         // ����
    bool getData(int i, T &x) const;                     // ȡֵ
    void setData(int i, const T &x);                     // ��ֵ
    int size() const { return maxSize; }                 // ������ռ�
    int length() const { return last + 1; }              // �����
    bool isEmpty() const { return last == -1; };         // �б��
    bool isFull() const { return last == maxSize - 1; }; // �б���
    void input();                                        // ����
    void output();                                       // ���
protected:
    T *data;          // ����
    int maxSize;      // �����ռ�
    int last;         // ��β
    void reSize(int); // �ı��С
};

// ���캯��
template <typename T>
SeqList<T>::SeqList(int sz)
{
    if (sz > 0)
    {
        maxSize = sz; // �������ռ�
        last = -1;    // ��βλ��Ϊ-1
    }
    data = new T[maxSize];
    if (data == NULL)
    { // �ڴ����ʧ��
        cerr << "�洢�������" << endl;
        exit(1);
    }
};

// ���ƹ��캯��
template <typename T>
SeqList<T>::SeqList(SeqList<T> &L)
{
    maxSize = L.maxSize;
    last = L.last;
    data = new T[maxSize];
    if (data == NULL)
    {
        cerr << "�洢�������" << endl;
        exit(1);
    }
    for (int i = 0; i <= last; i++)
    {
        data[i] = L.data[i]; // ���θ�ֵ
    }
};

// ��ֵ���������
template <typename T>
SeqList<T> &SeqList<T>::operator=(const SeqList<T> &L)
{
    // ��ֹ���Ҹ�ֵ
    if (this == &L)
    {
        return *this;
    }
    delete[] data; // �ͷ�ԭ�ռ�
    maxSize = L.maxSize;
    last = L.last;
    data = new T[maxSize];
    if (data == NULL)
    {
        cerr << "�洢�������" << endl;
        exit(1);
    }
    for (int i = 0; i <= last; i++)
    {
        data[i] = L.data[i];
    }
    return *this;
};

// �ı��С
template <typename T>
void SeqList<T>::reSize(int newSize)
{
    if (newSize <= 0)
    { // ��Ч�޸�
        cerr << "��Ч�������С" << endl;
        exit(1);
    }
    if (newSize != maxSize)
    { // ��Ч�޸�
        T *newData = new T[newSize];
        if (newData == NULL)
        { // ���·����ڴ�
            cerr << "�洢�������" << endl;
            exit(1);
        }
        int n = last + 1; // Ԫ��ʵ�ʸ���
        T *srcptr = data;
        T *desptr = newData;
        while (n--)
        {
            *desptr++ = *srcptr++;
        }
        delete[] data; // �ͷ�ԭ�ڴ�
        data = newData;
        maxSize = newSize;
    };
};

// ��λ�ڼ���Ԫ�أ���0��ʼ��
template <typename T>
int SeqList<T>::locate(int i) const
{
    if (i >= 0 && i <= last)
    {
        return getData(i);
    }
    else
    {
        return -1;
    }
}

// ȡ��i��Ԫ��ֵ
template <typename T>
bool SeqList<T>::getData(int i, T &x) const
{
    if (locate(i) != -1)
    {
        x = data[i];
        return true;
    }
    else
    {
        return false;
    }
};

//  ����i��Ԫ�ظ�ֵ
template <typename T>
void SeqList<T>::setData(int i, const T &x)
{
    if (locate(i) != -1)
    {
        data[i] = x;
    }
};

// ����Ԫ��
template <typename T>
int SeqList<T>::search(T &x) const
{
    for (int i = 0; i <= last; i++)
    {
        if (data[i] == x)
        {
            return i; // �����±�
        }
    }
    return -1;
}

// ����
template <typename T>
bool SeqList<T>::insert(int i, const T &x)
{
    if (i >= maxSize - 1)
    {
        return false;
    }
    if (locate(i) == -1)
    { // Խ��
        return false;
    }
    for (int j = last; j >= i; j--)
    {
        data[j + 1] = data[j]; // ��i���Ԫ����������ƶ�һλ��ע����Ҫ�Ӻ���ǰ���θ�ֵ
    }

    data[i] = x; // ָ��Ԫ�ز���
    ++last;      // Ԫ�ظ���+1
    return true;
}

// ɾ��
template <typename T>
bool SeqList<T>::remove(int i, T &x)
{
    if (last == -1)
    { // ���
        return false;
    }
    if (locate(i) == -1)
    { // Խ��
        return false;
    }
    x = data[i];
    for (int j = i; j <= last; j++)
    { // ��i���Ԫ��������ǰ�ƶ�һλ��ע����Ҫ��ǰ�������θ�ֵ
        data[j] = data[j + 1];
    }
    --last; // Ԫ�ظ���-1
    return true;
}

// ����Ԫ��
template <typename T>
void SeqList<T>::input()
{
    cout << "��ʼ����˳���������Ҫ�����Ԫ��������������Ԫ�أ�" << endl;
    while (1)
    {
        cin >> last;
        if (last < maxSize)
        {
            break;
        }
        cout << "�����������㣬����������" << endl;
    }
    for (int i = 0; i < last; i++)
    {
        cin >> data[i];
    }
    --last; // Ԫ�ظ������±����ֵ���1
}

// ���Ԫ��
template <typename T>
void SeqList<T>::output()
{
    for (int i = 0; i <= last; i++) // ��ʽ�����
    {
        if (i != 0)
        {
            cout << " ";
        }
        cout << data[i];
    }
    cout << endl;
}

// ����
template <typename T>
void SeqList<T>::sort() // �������к���
{
    std::sort(data, data + last + 1);
}
