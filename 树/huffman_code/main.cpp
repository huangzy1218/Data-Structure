#include "huffmancode.h"
using namespace std;
int main()
{
    string str;
    cin >> str;
    HuffmanCode hc(str);
    cout << "��Ӧ�ַ��ı��������" << endl;
    hc.encode();
    cout << endl;
    cout << "������Ҫ����Ķ����Ʊ���:" << endl;
    cin >> str;
    cout << "�������£�" << endl;
    hc.decode(str);

    return 0;
}