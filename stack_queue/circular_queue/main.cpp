#include "seqqueue.h"

int main(void)
{
    SeqQueue<int> sq;
    int n;
    int elem;
    cout << "��ӣ�" << endl;
    cout << "���������Ԫ�ظ�����Ԫ��ֵ" << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> elem;
        sq.enQueue(elem);
    }
    cout << "��Ӻ󣬶������£�" << endl;
    cout << sq;
    cout << "��ȡ����Ԫ�أ�" << endl;
    sq.getFront(elem);
    cout << elem << endl;
    cout << "���ӣ�" << endl;
    sq.deQueue(elem);
    cout << "����Ԫ�أ�" << elem << endl;

    return 0;
}