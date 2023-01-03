/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of static linked list
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "staticlist.h"
#include <iostream>
using namespace std;
int main(void)
{
    StaticList<int> sl;

    // ׷��
    for (int i = 1; i <= 10; i++) {
        sl.append(i);
    }

    // ���
    sl.output();

    // ����
    sl.insert(10, 1);

    // ɾ��
    sl.remove(1); // �±�� 1 ��ʼ
    sl.output();

    // ����
    if (sl.search(1)) {
        cout << "���ҳɹ�" << endl;
    } else {
        cout << "����ʧ��" << endl;
    }

    // ����
    cout << "��̬�����ȣ�" << sl.length() << endl;

    return 0;
}