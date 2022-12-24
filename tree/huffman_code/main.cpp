#include "huffmancode.h"
using namespace std;
int main()
{
    string str;
    cin >> str;
    HuffmanCode hc(str);
    cout << "对应字符的编码情况：" << endl;
    hc.encode();
    cout << endl;
    cout << "请输入要解码的二进制编码:" << endl;
    cin >> str;
    cout << "解码如下：" << endl;
    hc.decode(str);

    return 0;
}