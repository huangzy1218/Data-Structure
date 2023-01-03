#include <cstring>
#include <iostream>
const int defaultSize = 100 + 5;
using namespace std;
class String {
public:
    String(int sz = defaultSize); // 构造函数
    String(const char* init); // 构造函数
    String(const String& ob); // 拷贝构造函数
    ~String() { delete[] ch; } // 析构函数
    int length() const { return curLength; } // 获取长度
    String operator()(int pos, int len); // 截取从pos开始长度为len的字符串
    int operator==(String& ob) const // 判断串是否相等
    {
        return strcmp(ch, ob.ch) == 0;
    }
    int operator!=(String& ob) const // 判断串是否不等
    {
        return strcmp(ch, ob.ch) != 0;
    }
    int operator!() const { return curLength == 0; } // 判断是否为空串
    String& operator=(const String& ob); // 赋值运算符重载
    String& operator+=(const String& ob); // 字符串拼接
    char& operator[](int i); // 取第i个字符
    int find(String& pat) const; // 若pat与this中某个子串匹配。返回第一次出现的位置
    friend ostream& operator<<(ostream& os, String& s); // 输出运算符重载
    friend istream& operator>>(istream& is, String& s); // 输入运算符重载

private:
    char* ch;
    int curLength;
    int maxSize;
    void bulidNext(int n);
};

// 构造函数
String::String(int sz)
{
    maxSize = sz;
    ch = new char[maxSize + 1]; // 为'\0'预留空间
    if (ch == NULL) {
        cerr << "内存分配失败" << endl;
        exit(1);
    }
    curLength = 0;
    ch[0] = '\0';
};

// 构造函数
String::String(const char* init)
{
    int len = strlen(init);
    maxSize = (len > defaultSize) ? len : defaultSize;
    ch = new char[maxSize + 1];
    if (ch == NULL) {
        cerr << "内存分配失败" << endl;
        exit(1);
    }
    curLength = len;
    strcpy(ch, init);
};

// 复制构造函数
String::String(const String& ob)
{
    maxSize = ob.maxSize;
    ch = new char[maxSize + 1];
    if (ch == NULL) {
        cerr << "内存分配失败" << endl;
        exit(1);
    }
    curLength = ob.curLength;
    strcpy(ch, ob.ch);
};

// 求子串
String String::operator()(int pos, int len)
{
    String temp;
    if (pos < 0 || pos + len - 1 >= maxSize || len < 0) {
        temp.curLength = 0;
        temp.ch[0] = '\0';
    } else {
        if (pos + len - 1 >= curLength)
            len = curLength - pos;
        temp.curLength = len;
        for (int i = 0, j = pos; i < len; i++, j++) {
            temp.ch[i] = ch[j];
        }
    }
    return temp;
};

// 赋值运算符重载
String& String::operator=(const String& ob)
{
    if (&ob != this) {
        delete[] ch;
        ch = new char[ob.maxSize];
        if (ch == NULL) {
            cerr << "内存分配失败" << endl;
            exit(1);
        }
        strcpy(ch, ob.ch);
        curLength = ob.curLength;
        maxSize = ob.maxSize;
    }
    return *this;
};

// 字符串连接
String& String::operator+=(const String& ob)
{
    char* temp = ch;
    int n = curLength + ob.curLength;
    int m = (maxSize >= n) ? maxSize : n;
    ch = new char[m];
    if (ch == NULL) {
        cerr << "内存分配异常" << endl;
        exit(1);
    }
    maxSize = m;
    curLength = n;
    strcpy(ch, temp);
    strcat(ch, ob.ch);
    delete[] temp;
    return *this;
};

// []运算符重载：取第i个yuansu
char& String::operator[](int i)
{
    if (i < 0 || i >= curLength) {
        cout << "下标越界" << endl;
    }
    return ch[i];
};

// 若pat与this中某个子串匹配。返回第一次出现的位置
// KMP算法：最长（小于子串长度）公共前后缀，使前缀来到后缀的位置
int String::find(String& pat) const
{
    int* next = new int[pat.curLength];
    int i, j, k = 0;
    int prefix_len = 0; // 当前公共前缀的长度
    i = 1;
    while (i < pat.curLength) {
        if (pat[prefix_len] == pat[i]) {
            prefix_len++;
            next[k++] = prefix_len;
            i++;
        } else {
            if (prefix_len == 0) {
                next[k++] = 0;
                i++;
            } else {
                prefix_len = next[prefix_len - 1];
            }
        }
    }
    i = 0, j = 0;
    for (i = 0; i < curLength; i++) {
        if (ch[i] == pat[j]) {
            j++;
        } else if (j > 0) {
            j = next[j - 1];
        } else {
            continue;
        }
        if (j == pat.curLength) {
            return i - j + 1;
        }
    }
    delete[] next;
    return -1;
};

// 输出运算符重载
ostream& operator<<(ostream& os, String& s)
{
    os << s.ch;
    return os;
};

// 输入运算符重载
istream& operator>>(istream& is, String& s)
{
    cout << "请输入字符串：" << endl;
    is >> s.ch;
    s.curLength = strlen(s.ch);
    return is;
};