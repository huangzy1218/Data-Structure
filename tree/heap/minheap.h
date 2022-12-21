#include <iostream>
#include <queue>
using namespace std;
const int defaultSize = 10;
template <class T>
class MinHeap : public priority_queue<T>
{
public:
    MinHeap(int sz = defaultSize); // 构造函数，构造空堆
    MinHeap(T arr[], int n);       // 通过数组建立堆
    ~MinHeap() { delete[] heap; }  // 析构函数
    bool insert(const T &x);       // 将x插入最小堆
    bool removeMin(T &x);          // 删除堆顶上最小元素
    bool isEmpty() const           // 判空
    {
        return currentSize == 0;
    }
    bool isFull() const // 判满
    {
        return currentSize == maxHeapSize;
    }
    void makeEmpty() // 置空堆
    {
        currentSize = 0;
    }

private:
    T *heap;                         // 存放最小堆中元素的数组
    int currentSize;                 // 最小堆中当前元素个数
    int maxHeapSize;                 // 最小堆最多允许元素个数
    void siftDown(int start, int m); // 从start到m下滑调整为最小堆
    void siftUp(int start);          // 从start到0上滑调整为最小堆
};

// 构造函数，构造空堆
template <class T>
MinHeap<T>::MinHeap(int sz)
{
    maxHeapSize = (defaultSize < sz) ? sz : defaultSize;
    heap = new T[maxHeapSize];
    if (heap == NULL)
    {
        cerr << "堆内存分配失败" << endl;
        exit(1);
    }
    currentSize = 0;
};

// // 通过数组建立堆
template <class T>
MinHeap<T>::MinHeap(T arr[], int n)
{
    maxHeapSize = (defaultSize < n) ? n : defaultSize;
    heap = new T[maxHeapSize];
    if (heap == NULL)
    {
        cerr << "堆内存分配失败" << endl;
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        heap[i] = arr[i]; // 复制堆数组
    }
    currentSize = n;
    int currentPos = (currentSize - 2) / 2; // 寻找最初调整位置
    while (currentPos >= 0)                 // 自底向上扩大形成堆
    {
        siftDown(currentPos, currentSize - 1);
        currentPos--;
    }
};

// 从start到m下滑调整为最小堆
template <class T>
void MinHeap<T>::siftDown(int start, int m)
{
    int i = start, j = 2 * i + 1;
    T temp = heap[i];
    while (j <= m)
    {
        if (j < m && heap[j] > heap[j + 1]) // j指向两子女较小者
        {
            j++;
        }
        if (temp <= heap[j]) // 父结点小于较小者，不做调整
        {
            break;
        }
        else
        {
            heap[i] = heap[j]; // 小者上移
            i = j;             // 对调整后子节点的子树操作，i,j下降
            j = 2 * j + 1;
        }
    }
    heap[i] = temp; // 回放temp暂存的元素
};

// 从start到0上滑调整为最小堆
template <class T>
void MinHeap<T>::siftUp(int start)
{
    int j = start, i = (j - 1) >> 1;
    T temp = heap[i];
    while (j > 0) // 沿父路径直到根
    {
        if (heap[i] <= temp) // 父结点值小，不调整
        {
            break;
        }
        else // 父结点值大，调整
        {
            heap[j] = heap[i];
            j = i;
            i = (i - 1) >> 1;
        }
    }
    heap[j] = temp; // 回放temp暂存的元素
};

// 将x插入最小堆
template <class T>
bool MinHeap<T>::insert(const T &x)
{
    if (isFull())
    {
        cerr << "堆满" << endl;
        return false;
    }
    heap[currentSize] = x; // 插入
    siftUp(currentSize);   // 向上调整
    currentSize++;         // 堆计数+1
    return true;
};

// 删除堆顶上最小元素
template <class T>
bool MinHeap<T>::removeMin(T &x)
{
    if (!currentSize)
    {
        cerr << "堆空" << endl;
        return false;
    }
    x = heap[0];
    heap[0] = heap[currentSize - 1]; // 最后的元素补到根节点
    --currentSize;
    siftDown(0, currentSize - 1); // 自上向下调整
    return true;
};