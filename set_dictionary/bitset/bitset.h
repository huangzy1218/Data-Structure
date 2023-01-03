#include <cassert>
#include <iostream>
using namespace std;

const int defaultSize = 50;
template <class T>
class BitSet;
template <class T>
istream& operator>>(istream& in, BitSet<T>& r); // 输入
template <class T>
ostream& operator<<(ostream& in, BitSet<T>& r); // 输出
template <class T>
class BitSet {
public:
    BitSet(int sz = defaultSize); // 构造函数
    BitSet(const BitSet<T>& r); // 复制构造函数
    ~BitSet() { delete[] bitVector; } // 析构函数
    void makeEmpty() // 置空集合
    {
        for (int i = 0; i < vectorSize; i++)
            bitVector[i] = 0;
    }
    unsigned short getMember(const T& x); // 读取集合元素 x
    void putMember(const T x, unsigned short v); // 将值 v 送入集合元素 x
    bool addMember(const T x); // 加入 x
    bool deleteMember(const T x); // 删除 x
    BitSet<T>& operator=(const BitSet<T>& r); // 赋值
    BitSet<T> operator+(const BitSet<T>& r); // 并操作
    BitSet<T> operator*(const BitSet<T>& r); // 交操作
    BitSet<T> operator-(const BitSet<T>& r); // 差操作
    bool contains(const T x); // 判断是否含有元素 x
    bool subSet(BitSet<T>& r); // 判断是否为子集
    bool operator==(const BitSet<T>& r); // 判断集合是否相等
    template <class U>
    friend istream& operator>>(istream& in, BitSet<U>& r); // 输入
    template <class U>
    friend ostream& operator<<(ostream& out, BitSet<T>& r); // 输出
    int size() const { return setSize; }

private:
    int setSize; // 集合大小
    int vectorSize; // 位数组大小
    unsigned short* bitVector; // 存储集合元素的数组
};

// 构造函数
template <class T>
BitSet<T>::BitSet(int sz)
    : setSize(sz)
{
    assert(setSize > 0);
    vectorSize = (setSize + 15) >> 4; // 检查参数合理性
    bitVector = new unsigned short[vectorSize];
    assert(bitVector != NULL);
    for (int i = 0; i < vectorSize; i++) // 初始化
        bitVector[i] = 0;
};

// 复制构造函数
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

// 赋值运算符重载
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

// 读取集合元素 x, x 从 0 开始
template <class T>
unsigned short BitSet<T>::getMember(const T& x)
{
    int ad = x / 16, id = x % 16; // 计算元素下标
    unsigned short elem = bitVector[ad]; // 取 x 所在的数组元素
    return ((elem >> (15 - id)) % 2); // 取第 id 位的值
};

// 将值 v 送入集合元素 x
template <class T>
void BitSet<T>::putMember(const T x, unsigned short v)
{
    int ad = x / 16, id = x % 16;
    unsigned short elem = bitVector[ad];
    unsigned short temp = elem >> (15 - id);
    elem = elem << (id + 1);
    if (temp % 2 == 0 && v == 1) {
        temp = temp + 1; // 该位置为 1
    } else if (temp % 2 == 1 && v == 0) {
        temp = temp - 1; // 该位置为 0
    }
    bitVector[ad] = (temp << (15 - id)) | (elem >> (id + 1)); // 送回
};

// 添加
template <class T>
bool BitSet<T>::addMember(const T x)
{
    assert(x >= 0 && x < setSize); // 检查 x 的合理性
    if (getMember(x) == 0) {
        putMember(x, 1); // 1 表示在集合
        return true;
    }
    return false;
};

// 删除
template <class T>
bool BitSet<T>::deleteMember(const T x)
{
    assert(x >= 0 && x < setSize); // 检查 x 的合理性
    if (getMember(x) == 1) {
        putMember(x, 0); // 0 表示不在集合
        return true;
    }
    return false;
};

// 并操作
template <class T>
BitSet<T> BitSet<T>::operator+(const BitSet<T>& r)
{
    assert(vectorSize == r.vectorSize); // 两集合大小相等
    BitSet<T> temp(setSize);
    for (int i = 0; i < vectorSize; i++) {
        temp.bitVector[i] = bitVector[i] | r.bitVector[i];
    }
    return temp;
};

// 交操作
template <class T>
BitSet<T> BitSet<T>::operator*(const BitSet<T>& r)
{
    assert(vectorSize == r.vectorSize); // 两集合大小相等
    BitSet<T> temp(setSize);
    for (int i = 0; i < vectorSize; i++) {
        temp.bitVector[i] = bitVector[i] & r.bitVector[i];
    }
    return temp;
};

// 差操作
template <class T>
BitSet<T> BitSet<T>::operator-(const BitSet<T>& r)
{
    assert(vectorSize == r.vectorSize); // 两集合大小相等
    BitSet<T> temp(setSize);
    for (int i = 0; i < vectorSize; i++) {
        temp.bitVector[i] = bitVector[i] & !r.bitVector[i];
    }
    return temp;
};

// 判断是否含有元素 x
template <class T>
bool BitSet<T>::contains(const T x)
{
    assert(x >= 0 && x <= setSize);
    return (getMember(x) == 1) ? true : false;
};

// 判断是否为子集
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

// 判断集合是否相等
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

// 输入
template <class T>
istream& operator>>(istream& in, BitSet<T>& r)
{
    int n;
    T member;
    cout << "开始创建位图，请输入元素个数并依次输入集合元素：" << endl;
    in >> n;
    for (int i = 0; i < n; i++) {
        in >> member;
        r.addMember(member);
    }
    return in;
};

// 输出
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