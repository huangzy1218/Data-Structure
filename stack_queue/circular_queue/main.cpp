#include "seqqueue.h"

int main(void)
{
    SeqQueue<int> sq;
    int n;
    int elem;
    cout << "入队：" << endl;
    cout << "请输入插入元素个数及元素值" << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> elem;
        sq.enQueue(elem);
    }
    cout << "入队后，队列如下：" << endl;
    cout << sq;
    cout << "获取队首元素：" << endl;
    sq.getFront(elem);
    cout << elem << endl;
    cout << "出队：" << endl;
    sq.deQueue(elem);
    cout << "出队元素：" << elem << endl;

    return 0;
}