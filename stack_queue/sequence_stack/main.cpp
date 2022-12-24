#include "SeqStack.h"
using namespace std;
int main(void)
{
    SeqStack<int> ss;
    cout << "入栈：" << endl;
    cout << "请输入插入元素个数及元素值" << endl;
    int n, elem;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> elem;
        ss.push(elem);
    }
    cout << "入栈后，栈如下：" << endl;
    cout << ss;
    cout << "获取栈顶元素：" << endl;
    ss.getTop(elem);
    cout << "栈顶元素为：" << elem << endl;
    cout << "出栈：" << endl;
    ss.pop(elem);
    cout << "出栈元素为：" << elem << endl;
    cout << "出栈后，栈如下：" << endl;
    cout << ss;
    cout << "获取大小：" << endl;
    cout << "栈大小：" << ss.size() << endl;

    return 0;
}