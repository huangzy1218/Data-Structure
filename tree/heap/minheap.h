#include <iostream>
#include <queue>
using namespace std;
const int defaultSize = 10;
template <class T>
class MinHeap : public priority_queue<T>
{
public:
    MinHeap(int sz = defaultSize); // ���캯��������ն�
    MinHeap(T arr[], int n);       // ͨ�����齨����
    ~MinHeap() { delete[] heap; }  // ��������
    bool insert(const T &x);       // ��x������С��
    bool removeMin(T &x);          // ɾ���Ѷ�����СԪ��
    bool isEmpty() const           // �п�
    {
        return currentSize == 0;
    }
    bool isFull() const // ����
    {
        return currentSize == maxHeapSize;
    }
    void makeEmpty() // �ÿն�
    {
        currentSize = 0;
    }

private:
    T *heap;                         // �����С����Ԫ�ص�����
    int currentSize;                 // ��С���е�ǰԪ�ظ���
    int maxHeapSize;                 // ��С���������Ԫ�ظ���
    void siftDown(int start, int m); // ��start��m�»�����Ϊ��С��
    void siftUp(int start);          // ��start��0�ϻ�����Ϊ��С��
};

// ���캯��������ն�
template <class T>
MinHeap<T>::MinHeap(int sz)
{
    maxHeapSize = (defaultSize < sz) ? sz : defaultSize;
    heap = new T[maxHeapSize];
    if (heap == NULL)
    {
        cerr << "���ڴ����ʧ��" << endl;
        exit(1);
    }
    currentSize = 0;
};

// // ͨ�����齨����
template <class T>
MinHeap<T>::MinHeap(T arr[], int n)
{
    maxHeapSize = (defaultSize < n) ? n : defaultSize;
    heap = new T[maxHeapSize];
    if (heap == NULL)
    {
        cerr << "���ڴ����ʧ��" << endl;
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        heap[i] = arr[i]; // ���ƶ�����
    }
    currentSize = n;
    int currentPos = (currentSize - 2) / 2; // Ѱ���������λ��
    while (currentPos >= 0)                 // �Ե����������γɶ�
    {
        siftDown(currentPos, currentSize - 1);
        currentPos--;
    }
};

// ��start��m�»�����Ϊ��С��
template <class T>
void MinHeap<T>::siftDown(int start, int m)
{
    int i = start, j = 2 * i + 1;
    T temp = heap[i];
    while (j <= m)
    {
        if (j < m && heap[j] > heap[j + 1]) // jָ������Ů��С��
        {
            j++;
        }
        if (temp <= heap[j]) // �����С�ڽ�С�ߣ���������
        {
            break;
        }
        else
        {
            heap[i] = heap[j]; // С������
            i = j;             // �Ե������ӽڵ������������i,j�½�
            j = 2 * j + 1;
        }
    }
    heap[i] = temp; // �ط�temp�ݴ��Ԫ��
};

// ��start��0�ϻ�����Ϊ��С��
template <class T>
void MinHeap<T>::siftUp(int start)
{
    int j = start, i = (j - 1) >> 1;
    T temp = heap[i];
    while (j > 0) // �ظ�·��ֱ����
    {
        if (heap[i] <= temp) // �����ֵС��������
        {
            break;
        }
        else // �����ֵ�󣬵���
        {
            heap[j] = heap[i];
            j = i;
            i = (i - 1) >> 1;
        }
    }
    heap[j] = temp; // �ط�temp�ݴ��Ԫ��
};

// ��x������С��
template <class T>
bool MinHeap<T>::insert(const T &x)
{
    if (isFull())
    {
        cerr << "����" << endl;
        return false;
    }
    heap[currentSize] = x; // ����
    siftUp(currentSize);   // ���ϵ���
    currentSize++;         // �Ѽ���+1
    return true;
};

// ɾ���Ѷ�����СԪ��
template <class T>
bool MinHeap<T>::removeMin(T &x)
{
    if (!currentSize)
    {
        cerr << "�ѿ�" << endl;
        return false;
    }
    x = heap[0];
    heap[0] = heap[currentSize - 1]; // ����Ԫ�ز������ڵ�
    --currentSize;
    siftDown(0, currentSize - 1); // �������µ���
    return true;
};