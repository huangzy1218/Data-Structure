#include "String.h"

int main()
{
    String s;
    cout << "���룺" << endl;
    cin >> s;
    cout << "�����" << endl;
    cout << s << endl;
    cout << "���ȣ�" << endl;
    cout << s.length() << endl;
    cout << "�ַ���ƥ�䣺" << endl;
    cout << "������ƥ�䴮��" << endl;
    String pattern;
    cin >> pattern;
    cout << s.find(pattern) << endl;

    return 0;
}