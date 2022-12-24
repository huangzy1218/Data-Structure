#include <algorithm>
#include <iostream>
using namespace std;
const int defaultSize = 100;
template <class T>
class LinearList {
public:
    LinearList() { } // 构造函数
    ~LinearList() { } // 析构函数
    virtual bool insert(int i, const T& x) = 0; // 插入
    virtual bool remove(int i, T& x) = 0; // 删除
    virtual int search(T& x) const = 0; // 查找
    virtual int locate(int i) const = 0; // 定位
    virtual void sort() = 0; // 排序
    virtual bool getData(int i, T& x) const = 0; // 获取指定位元素值
    virtual void setData(int i, const T& x) = 0; // 设置指定位元素值
    virtual int size() const = 0; // 获取大小
    virtual int length() const = 0; // 获取长度
    virtual bool isEmpty() const = 0; // 判空
    virtual bool isFull() const = 0; // 判满
    virtual void input() = 0; // 输入
    virtual void output() = 0; // 输出
};