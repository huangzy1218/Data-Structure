/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of hash table
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "hashtable.h"
using namespace std;
int main(void)
{
    HashTable<string, int> hashtable;

    // ����
    hashtable.put("hello", 1);
    hashtable.put("world", 100);

    // ���
    hashtable.output();

    // ����
    string target = "hello";
    if (hashtable.find(target)) {
        cout << target << " ����" << endl;
    } else {
        cout << target << " ������" << endl;
    }

    // ɾ��
    hashtable.remove(target);
    if (hashtable.find(target)) {
        cout << target << " ����" << endl;
    } else {
        cout << target << " ������" << endl;
    }

    // [] ���������
    cout << hashtable["world"] << endl;

    return 0;
}