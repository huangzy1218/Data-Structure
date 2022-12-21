#include "../LinearList.h"

template <class T>
class SeqList : public LinearList<T>
{
public:
    SeqList(int = defaultSize);                          // 构造函数
    SeqList<T> &operator=(const SeqList<T> &);           // 重载函数：赋值
    SeqList(SeqList<T> &);                               // 复制构造
    ~SeqList() { delete[] data; }                        // 析构函数
    bool insert(int i, const T &x);                      // 插入
    bool remove(int i, T &x);                            // 删除
    int search(T &x) const;                              // 搜索
    int locate(int i) const;                             // 定位
    void sort();                                         // 排序
    bool getData(int i, T &x) const;                     // 取值
    void setData(int i, const T &x);                     // 赋值
    int size() const { return maxSize; }                 // 求表最大空间
    int length() const { return last + 1; }              // 求表长度
    bool isEmpty() const { return last == -1; };         // 判表空
    bool isFull() const { return last == maxSize - 1; }; // 判表满
    void input();                                        // 输入
    void output();                                       // 输出
protected:
    T *data;          // 数据
    int maxSize;      // 表最大空间
    int last;         // 表尾
    void reSize(int); // 改变大小
};

// 构造函数
template <typename T>
SeqList<T>::SeqList(int sz)
{
    if (sz > 0)
    {
        maxSize = sz; // 更新最大空间
        last = -1;    // 表尾位置为-1
    }
    data = new T[maxSize];
    if (data == NULL)
    { // 内存分配失败
        cerr << "存储分配错误" << endl;
        exit(1);
    }
};

// 复制构造函数
template <typename T>
SeqList<T>::SeqList(SeqList<T> &L)
{
    maxSize = L.maxSize;
    last = L.last;
    data = new T[maxSize];
    if (data == NULL)
    {
        cerr << "存储分配错误" << endl;
        exit(1);
    }
    for (int i = 0; i <= last; i++)
    {
        data[i] = L.data[i]; // 依次赋值
    }
};

// 赋值运算符重载
template <typename T>
SeqList<T> &SeqList<T>::operator=(const SeqList<T> &L)
{
    // 防止自我赋值
    if (this == &L)
    {
        return *this;
    }
    delete[] data; // 释放原空间
    maxSize = L.maxSize;
    last = L.last;
    data = new T[maxSize];
    if (data == NULL)
    {
        cerr << "存储分配错误" << endl;
        exit(1);
    }
    for (int i = 0; i <= last; i++)
    {
        data[i] = L.data[i];
    }
    return *this;
};

// 改变大小
template <typename T>
void SeqList<T>::reSize(int newSize)
{
    if (newSize <= 0)
    { // 无效修改
        cerr << "无效的数组大小" << endl;
        exit(1);
    }
    if (newSize != maxSize)
    { // 有效修改
        T *newData = new T[newSize];
        if (newData == NULL)
        { // 重新分配内存
            cerr << "存储分配错误" << endl;
            exit(1);
        }
        int n = last + 1; // 元素实际个数
        T *srcptr = data;
        T *desptr = newData;
        while (n--)
        {
            *desptr++ = *srcptr++;
        }
        delete[] data; // 释放原内存
        data = newData;
        maxSize = newSize;
    };
};

// 定位第几个元素（从0开始）
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

// 取第i个元素值
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

//  给第i个元素赋值
template <typename T>
void SeqList<T>::setData(int i, const T &x)
{
    if (locate(i) != -1)
    {
        data[i] = x;
    }
};

// 查找元素
template <typename T>
int SeqList<T>::search(T &x) const
{
    for (int i = 0; i <= last; i++)
    {
        if (data[i] == x)
        {
            return i; // 返回下标
        }
    }
    return -1;
}

// 插入
template <typename T>
bool SeqList<T>::insert(int i, const T &x)
{
    if (i >= maxSize - 1)
    {
        return false;
    }
    if (locate(i) == -1)
    { // 越界
        return false;
    }
    for (int j = last; j >= i; j--)
    {
        data[j + 1] = data[j]; // 将i后的元素依次向后移动一位，注意需要从后往前依次赋值
    }

    data[i] = x; // 指定元素插入
    ++last;      // 元素个数+1
    return true;
}

// 删除
template <typename T>
bool SeqList<T>::remove(int i, T &x)
{
    if (last == -1)
    { // 表空
        return false;
    }
    if (locate(i) == -1)
    { // 越界
        return false;
    }
    x = data[i];
    for (int j = i; j <= last; j++)
    { // 将i后的元素依次向前移动一位，注意需要从前往后依次赋值
        data[j] = data[j + 1];
    }
    --last; // 元素个数-1
    return true;
}

// 输入元素
template <typename T>
void SeqList<T>::input()
{
    cout << "开始创建顺序表，请输入要插入的元素数并依次输入元素：" << endl;
    while (1)
    {
        cin >> last;
        if (last < maxSize)
        {
            break;
        }
        cout << "数组容量不足，请重新输入" << endl;
    }
    for (int i = 0; i < last; i++)
    {
        cin >> data[i];
    }
    --last; // 元素个数与下标最大值相差1
}

// 输出元素
template <typename T>
void SeqList<T>::output()
{
    for (int i = 0; i <= last; i++) // 格式化输出
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
template <typename T>
void SeqList<T>::sort() // 利用已有函数
{
    std::sort(data, data + last + 1);
}
