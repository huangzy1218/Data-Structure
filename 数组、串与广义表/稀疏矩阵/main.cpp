#include "SparseMatrix.h"

int main()
{
    SparseMatrix<int> sm1;
    cin >> sm1;
    cout << sm1;
    cout << "����ת�ã�" << endl;
    SparseMatrix<int> tm = sm1.transpose();
    cout << tm << endl;
    SparseMatrix<int> sm2 = sm1;
    cout << sm2;
    cout << "������ӣ�" << endl;
    SparseMatrix<int> result1 = sm1.add(sm2);
    cout << result1;
    cout << "������ˣ�" << endl;
    SparseMatrix<int> result2 = sm1.add(sm2);
    cout << result2 << endl;

    return 0;
}