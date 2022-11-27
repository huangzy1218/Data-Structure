#include <iostream>
#include <algorithm>

using namespace std;
const int defaultSize = 100;
template <class T>
class LinearList {
public:
    LinearList() {}                                 // 构造函数
    LinearList(LinearList<T>& L);                   // 复制构造函数
    ~LinearList() {}                                // 析构函数
    virtual bool Insert(int i, const T& x) = 0;     // 插入
    virtual bool Remove(int i) = 0;                 // 删除
    virtual int Search(T& x) const = 0;             // 搜索
    virtual int Locate(int i) const = 0;            // 定位
    virtual void Sort() = 0;                        // 排序
    virtual bool GetData(int i, T& x) const = 0;    // 取值
    virtual void SetData(int i, T& x) = 0;          // 赋值
    virtual int Size() const = 0;                   // 求表最大空间
    virtual int Length() const = 0;                 // 求表长度
    virtual bool IsEmpty() const = 0;               // 判表空
    virtual bool IsFull() const = 0;                // 判表满
    virtual void Input() = 0;                       // 输入
    virtual void Output() = 0;                      // 输出
};

