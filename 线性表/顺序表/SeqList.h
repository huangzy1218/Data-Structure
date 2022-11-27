#include "LinearList.h"

template<class T>
class SeqList: public LinearList<T> {
public:
    SeqList(int = defaultSize);               // 构造函数
    SeqList<T>& operator=(const SeqList<T>&); // 重载函数：赋值
    SeqList(SeqList<T>&);                     // 复制构造
    ~SeqList();                               // 析构函数
    bool Insert(int i, const T& x);           // 插入
    bool Remove(int i);                       // 删除
    int Search(T& x) const;                   // 搜索
    int Locate(int i) const;                  // 定位
    void Sort();                              // 排序
    bool GetData(int i, T& x) const;          // 取值
    void SetData(int i, T& x);                // 赋值
    int Size() const;                         // 求表最大空间
    int Length() const;                       // 求表长度
    bool IsEmpty() const;                     // 判表空
    bool IsFull() const;                      // 判表满
    void Input();                             // 输入
    void Output();                            // 输出 
protected:
    T* data;                                  // 数据
    int MaxSize;                              // 表最大空间
    int last;                                 // 表尾
    void ReSize(int);                         // 改变大小
};

// 构造函数
template<typename T>
SeqList<T>::SeqList(int sz)
{
    if (sz > 0) {
        MaxSize = sz;                           // 更新最大空间
        last = -1;                              // 表尾位置为-1
    }
    data = new T[MaxSize];  
    if (data == NULL) {                         // 内存分配失败
        cerr << "存储分配错误" << endl;
        exit(1);
    }
}

// 复制构造函数
template<typename T>
SeqList<T>::SeqList(SeqList<T>& L)
{
    MaxSize = L.MaxSize;   
    last = L.last;
    data = new T[MaxSize];
    if (data == NULL) {
        cerr << "存储分配错误" << endl;
        exit(1);
    }
    for (int i = 0; i <= last; i++) {
        data[i] = L.data[i];                    // 依次赋值
    }
}

// 赋值运算符重载
template<typename T>
SeqList<T>& SeqList<T>::operator=(const SeqList<T>& L)
{
    // 防止自我赋值
    if (this == &L) {
        return *this;
    }
    delete[] data;                              // 释放原空间
        MaxSize = L.MaxSize;
    last = L.last;
    data = new T[MaxSize];
    if (data == NULL) {
        cerr << "存储分配错误" << endl;
        exit(1);
    }
    for (int i = 0; i <= last; i++) {
        data[i] = L.data[i];
    }
}

// 改变大小
template<typename T>
void SeqList<T>::ReSize(int newSize)
{
    if (newSize <= 0) {  // 无效修改
        cerr << "无效的数组大小" << endl;
        exit(1);
    }
    if (newSize != MaxSize) {                   // 有效修改
        T* newData = new T[newSize];
        if (newData == NULL) {                  // 重新分配内存
            cerr << "存储分配错误" << endl;
            exit(1);
        }
        int n = last + 1;                       // 元素实际个数 
        T* srcptr = data;
        T* desptr = newData;
        while (n--) {
            *desptr++ = *srcptr++;
        }
        delete [] data;                        // 释放原内存
        data = newData;   
        MaxSize = newSize;
    }
}

// 析构函数
template<typename T>
SeqList<T>::~SeqList()
{
    delete[] data;
}

// 判空
template<typename T>
bool SeqList<T>::IsEmpty() const
{
    return last == -1;
}

// 判满
template<typename T>
bool SeqList<T>::IsFull() const 
{
    return last == MaxSize - 1;
}

// 获取最大空间
template<typename T>
int SeqList<T>::Size() const
{
    return MaxSize;
}

// 获取表长
template<typename T>
int SeqList<T>::Length() const
{
    return last + 1;
}

// 定位第几个元素（从1开始）
template<typename T>
int SeqList<T>::Locate(int i) const
{
    if (i >= 1 && i <= last + 1) {
        return i;
    } else {
        return 0;
    }
}

// 取第i个元素值
template<typename T>
bool SeqList<T>::GetData(int i, T& x) const
{
    if (Locate(i)) {
        x = data[i-1];  
        return true;
    } else {
        return false;
    }
}

//  给第i个元素赋值
template<typename T>
void SeqList<T>::SetData(int i, T& x)
{
    if (Locate(i)) {
        data[i-1] = x;
    }
}

// 查找元素
template<typename T>
int SeqList<T>::Search(T & x) const
{
    for (int i = 0; i <= last; i++) {
        if (data[i] == x) {
            return i + 1;                        // 下标与元素位置相差1                  
        }
    }
    return 0;
}


// 插入
template<typename T>
bool SeqList<T>::Insert(int i, const T& x)
{
    if (i == MaxSize - 1) {
        return false;
    }
    if (!Locate(i)) {                           // 越界
        return false;
    }
    for (int j = last; j >= i - 1; j--) {
        data[j+1] = data[j];                    // 将i后的元素依次向后移动一位，注意需要从后往前依次赋值
    }
    
    data[i-1] = x;                             // 指定元素插入
    ++last;                                    // 元素个数+1
    return true;
}


// 删除
template<typename T>
bool SeqList<T>::Remove(int i)
{
    if (last == -1) {                          // 表空
        return false;
    }
    if (!Locate(i)) {                         // 越界
        return false;
    }
    for (int j = i - 1; j < last; j++) {      // 将i后的元素依次向前移动一位，注意需要从前往后依次赋值
        data[j] = data[j+1];
    }
    --last;                                   // 元素个数-1
    return true;
}


// 输入元素
template<typename T>
void SeqList<T>::Input()
{
    cout << "Start to create a sequence table. Please enter the number of elements in the table" << endl;
    while (1) {
        cin >> last;
        if (last < MaxSize) {
            break;
        }
        cout << "The number of entries is incorrect, and the range cannot exceed" << MaxSize - 1 << endl;
    }
    for (int i = 0; i < last; i++) {
        cin >> data[i];
    }
    --last;                                 // 元素个数与下标最大值相差1
}

// 输出元素
template<typename T>
void SeqList<T>::Output()
{
   for (int i = 0; i <= last; i++)           // 格式化输出
   {
       if (i != 0)
       {
           cout << " ";
       }
       cout << data[i];
   }
   cout << endl;
}

// 排序
template<typename T>
void SeqList<T>::Sort()                     // 利用已有函数
{
   std::sort(data, data + last);
}
