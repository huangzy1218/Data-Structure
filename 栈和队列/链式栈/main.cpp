#include "LinkedStack.h"

int main(void)
{
    LinkedStack<int> ls;
    cout << "��ջ��" << endl;
    cout << "���������Ԫ�ظ�����Ԫ��ֵ" << endl;
    int n, elem;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> elem;
        ls.push(elem);
    }
    cout << "��ջ��ջ���£�" << endl;
    cout << ls;
    cout << "��ȡջ��Ԫ�أ�" << endl;
    ls.getTop(elem);
    cout << "ջ��Ԫ��Ϊ��" << elem << endl;
    cout << "��ջ��" << endl;
    ls.pop(elem);
    cout << "��ջԪ��Ϊ��" << elem << endl;
    cout << "��ջ��ջ���£�" << endl;
    cout << ls;
    cout << "��ȡ��С��" << endl;
    cout << "ջ��С��" << ls.size() << endl;
}