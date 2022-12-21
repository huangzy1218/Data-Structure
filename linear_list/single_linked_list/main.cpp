#include "List.h"
#include <iostream>
using namespace std;
int main(void)
{
    List<int> ul;
    std::cout << "输入：" << endl;
    l.input();

    std::cout << "输出：" << endl;
    l.output();

    cout << "插入：" << endl; // 注意：下标从1开始
    cout << "输入插入位置和元素值" << endl;
    int pos, value;
    cin >> pos >> value;
    l.insert(pos, value);
    cout << "插入后，链表如下：" << endl;
    l.output();

    cout << "删除：" << endl;
    cout << "请输入需删除的元素下标" << endl;
    cin >> pos;
    l.remove(pos, value);
    cout << "删除后，链表如下：" << endl;
    l.output();

    cout << "获取元素：" << endl;
    cout << "请输入元素下标：" << endl;
    cin >> pos;
    l.getData(pos, value); // 链表下标从1开始，而输入下标从1
    cout << "下标为" << pos << " 的元素为：" << value << endl;

    cout << "设置元素：" << endl;
    cout << "请输入要设置的元素下标及值：" << endl;
    cin >> pos >> value;
    l.setData(pos, value);
    cout << "设置后，单链表如下：" << endl;
    l.output();

    cout << "长度：" << endl;
    cout << "单链表长度为：" << l.length() << endl;

    cout << "查找：" << endl;
    cout << "请输入所要查找的元素：" << endl;
    cin >> value;
    LinkNode<int> *ptr = l.search(value);
    if (ptr == NULL)
    {
        cout << "未查询到该元素" << endl;
    }
    else
    {
        cout << "该元素存在" << endl;
    }

    cout << "排序：" << endl;
    l.sort();
    cout << "排序后，单链表如下：" << endl;
    l.output();

    return 0;
}