#include "SeqStack.h"
using namespace std;
int main(void)
{
    SeqStack<int> ss;
    cout << "��ջ��" << endl;
    cout << "���������Ԫ�ظ�����Ԫ��ֵ" << endl;
    int n, elem;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> elem;
        ss.push(elem);
    }
    cout << "��ջ��ջ���£�" << endl;
    cout << ss;
    cout << "��ȡջ��Ԫ�أ�" << endl;
    ss.getTop(elem);
    cout << "ջ��Ԫ��Ϊ��" << elem << endl;
    cout << "��ջ��" << endl;
    ss.pop(elem);
    cout << "��ջԪ��Ϊ��" << elem << endl;
    cout << "��ջ��ջ���£�" << endl;
    cout << ss;
    cout << "��ȡ��С��" << endl;
    cout << "ջ��С��" << ss.size() << endl;

    return 0;
}