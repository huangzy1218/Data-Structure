/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of sequence list
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "seqlist.h"
#include <iostream>
using namespace std;
int main(void)
{
    SeqList<int> sl;

    // ����
    sl.input();

    // ���
    sl.output();

    // ����
    cout << "�������λ�ú�Ԫ��ֵ" << endl;
    int pos, value;
    cin >> pos >> value;
    sl.insert(pos, value);
    sl.output();

    // ɾ��
    cout << "����ɾ����Ԫ���±�" << endl;
    cin >> pos;
    sl.remove(pos, value);
    sl.output();

    // ��ȡ
    cout << "����Ԫ���±꣺" << endl;
    cin >> pos;
    sl.getData(pos, value); // �±�� 0 ��ʼ
    cout << "�±�Ϊ" << pos << " ��Ԫ��Ϊ��" << value << endl;

    // ����
    cout << "����Ҫ���õ�Ԫ���±꼰ֵ��" << endl;
    cin >> pos >> value;
    sl.setData(pos, value);

    // ����
    cout << "˳�����Ϊ��" << sl.length() << endl;

    // ����
    cout << "������ҵ�Ԫ�أ�" << endl;
    cin >> value;
    pos = sl.search(value);
    if (pos == -1) {
        cout << "δ��ѯ����Ԫ��" << endl;
    } else {
        cout << "��Ԫ�ش���" << endl;
    }

    // ����
    sl.sort();
    cout << "����󣬵��������£�" << endl;
    sl.output();

    return 0;
}