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
struct Trituple // ��Ԫ��
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
    friend ostream& operator<<(ostream& out, SparseMatrix<U>& x); // ��Ԫ������������������
    template <class U>
    friend istream& operator>>(istream* in, SparseMatrix<U>& x); // ��Ԫ�������������������
public:
    SparseMatrix(int sz = defaultSize); // ���캯��
    SparseMatrix(int rows, int cols, int sz = defaultSize); // ���캯��
    SparseMatrix(const SparseMatrix<T>& x); // ���ƹ��캯��
    ~SparseMatrix() { delete[] smArray; } // ��������
    SparseMatrix<T>& operator=(const SparseMatrix<T>& s); // ��ֵ���������
    SparseMatrix<T> transpose(); // �Ե�ǰ�������ת�ò���
    SparseMatrix<T> add(SparseMatrix<T>& s); // ��ǰ������s���
    SparseMatrix<T> multiply(SparseMatrix<T>& s); // ��ǰ������s���
    int rows, cols, terms;
    Trituple<T>* smArray;
    int maxTerms;
};

// ���캯��
template <class T>
SparseMatrix<T>::SparseMatrix(int sz)
    : maxTerms(sz)
{
    if (maxTerms < 1) {
        cerr << "�����ʼ������" << endl;
        exit(1);
    }
    smArray = new Trituple<T>[maxTerms];
    if (smArray == NULL) {
        cerr << "�ڴ�������" << endl;
        exit(1);
    }
    rows = cols = terms = 0;
};

// ���캯��
template <class T>
SparseMatrix<T>::SparseMatrix(int r, int c, int sz)
    : maxTerms(sz)
{
    if (maxTerms < 1) {
        cerr << "�����ʼ������" << endl;
        exit(1);
    }
    smArray = new Trituple<T>[maxTerms];
    if (smArray == NULL) {
        cerr << "�ڴ�������" << endl;
        exit(1);
    }
    rows = r;
    cols = c;
    terms = 0;
}

// �������캯��
template <class T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T>& s)
{
    rows = s.rows;
    cols = s.cols;
    terms = s.terms;
    maxTerms = s.terms;
    smArray = new Trituple<T>[maxTerms];
    if (smArray == NULL) {
        cerr << "�ڴ�������" << endl;
        exit(1);
    }
    for (int i = 0; i < terms; i++) {
        smArray[i] = s.smArray[i];
    }
};

// ������������
template <class T>
ostream& operator<<(ostream& out, SparseMatrix<T>& s)
{
    out << "������" << s.rows << endl;
    out << "������" << s.cols << endl;
    out << "����Ԫ�ظ�����" << s.terms << endl;
    for (int i = 0; i < s.terms; i++) {
        out << "M[" << s.smArray[i].row << "][" << s.smArray[i].col
            << "] = " << s.smArray[i].value << endl;
    }
    return out;
};

// �������������
template <class T>
istream& operator>>(istream& is, SparseMatrix<T>& s)
{
    cout << "����������������������Ԫ�ظ���" << endl;
    is >> s.rows >> s.cols >> s.terms;
    if (s.terms > defaultSize) {
        cerr << "ջ���" << endl;
        exit(1);
    }
    for (int i = 0; i < s.terms; i++) {
        cout << "������Ԫ���кţ��кż�Ԫ��ֵ��" << endl;
        is >> s.smArray[i].row >> s.smArray[i].col >> s.smArray[i].value;
    }
    return is;
};

// ��ֵ���������
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
        cerr << "�ڴ�������" << endl;
        exit(1);
    }
    for (int i = 0; i < terms; i++) {
        smArray[i] = s.smArray[i];
    }
    return *this;
};

// ת��
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
            rowSize[smArray[i].col]++; // ��¼����ÿ�У�ԭ��ÿ�У���Ԫ�ظ���
        }
        rowStart[0] = 0;
        for (int i = 1; i < cols; i++) {
            rowStart[i] = rowSize[i - 1] + rowStart[i - 1]; // ������ÿ�е���ʼλ��
        }
        for (i = 0; i < terms; i++) {
            j = rowStart[smArray[i].col];
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++; // Ѱ�ұ��е��¸�Ԫ��
        }
    }
    delete[] rowSize;
    delete[] rowStart;
    return b;
};

// ��ǰ������s���
template <class T>
SparseMatrix<T> SparseMatrix<T>::add(SparseMatrix<T>& b)
{
    SparseMatrix<T> result(rows, cols);
    if (rows != b.rows || cols != b.cols) {
        cout << "��ƥ��ľ���" << endl;
        return result;
    }
    int i = 0, j = 0, indexA, indexB;
    result.terms = 0;
    while (i < terms && j < b.terms) {
        indexA = cols * smArray[i].row + smArray[i].col;
        indexB = cols * b.smArray[j].row + b.smArray[j].col;
        if (indexA < indexB) // smArray[i]��b.smArray[j]ǰ
        {
            result.smArray[result.terms] = smArray[i];
            i++;
        } else if (indexA > indexB) // smArray[i]��b.smArray[j]��
        {
            result.smArray[result.terms] = b.smArray[i];
            j++;
        } else // smArray[i]��b.smArray[j]����ͬλ��
        {
            result.smArray[result.terms] = smArray[i];
            result.smArray[result.terms].value = smArray[i].value + b.smArray[j].value;
            i++;
            j++;
        }
        result.terms++; // ϡ�����Ԫ�ظ���+1
    }
    // ��������Ԫ��
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

// ��ǰ������s���
template <class T>
SparseMatrix<T> SparseMatrix<T>::multiply(SparseMatrix<T>& b)
{
    SparseMatrix<T> result(rows, b.cols);
    if (cols != b.rows) // A������B��������
    {
        cout << "����ƥ��" << endl;
        return result;
    }
    int* rowSize = new int[b.rows]; // Bÿ�з���Ԫ�ظ���
    int* rowStart = new int[b.rows]; // Bÿ�з���Ԫ����ʼ�±�
    T* temp = new T[b.cols]; // �ݴ�ÿ�еļ�����
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
            for (i = rowStart[colA]; i < rowStart[colA + 1]; i++) // ����B�ڵ�rowB�е�Ԫ��
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