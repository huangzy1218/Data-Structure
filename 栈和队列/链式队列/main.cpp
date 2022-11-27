#include "LinkedQueue.h"

int main(void)
{
    LinkedQueue<int> lq;
    int n;
    int elem;
    cout << "入队：" << endl;
    cout << "请输入插入元素个数及元素值" << endl;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> elem;
        lq.enQueue(elem);
    }
    cout << "入队后，队列如下：" << endl;
    cout << lq;
    cout << "获取队首元素：" << endl;
    lq.getFront(elem);
    cout << elem << endl;
    cout << "出队：" << endl;
    lq.deQueue(elem);
    cout << "出队元素：" << elem << endl;

    return 0;
}