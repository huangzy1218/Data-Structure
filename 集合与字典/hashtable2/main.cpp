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

    // 插入
    hashtable.put("hello", 1);
    hashtable.put("world", 100);

    // 输出
    hashtable.output();

    // 查找
    string target = "hello";
    if (hashtable.find(target)) {
        cout << target << " 存在" << endl;
    } else {
        cout << target << " 不存在" << endl;
    }

    // 删除
    hashtable.remove(target);
    if (hashtable.find(target)) {
        cout << target << " 存在" << endl;
    } else {
        cout << target << " 不存在" << endl;
    }

    // [] 运算符重载
    cout << hashtable["world"] << endl;

    return 0;
}