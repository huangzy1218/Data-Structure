#include "seqlist.h"
#include <iostream>
using namespace std;
int main(void)
{
    SeqList<int> sl;
    std::cout << "���룺" << endl;
    sl.input();

    std::cout << "�����" << endl;
    sl.output();

    cout << "���룺" << endl; // ע�⣺�±��1��ʼ
    cout << "�������λ�ú�Ԫ��ֵ" << endl;
    int pos, value;
    cin >> pos >> value;
    sl.insert(pos, value);
    cout << "�����˳������£�" << endl;
    sl.output();

    cout << "ɾ����" << endl;
    cout << "��������ɾ����Ԫ���±�" << endl;
    cin >> pos;
    sl.remove(pos, value);
    cout << "ɾ����˳������£�" << endl;
    sl.output();

    cout << "��ȡԪ�أ�" << endl;
    cout << "������Ԫ���±꣺" << endl;
    cin >> pos;
    sl.getData(pos, value); // �����±��1��ʼ���������±��1
    cout << "�±�Ϊ" << pos << " ��Ԫ��Ϊ��" << value << endl;

    cout << "����Ԫ�أ�" << endl;
    cout << "������Ҫ���õ�Ԫ���±꼰ֵ��" << endl;
    cin >> pos >> value;
    sl.setData(pos, value);
    cout << "���ú�˳������£�" << endl;
    sl.output();

    cout << "���ȣ�" << endl;
    cout << "˳�����Ϊ��" << sl.length() << endl;

    cout << "���ң�" << endl;
    cout << "��������Ҫ���ҵ�Ԫ�أ�" << endl;
    cin >> value;
    pos = sl.search(value);
    if (pos == -1) {
        cout << "δ��ѯ����Ԫ��" << endl;
    } else {
        cout << "��Ԫ�ش���" << endl;
    }

    cout << "����" << endl;
    sl.sort();
    cout << "����󣬵��������£�" << endl;
    sl.output();

    return 0;
}