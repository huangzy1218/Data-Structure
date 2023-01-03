#include "linkedset.h"
using namespace std;
int main()
{
    LinkedSet<int> s1;
    cout << "输入：" << endl;
    cin >> s1;
    cout << "输出：" << endl;
    cout << s1;
    LinkedSet<int> s2;
    cout << "添加：" << endl;
    for (int i = 1; i <= 10; i++) {
        s2.addMember(i);
    }
    cout << "添加后，集合如下：" << endl;
    cout << s2;
    cout << "删除：" << endl;
    cout << "请输入要删除的元素：" << endl;
    int n;
    cin >> n;
    s2.deleteMember(n);
    cout << "删除后，集合如下：" << endl;
    cout << s2;
    cout << "并操作：" << endl;
    LinkedSet<int> s3 = s1 + s2;
    cout << "两集合进行并操作后如下：" << endl;
    cout << s3;
    cout << "交操作：" << endl;
    s3 = s1 * s2;
    cout << "两集合进行交操作后如下：" << endl;
    cout << s3;
    cout << "差操作：" << endl;
    s3 = s1 - s2;
    cout << "两集合进行差操作后如下：" << endl;
    cout << s3;

    return 0;
}