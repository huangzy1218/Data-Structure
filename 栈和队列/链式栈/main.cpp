#include "LinkedStack.h"

int main(void)
{
    LinkedStack<int> ls;
    cout << "入栈：" << endl;
    cout << "请输入插入元素个数及元素值" << endl;
    int n, elem;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> elem;
        ls.push(elem);
    }
    cout << "入栈后，栈如下：" << endl;
    cout << ls;
    cout << "获取栈顶元素：" << endl;
    ls.getTop(elem);
    cout << "栈顶元素为：" << elem << endl;
    cout << "出栈：" << endl;
    ls.pop(elem);
    cout << "出栈元素为：" << elem << endl;
    cout << "出栈后，栈如下：" << endl;
    cout << ls;
    cout << "获取大小：" << endl;
    cout << "栈大小：" << ls.size() << endl;
}