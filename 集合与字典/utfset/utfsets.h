#include <iostream>
const int defaultSize = 10;
class UTFSets {
public:
    UTFSets(int sz = defaultSize); // 构造函数
    ~UTFSets() { delete[] parent; } // 析构函数
    UTFSets& operator=(UTFSets& r); // 赋值运算符重载
    void unionSet(int root1, int root2); // 两个集合求并集
    int find(int x); // 搜索集合 x 的根
    void weightUnion(int root1, int root2); // 加权合并
    int collapsingFind(int x); // 压缩路径搜索

private:
    int* parent; // 集合元素数组
    int size; // 集合元素个数
};

UTFSets::UTFSets(int sz)
{
    size = sz;
    parent = new int[size];
    for (int i = 0; i < size; i++) {
        parent[i] = -1; // 每个自成单元素集合
    }
};

// 搜索集合 x 的根
int UTFSets::find(int x)
{
    while (parent[x] >= 0) {
        x = parent[x];
    }
    return x;
};

// 两个集合求并集
void UTFSets::unionSet(int root1, int root2)
{
    parent[root1] += parent[root2];
    parent[root2] = root1;
};

// 加权合并
void UTFSets::weightUnion(int root1, int root2)
{
    int r1 = find(root1), r2 = find(root2);
    int temp;
    if (r1 != r2) {
        temp = parent[r1] + parent[r2];
        if (parent[r2] > parent[r1]) { // 以 r2 为根的树结点多
            parent[r1] = r2; // r1 接在 r2 下
            parent[r2] = temp;
        } else {
            parent[r2] = r1;
            parent[r1] = temp; // r2 接在 r1 下
        }
    }
};

// 压缩路径搜索
int UTFSets::collapsingFind(int x)
{
    int root;
    for (root = x; parent[root] >= 0; root = parent[root])
        ; // 搜索根 root
    while (x != root) {
        int temp = parent[x]; // 向上主次压缩
        parent[x] = root;
        x = temp;
    }
    return root;
};