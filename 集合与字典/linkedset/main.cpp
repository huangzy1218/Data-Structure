#include "linkedset.h"
using namespace std;
int main()
{
    LinkedSet<int> s1;
    cout << "���룺" << endl;
    cin >> s1;
    cout << "�����" << endl;
    cout << s1;
    LinkedSet<int> s2;
    cout << "��ӣ�" << endl;
    for (int i = 1; i <= 10; i++) {
        s2.addMember(i);
    }
    cout << "��Ӻ󣬼������£�" << endl;
    cout << s2;
    cout << "ɾ����" << endl;
    cout << "������Ҫɾ����Ԫ�أ�" << endl;
    int n;
    cin >> n;
    s2.deleteMember(n);
    cout << "ɾ���󣬼������£�" << endl;
    cout << s2;
    cout << "��������" << endl;
    LinkedSet<int> s3 = s1 + s2;
    cout << "�����Ͻ��в����������£�" << endl;
    cout << s3;
    cout << "��������" << endl;
    s3 = s1 * s2;
    cout << "�����Ͻ��н����������£�" << endl;
    cout << s3;
    cout << "�������" << endl;
    s3 = s1 - s2;
    cout << "�����Ͻ��в���������£�" << endl;
    cout << s3;

    return 0;
}