/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of single linked list
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "List.h"
#include <iostream>
using namespace std;
int main(void)
{
    List<int> l;

    // ����
    l.input();

    // ���
    l.output();

    // ����
    cout << "�������λ�ú�Ԫ��ֵ" << endl;
    int pos, value;
    cin >> pos >> value;
    l.insert(pos, value);
    l.output();

    // ɾ��
    cout << "������ɾ����Ԫ���±�" << endl;
    cin >> pos;
    l.remove(pos, value);
    l.output();

    // ��ȡ
    cout << "����Ԫ���±꣺" << endl;
    cin >> pos;
    l.getData(pos, value); // �����±��1��ʼ���������±��1
    cout << "�±�: " << pos << " ֵ: " << value << endl;

    // ����
    cout << "����Ҫ���õ�Ԫ���±꼰ֵ��" << endl;
    cin >> pos >> value;
    l.setData(pos, value);

    // ����
    cout << "��������Ϊ��" << l.length() << endl;

    // ����
    cout << "������Ҫ���ҵ�Ԫ�أ�" << endl;
    cin >> value;
    LinkNode<int>* ptr = l.search(value);
    if (ptr == NULL) {
        cout << "δ��ѯ����Ԫ��" << endl;
    } else {
        cout << "��Ԫ�ش���" << endl;
    }

    // ����
    l.sort();
    cout << "����󣬵��������£�" << endl;
    l.output();

    return 0;
}