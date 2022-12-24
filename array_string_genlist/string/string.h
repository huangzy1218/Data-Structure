#include <cstring>
#include <iostream>
const int defaultSize = 100 + 5;
using namespace std;
class String {
public:
    String(int sz = defaultSize); // ���캯��
    String(const char* init); // ���캯��
    String(const String& ob); // �������캯��
    ~String() { delete[] ch; } // ��������
    int length() const { return curLength; } // ��ȡ����
    String operator()(int pos, int len); // ��ȡ��pos��ʼ����Ϊlen���ַ���
    int operator==(String& ob) const // �жϴ��Ƿ����
    {
        return strcmp(ch, ob.ch) == 0;
    }
    int operator!=(String& ob) const // �жϴ��Ƿ񲻵�
    {
        return strcmp(ch, ob.ch) != 0;
    }
    int operator!() const { return curLength == 0; } // �ж��Ƿ�Ϊ�մ�
    String& operator=(const String& ob); // ��ֵ���������
    String& operator+=(const String& ob); // �ַ���ƴ��
    char& operator[](int i); // ȡ��i���ַ�
    int find(String& pat) const; // ��pat��this��ĳ���Ӵ�ƥ�䡣���ص�һ�γ��ֵ�λ��
    friend ostream& operator<<(ostream& os, String& s); // ������������
    friend istream& operator>>(istream& is, String& s); // �������������

private:
    char* ch;
    int curLength;
    int maxSize;
    void bulidNext(int n);
};

// ���캯��
String::String(int sz)
{
    maxSize = sz;
    ch = new char[maxSize + 1]; // Ϊ'\0'Ԥ���ռ�
    if (ch == NULL) {
        cerr << "�ڴ����ʧ��" << endl;
        exit(1);
    }
    curLength = 0;
    ch[0] = '\0';
};

// ���캯��
String::String(const char* init)
{
    int len = strlen(init);
    maxSize = (len > defaultSize) ? len : defaultSize;
    ch = new char[maxSize + 1];
    if (ch == NULL) {
        cerr << "�ڴ����ʧ��" << endl;
        exit(1);
    }
    curLength = len;
    strcpy(ch, init);
};

// ���ƹ��캯��
String::String(const String& ob)
{
    maxSize = ob.maxSize;
    ch = new char[maxSize + 1];
    if (ch == NULL) {
        cerr << "�ڴ����ʧ��" << endl;
        exit(1);
    }
    curLength = ob.curLength;
    strcpy(ch, ob.ch);
};

// ���Ӵ�
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

// ��ֵ���������
String& String::operator=(const String& ob)
{
    if (&ob != this) {
        delete[] ch;
        ch = new char[ob.maxSize];
        if (ch == NULL) {
            cerr << "�ڴ����ʧ��" << endl;
            exit(1);
        }
        strcpy(ch, ob.ch);
        curLength = ob.curLength;
        maxSize = ob.maxSize;
    }
    return *this;
};

// �ַ�������
String& String::operator+=(const String& ob)
{
    char* temp = ch;
    int n = curLength + ob.curLength;
    int m = (maxSize >= n) ? maxSize : n;
    ch = new char[m];
    if (ch == NULL) {
        cerr << "�ڴ�����쳣" << endl;
        exit(1);
    }
    maxSize = m;
    curLength = n;
    strcpy(ch, temp);
    strcat(ch, ob.ch);
    delete[] temp;
    return *this;
};

// []��������أ�ȡ��i��yuansu
char& String::operator[](int i)
{
    if (i < 0 || i >= curLength) {
        cout << "�±�Խ��" << endl;
    }
    return ch[i];
};

// ��pat��this��ĳ���Ӵ�ƥ�䡣���ص�һ�γ��ֵ�λ��
// KMP�㷨�����С���Ӵ����ȣ�����ǰ��׺��ʹǰ׺������׺��λ��
int String::find(String& pat) const
{
    int* next = new int[pat.curLength];
    int i, j, k = 0;
    int prefix_len = 0; // ��ǰ����ǰ׺�ĳ���
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

// ������������
ostream& operator<<(ostream& os, String& s)
{
    os << s.ch;
    return os;
};

// �������������
istream& operator>>(istream& is, String& s)
{
    cout << "�������ַ�����" << endl;
    is >> s.ch;
    s.curLength = strlen(s.ch);
    return is;
};