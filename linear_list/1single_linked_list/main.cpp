#include "List.h"
#include <iostream>
using namespace std;
int main(void)
{
    List<int> ul;
    std::cout << "���룺" << endl;
    l.input();

    std::cout << "�����" << endl;
    l.output();

    cout << "���룺" << endl; // ע�⣺�±��1��ʼ
    cout << "�������λ�ú�Ԫ��ֵ" << endl;
    int pos, value;
    cin >> pos >> value;
    l.insert(pos, value);
    cout << "������������£�" << endl;
    l.output();

    cout << "ɾ����" << endl;
    cout << "��������ɾ����Ԫ���±�" << endl;
    cin >> pos;
    l.remove(pos, value);
    cout << "ɾ�����������£�" << endl;
    l.output();

    cout << "��ȡԪ�أ�" << endl;
    cout << "������Ԫ���±꣺" << endl;
    cin >> pos;
    l.getData(pos, value); // �����±��1��ʼ���������±��1
    cout << "�±�Ϊ" << pos << " ��Ԫ��Ϊ��" << value << endl;

    cout << "����Ԫ�أ�" << endl;
    cout << "������Ҫ���õ�Ԫ���±꼰ֵ��" << endl;
    cin >> pos >> value;
    l.setData(pos, value);
    cout << "���ú󣬵��������£�" << endl;
    l.output();

    cout << "���ȣ�" << endl;
    cout << "��������Ϊ��" << l.length() << endl;

    cout << "���ң�" << endl;
    cout << "��������Ҫ���ҵ�Ԫ�أ�" << endl;
    cin >> value;
    LinkNode<int> *ptr = l.search(value);
    if (ptr == NULL)
    {
        cout << "δ��ѯ����Ԫ��" << endl;
    }
    else
    {
        cout << "��Ԫ�ش���" << endl;
    }

    cout << "����" << endl;
    l.sort();
    cout << "����󣬵��������£�" << endl;
    l.output();

    return 0;
}