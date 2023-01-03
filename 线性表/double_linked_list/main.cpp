/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of double linked list
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "DblList.h"
#include <iostream>
using namespace std;
int main(void)
{
    DblList<int> dl;

    // ����
    dl.input();

    // ���
    dl.output();

    // ����
    cout << "�������λ�ú�Ԫ��ֵ" << endl;
    int pos, value;
    cin >> pos >> value;
    dl.insert(pos, value);
    dl.output();

    // ɾ��
    cout << "������ɾ����Ԫ���±�" << endl;
    cin >> pos;
    dl.remove(pos, value);
    dl.output();

    // ��ȡ
    cout << "������Ԫ���±꣺" << endl;
    cin >> pos;
    dl.getData(pos, value); // �����±��1��ʼ���������±��1
    cout << "�±�: " << pos << " ֵ: " << value << endl;

    // ��ȡǰ��
    cin >> pos;
    cout << dl.getPreData(pos) << endl;

    // ��ȡ���
    cin >> pos;
    cout << dl.getNextData(pos) << endl;

    // ����
    cout << "����Ҫ���õ�Ԫ���±꼰ֵ��" << endl;
    cin >> pos >> value;
    dl.setData(pos, value);

    // ����
    cout << "˫��������Ϊ��" << dl.length() << endl;

    // ����
    cout << "������Ҫ���ҵ�Ԫ�أ�" << endl;
    cin >> value;
    DblNode<int>* ptr = dl.search(value);
    if (ptr == NULL) {
        cout << "δ��ѯ����Ԫ��" << endl;
    } else {
        cout << "��Ԫ�ش���" << endl;
    }

    // ����
    dl.sort();
    cout << "����󣬵��������£�" << endl;
    dl.output();

    return 0;
}