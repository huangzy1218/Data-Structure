#include <cstdlib>
#include <iostream>
const int defaultSize = 100;
using namespace std;
template <class T>
class SparseMatrix;
template <class T>
ostream& operator<<(ostream& out, SparseMatrix<T>& x);
template <class T>
istream& operator<<(istream& out, SparseMatrix<T>& x);

template <class T>
struct Trituple // 三元组
{
    int row, col;
    T value;
    Trituple<T>& operator=(Trituple<T>& x)
    {
        if (this == &x) {
            return *this;
        }
        row = x.row;
        col = x.col;
        value = x.value;
        return *this;
    }
};

template <class T>
class SparseMatrix {
    template <class U>
    friend ostream& operator<<(ostream& out, SparseMatrix<U>& x); // 友元函数：输出运算符重载
    template <class U>
    friend istream& operator>>(istream* in, SparseMatrix<U>& x); // 友元函数：输入运算符重载
public:
    SparseMatrix(int sz = defaultSize); // 构造函数
    SparseMatrix(int rows, int cols, int sz = defaultSize); // 构造函数
    SparseMatrix(const SparseMatrix<T>& x); // 复制构造函数
    ~SparseMatrix() { delete[] smArray; } // 析构函数
    SparseMatrix<T>& operator=(const SparseMatrix<T>& s); // 赋值运算符重载
    SparseMatrix<T> transpose(); // 对当前对象进行转置操作
    SparseMatrix<T> add(SparseMatrix<T>& s); // 当前矩阵与s相加
    SparseMatrix<T> multiply(SparseMatrix<T>& s); // 当前矩阵与s相乘
    int rows, cols, terms;
    Trituple<T>* smArray;
    int maxTerms;
};

// 构造函数
template <class T>
SparseMatrix<T>::SparseMatrix(int sz)
    : maxTerms(sz)
{
    if (maxTerms < 1) {
        cerr << "矩阵初始化错误" << endl;
        exit(1);
    }
    smArray = new Trituple<T>[maxTerms];
    if (smArray == NULL) {
        cerr << "内存分配错误" << endl;
        exit(1);
    }
    rows = cols = terms = 0;
};

// 构造函数
template <class T>
SparseMatrix<T>::SparseMatrix(int r, int c, int sz)
    : maxTerms(sz)
{
    if (maxTerms < 1) {
        cerr << "矩阵初始化错误" << endl;
        exit(1);
    }
    smArray = new Trituple<T>[maxTerms];
    if (smArray == NULL) {
        cerr << "内存分配错误" << endl;
        exit(1);
    }
    rows = r;
    cols = c;
    terms = 0;
}

// 拷贝构造函数
template <class T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T>& s)
{
    rows = s.rows;
    cols = s.cols;
    terms = s.terms;
    maxTerms = s.terms;
    smArray = new Trituple<T>[maxTerms];
    if (smArray == NULL) {
        cerr << "内存分配错误" << endl;
        exit(1);
    }
    for (int i = 0; i < terms; i++) {
        smArray[i] = s.smArray[i];
    }
};

// 输出运算符重载
template <class T>
ostream& operator<<(ostream& out, SparseMatrix<T>& s)
{
    out << "行数：" << s.rows << endl;
    out << "列数：" << s.cols << endl;
    out << "非零元素个数：" << s.terms << endl;
    for (int i = 0; i < s.terms; i++) {
        out << "M[" << s.smArray[i].row << "][" << s.smArray[i].col
            << "] = " << s.smArray[i].value << endl;
    }
    return out;
};

// 输入运算符重载
template <class T>
istream& operator>>(istream& is, SparseMatrix<T>& s)
{
    cout << "请输入矩阵的行数，列数及元素个数" << endl;
    is >> s.rows >> s.cols >> s.terms;
    if (s.terms > defaultSize) {
        cerr << "栈溢出" << endl;
        exit(1);
    }
    for (int i = 0; i < s.terms; i++) {
        cout << "请输入元素行号，列号及元素值：" << endl;
        is >> s.smArray[i].row >> s.smArray[i].col >> s.smArray[i].value;
    }
    return is;
};

// 赋值运算符重载
template <class T>
SparseMatrix<T>& SparseMatrix<T>::operator=(const SparseMatrix<T>& s)
{
    if (&s == this) {
        return *this;
    }
    rows = s.rows;
    cols = s.cols;
    terms = s.terms;
    maxTerms = s.terms;
    smArray = new Trituple<T>[maxTerms];
    if (smArray == NULL) {
        cerr << "内存分配错误" << endl;
        exit(1);
    }
    for (int i = 0; i < terms; i++) {
        smArray[i] = s.smArray[i];
    }
    return *this;
};

// 转置
template <class T>
SparseMatrix<T> SparseMatrix<T>::transpose()
{
    int* rowSize = new int[cols];
    int* rowStart = new int[cols];
    SparseMatrix<T> b(maxTerms);
    b.terms = terms;
    b.rows = cols;
    b.cols = rows;
    if (terms > 0) {
        int i, j;
        for (i = 0; i < cols; i++) {
            rowSize[i] = 0;
        }
        for (i = 0; i < terms; i++) {
            rowSize[smArray[i].col]++; // 记录现在每行（原先每列）的元素个数
        }
        rowStart[0] = 0;
        for (int i = 1; i < cols; i++) {
            rowStart[i] = rowSize[i - 1] + rowStart[i - 1]; // 计算现每行的起始位置
        }
        for (i = 0; i < terms; i++) {
            j = rowStart[smArray[i].col];
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++; // 寻找本行的下个元素
        }
    }
    delete[] rowSize;
    delete[] rowStart;
    return b;
};

// 当前矩阵与s相加
template <class T>
SparseMatrix<T> SparseMatrix<T>::add(SparseMatrix<T>& b)
{
    SparseMatrix<T> result(rows, cols);
    if (rows != b.rows || cols != b.cols) {
        cout << "不匹配的矩阵" << endl;
        return result;
    }
    int i = 0, j = 0, indexA, indexB;
    result.terms = 0;
    while (i < terms && j < b.terms) {
        indexA = cols * smArray[i].row + smArray[i].col;
        indexB = cols * b.smArray[j].row + b.smArray[j].col;
        if (indexA < indexB) // smArray[i]在b.smArray[j]前
        {
            result.smArray[result.terms] = smArray[i];
            i++;
        } else if (indexA > indexB) // smArray[i]在b.smArray[j]后
        {
            result.smArray[result.terms] = b.smArray[i];
            j++;
        } else // smArray[i]和b.smArray[j]在相同位置
        {
            result.smArray[result.terms] = smArray[i];
            result.smArray[result.terms].value = smArray[i].value + b.smArray[j].value;
            i++;
            j++;
        }
        result.terms++; // 稀疏矩阵元素个数+1
    }
    // 复制其余元素
    for (; i < terms; i++) {
        result.smArray[result.terms] = smArray[i];
        result.terms++;
    }
    for (; j < b.terms; j++) {
        result.smArray[result.terms] = b.smArray[j];
        result.terms++;
    }
    return result;
};

// 当前矩阵与s相乘
template <class T>
SparseMatrix<T> SparseMatrix<T>::multiply(SparseMatrix<T>& b)
{
    SparseMatrix<T> result(rows, b.cols);
    if (cols != b.rows) // A列数与B行数不等
    {
        cout << "矩阵不匹配" << endl;
        return result;
    }
    int* rowSize = new int[b.rows]; // B每行非零元素个数
    int* rowStart = new int[b.rows]; // B每行非零元素起始下标
    T* temp = new T[b.cols]; // 暂存每行的计算结果
    int i, current, lastInResult, rowA, colA, colB;
    for (i = 0; i < b.rows; i++) {
        rowSize[i] = 0;
    }
    for (i = 0; i < b.terms; i++) {
        rowSize[b.smArray[i].row]++;
    }
    rowStart[i] = 0;
    for (i = 1; i < b.rows; i++) {
        rowStart[i] = rowSize[i - 1] + rowStart[i - 1];
    }
    current = 0, lastInResult = -1;
    while (current < terms) {
        rowA = smArray[current].row;
        for (int i = 0; i < b.cols; i++) {
            temp[i] = 0;
        }
        while (current < terms && smArray[current].row == rowA) {
            colA = smArray[current].col;
            for (i = rowStart[colA]; i < rowStart[colA + 1]; i++) // 遍历B在第rowB行的元素
            {
                colB = b.smArray[i].col;
                temp[colB] += smArray[current].value * b.smArray[i].value;
            }
            current++;
        }
        for (i = 0; i < b.cols; i++) {
            if (temp[i] != 0) {
                lastInResult++;
                result.smArray[lastInResult].row = rowA;
                result.smArray[lastInResult].col = i;
                result.smArray[lastInResult].value = temp[i];
            }
        }
    }
    result.rows = rows;
    result.cols = b.cols;
    result.terms = lastInResult + 1;
    delete[] rowStart;
    delete[] rowSize;
    return result;
};