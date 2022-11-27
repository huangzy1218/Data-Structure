#include "SeqList.h"
using namespace std;

int main()
{
    SeqList<int> sl;                    // 构建顺序表
    cout << "---Input---" << endl;
    sl.Input();

    cout << "---Output---" << endl;
    sl.Output();

    cout << "---Insert---" << endl;
    cout << "Please input the position and value:" << endl;
    int pos, value;
    cin >> pos >> value;
    sl.Insert(pos, value);
    cout << "After insert, the sequent list is as followed:" << endl;
    sl.Output();

    cout << "---Remove---" << endl;
    cout << "Please input the index of element should be removed:" << endl;
    cin >> pos;
    sl.Remove(pos);
    cout << "After remove, the sequent list is as followed:" << endl;
    sl.Output();

    cout << "---GetData---" << endl;
    cout << "Please enter the index of the element you want:" << endl;
    cin >> pos;
    sl.GetData(pos + 1, value);
    cout << "Element with subscript " << pos << " is " <<  value << endl;

    cout << "---SetDate---" << endl;
    cout << "Please enter the index of the element you want reset" << endl;
    cin >> pos >> value;
    sl.SetData(pos + 1, value);
    cout << "After set, the sequent list is as followed:" << endl;
    sl.Output();

    cout << "---Length---" << endl;
    cout << "The length of the sequent list is " << sl.Length() << endl;

    cout << "---Size---" << endl;
    cout << "The size of the sequent list is " << sl.Size() << endl;

    cout << "---Search---" << endl;
    cout << "Please enter the element you search:" << endl;
    cin >> value;
    pos = sl.Search(value);
    if (!pos) {
        cout << "Not Found!" << endl;
    } else {
        cout << value << " is the NO." << pos << endl;
    }

    cout << "---Sort---" << endl;
    sl.Sort();
    cout << "After sorted, the the sequent list is as followed:" << endl;
    sl.Output();

    return 0;
}