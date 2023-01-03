#include <iostream>
const int defaultSize = 10;
class UTFSets {
public:
    UTFSets(int sz = defaultSize); // ���캯��
    ~UTFSets() { delete[] parent; } // ��������
    UTFSets& operator=(UTFSets& r); // ��ֵ���������
    void unionSet(int root1, int root2); // ���������󲢼�
    int find(int x); // �������� x �ĸ�
    void weightUnion(int root1, int root2); // ��Ȩ�ϲ�
    int collapsingFind(int x); // ѹ��·������

private:
    int* parent; // ����Ԫ������
    int size; // ����Ԫ�ظ���
};

UTFSets::UTFSets(int sz)
{
    size = sz;
    parent = new int[size];
    for (int i = 0; i < size; i++) {
        parent[i] = -1; // ÿ���Գɵ�Ԫ�ؼ���
    }
};

// �������� x �ĸ�
int UTFSets::find(int x)
{
    while (parent[x] >= 0) {
        x = parent[x];
    }
    return x;
};

// ���������󲢼�
void UTFSets::unionSet(int root1, int root2)
{
    parent[root1] += parent[root2];
    parent[root2] = root1;
};

// ��Ȩ�ϲ�
void UTFSets::weightUnion(int root1, int root2)
{
    int r1 = find(root1), r2 = find(root2);
    int temp;
    if (r1 != r2) {
        temp = parent[r1] + parent[r2];
        if (parent[r2] > parent[r1]) { // �� r2 Ϊ����������
            parent[r1] = r2; // r1 ���� r2 ��
            parent[r2] = temp;
        } else {
            parent[r2] = r1;
            parent[r1] = temp; // r2 ���� r1 ��
        }
    }
};

// ѹ��·������
int UTFSets::collapsingFind(int x)
{
    int root;
    for (root = x; parent[root] >= 0; root = parent[root])
        ; // ������ root
    while (x != root) {
        int temp = parent[x]; // ��������ѹ��
        parent[x] = root;
        x = temp;
    }
    return root;
};