#include "LinkedQueue.h"

int main(void)
{
    LinkedQueue<int> lq;
    int n;
    int elem;
    cout << "��ӣ�" << endl;
    cout << "���������Ԫ�ظ�����Ԫ��ֵ" << endl;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> elem;
        lq.enQueue(elem);
    }
    cout << "��Ӻ󣬶������£�" << endl;
    cout << lq;
    cout << "��ȡ����Ԫ�أ�" << endl;
    lq.getFront(elem);
    cout << elem << endl;
    cout << "���ӣ�" << endl;
    lq.deQueue(elem);
    cout << "����Ԫ�أ�" << elem << endl;

    return 0;
}