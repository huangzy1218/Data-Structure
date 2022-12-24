#include <iostream>
#include <queue>
#include <stack>
using namespace std;
template <class T>
struct BinTreeNode // 二叉树结点类型
{
    T data; // 数据域
    BinTreeNode<T>*leftChild, *rightChild; // 左子女，右子女链域
    BinTreeNode()
        : leftChild(NULL)
        , rightChild(NULL)
    {
    }
    BinTreeNode(T x, BinTreeNode<T>* l = NULL, BinTreeNode<T>* r = NULL)
        : data(x)
        , leftChild(l)
        , rightChild(r)
    {
    }
};

template <class T>
class BinaryTree {
public:
    BinaryTree()
        : root(NULL)
    {
    } // 构造函数
    BinaryTree(T value)
        : refValue(value)
        , root(NULL)
    {
    } // 构造函数
    BinaryTree(const BinaryTree<T>& s); // 拷贝构造函数
    ~BinaryTree() { destory(root); } // 析构函数
    bool isEmpty() { return root == NULL; } // 判断是否为空树
    void createBinaryTree(T* VLR, T* LVR, int n, int m); // 利用前序和中序遍历结果构建二叉树
    BinTreeNode<T>* parent(BinTreeNode<T>* current) //  返回父节点
    { // 当前结点为根节点
        return (root == NULL || root == current) ? NULL : parent(root, current);
    }
    BinTreeNode<T>* leftChild(BinTreeNode<T>* current) // 返回左子女
    {
        return (current != NULL) ? current->leftChild : NULL;
    }
    BinTreeNode<T>* rightChild(BinTreeNode<T>* current) // 返回右子女
    {
        return (current != NULL) ? current->rightChild : NULL;
    }
    void createBinTree(istream& in, BinTreeNode<T>*& subTree, int n); // 利用前序遍历创建二叉树
    int height()
    {
        return height(root);
    } // 返回树高
    int size() { return size(root); } // 返回结点数
    BinTreeNode<T>* getRoot() const { return root; } // 取根
    void preOrder() // 前序遍历
    {
        preOrder(root);
    }
    void inOrder() // 中序遍历
    {
        preOrder(root);
    }
    void postOrder() // 后序遍历
    {
        postOrder(root);
    }
    void levelOrder(); // 层次序遍历
    int insert(const T& item); // 插入新元素
    BinTreeNode<T>* find(T& item) const; // 搜索
    BinTreeNode<T>* createBinaryTree(T* VLR, T* LVR, int n); // 根据前序遍历和中序遍历的结果构建二叉树
    // protected:
    BinTreeNode<T>* root; // 二叉树根结点
    T refValue; // 数据停止输入标志
    void createBinTree(istream& in, BinTreeNode<T>*& subTree); // 从流中读入建树
    // bool insert(BinTreeNode<T> *&subTree);                                    // 插入
    void destory(BinTreeNode<T>*& subTree); // 删除
    // bool find(BinTreeNode<T> *subTree, const T &x) const;                     // 查找
    BinTreeNode<T>* copy(BinTreeNode<T>* orignode); // 复制
    int height(BinTreeNode<T>* subTree) const; // 返回树高
    int size(BinTreeNode<T>* subTree) const; // 返回结点树
    BinTreeNode<T>* parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current); // 返回父结点
    BinTreeNode<T>* find(BinTreeNode<T>* subTree, const T& x) const; // 搜寻x
    void traverse(BinTreeNode<T>* subTree, ostream& out); // 前序遍历输出
    void preOrder(BinTreeNode<T>* subTree); // 前序遍历
    void inOrder(BinTreeNode<T>* subTree); // 中序遍历
    void postOrder(BinTreeNode<T>* subTree); // 后序遍历
    template <class U>
    friend istream& operator>>(istream& in, BinaryTree<U>* tree); // 输入运算符重载
    template <class U>
    friend ostream& operator<<(ostream& out, BinaryTree<U>& Tree); // 输出运算符重载
    void visit(BinTreeNode<T>* p);
};

// 销毁（私有）
template <class T>
void BinaryTree<T>::destory(BinTreeNode<T>*& subTree)
{
    if (subTree != NULL) {
        destory(subTree->leftChild);
        destory(subTree->rightChild);
        delete subTree;
    }
};

// 输出元素
template <class T>
void BinaryTree<T>::visit(BinTreeNode<T>* p)
{
    if (p != NULL) {
        cout << p->data << ' ';
    }
};
// 返回父结点：从结点subTree开始，搜索current的父结点
template <class T>
BinTreeNode<T>* BinaryTree<T>::parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current)
{
    if (subTree == NULL) {
        return NULL;
    }
    if (subTree->leftChild == current || subTree->rightChild == current) {
        return subTree;
    }
    BinTreeNode<T>* p;
    if ((p = parent(subTree->leftChild, current)) != NULL) // 递归在左子树搜索
    {
        return p;
    } else {
        return parent(subTree->rightChild, current); // 递归在右子树搜索
    }
};

template <class T>
void BinaryTree<T>::traverse(BinTreeNode<T>* subTree, ostream& out)
{
    if (subTree != NULL) {
        out << subTree->data << ' '; // 输出subTree的数值
        traverse(subTree->leftChild, out); // 递归搜索subTree的左子树
        traverse(subTree->rightChild, out); // 递归搜索subTree的右子树
    }
};

// 建立一颗二叉树
template <class T>
void BinaryTree<T>::createBinTree(istream& in, BinTreeNode<T>*& bt)
{
    std::stack<BinTreeNode<T>*> s;
    bt = NULL;
    BinTreeNode<T>*p, *t;
    int k;
    char ch;
    in >> ch;
    while (ch != refValue) {
        switch (ch) {
        case '(':
            s.push(p);
            k = 1;
            break;
        case ')':
            t = s.top();
            s.pop();
            break;
        case ',':
            k = 2;
            break;
        default:
            p = new BinTreeNode<T>(ch - '0');
            if (bt == NULL)
                bt = p;
            else if (k == 1) {
                t = s.top();
                t->leftChild = p;
            } else {
                t = s.top();
                t->rightChild = p;
            }
        }
        in >> ch;
    }
};

// 输入并创建一颗二叉树
template <class T>
istream& operator>>(istream& in, BinaryTree<T>& tree)
{
    tree.createBinTree(in, tree.root);
    return in;
}

// 输出一颗二叉树
template <class T>
ostream& operator<<(ostream& out, BinaryTree<T>& tree)
{
    out << "二叉树前序遍历：" << endl;
    tree.traverse(tree.root, out);
    out << "\n二叉树中序遍历：" << endl;
    tree.inOrder();
    cout << "\n二叉树后续遍历：" << endl;
    tree.postOrder();
    cout << "\n二叉树层序遍历：" << endl;
    tree.levelOrder();
    return out;
};

// 中序遍历（左、根、右）
template <class T>
void BinaryTree<T>::inOrder(BinTreeNode<T>* subTree)
{
    if (subTree != NULL) {
        inOrder(subTree->leftChild); // 中序遍历根的左子树
        visit(subTree); // 访问根结点
        inOrder(subTree->rightChild); // 中序遍历根的右子树
    }
};

// 前序遍历（根、左、右）
template <class T>
void BinaryTree<T>::preOrder(BinTreeNode<T>* subTree)
{
    if (subTree != NULL) {
        visit(subTree); // 访问根结点
        preOrder(subTree->leftChild); // 前序访问根的左子树
        preOrder(subTree->rightChild); // 前序访问根的右子树
    }
};

// 后序遍历（左、右、根）
template <class T>
void BinaryTree<T>::postOrder(BinTreeNode<T>* subTree)
{
    if (subTree != NULL) {
        postOrder(subTree->leftChild); // 后序访问根的左子树
        postOrder(subTree->rightChild); // 后序访问根的右子树
        visit(subTree); // 访问根节点
    }
};

// 计算以subTree为根的二叉树的结点个数
template <class T>
int BinaryTree<T>::size(BinTreeNode<T>* subTree) const
{
    if (subTree == NULL) {
        return 0;
    } else {
        return 1 + size(subTree->leftChild) + size(subTree->rightChild);
    }
};

// 计算以subTree为根的二叉树的树高
template <class T>
int BinaryTree<T>::height(BinTreeNode<T>* subTree) const
{
    if (subTree == NULL) {
        return 0;
    } else {
        int i = height(subTree->leftChild) + 1;
        int j = height(subTree->rightChild) + 1;
        return max(i, j);
    }
};

// 复制构造函数
template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& s)
{
    root = copy(s.root);
};

// 返回origin二叉树的副本
template <class T>
BinTreeNode<T>* BinaryTree<T>::copy(BinTreeNode<T>* orignode)
{
    if (orignode == NULL) {
        return NULL;
    }
    BinTreeNode<T>* temp = new BinTreeNode<T>();
    temp->data = orignode->data;
    temp->leftChild = copy(orignode->leftChild);
    temp->rightChild = copy(orignode->rightChild);
    return temp;
};

// 判断两棵树是否相等
template <class T>
int operator==(const BinaryTree<T>& s, const BinaryTree<T>& t)
{
    return (equal(s.root, t.root)) ? true : false;
};

// 判断两树是否相等
template <class T>
bool equal(BinTreeNode<T>* a, BinTreeNode<T>* b)
{
    if (a == NULL && b == NULL) {
        return true;
    }
    if (a != NULL && b != NULL && a->data == b->data && equal(a->leftChild, b->leftChild) && equal(a->rightChild, b->rightChild)) {
        return true;
    }
    return false;
};

// 利用前序遍历建立二叉树
template <class T>
void BinaryTree<T>::createBinTree(istream& in, BinTreeNode<T>*& subTree, int n)
{
    T item;
    in >> item;
    if (item != refValue) {
        subTree = new BinTreeNode<T>(item);
        if (subTree == NULL) {
            cerr << "内存分配异常" << endl;
            exit(1);
        }
        createBinTree(in, subTree->leftChild);
        createBinTree(in, subTree->rightChild);
    } else {
        subTree = NULL;
    }
};

// 层次序遍历（非递归）
template <class T>
void BinaryTree<T>::levelOrder()
{
    std::queue<BinTreeNode<T>*> q;
    BinTreeNode<T>* p = root;
    q.push(p);
    while (!q.empty()) {
        p = q.front();
        q.pop();
        visit(p);
        if (p->leftChild != NULL) {
            q.push(p->leftChild);
        }
        if (p->rightChild != NULL) {
            q.push(p->rightChild);
        }
    }
};

// 根据前序遍历和中序遍历的结果构建二叉树
// 前序遍历（ABHFDECKG），中序遍历（HBDFAEKCG）
// -->A(HDBF,EKCG) --> A(B(H,DF),EKCG) --> A(B(H,F(D)), EKCG) -->
// A(B(H, F(D)), E(KCG)) --> A(B(H, F(D)), E(C(K,G)))
template <class T>
BinTreeNode<T>* BinaryTree<T>::createBinaryTree(T* VLR, T* LVR, int n)
{
    if (n == 0) {
        return NULL;
    }
    int k = 0;
    while (VLR[0] != LVR[k]) // 在中序遍历中寻找根的位置
    {
        k++;
    }
    BinTreeNode<T>* t = new BinTreeNode<T>(VLR[0]); // 创建根结点
    t->leftChild = createBinaryTree(VLR + 1, LVR, k); // 构建左子树
    t->rightChild = createBinaryTree(VLR + k + 1, LVR + k + 1, n - k - 1); // 构建右子树
    return t;
};

// 根据前序遍历和中序遍历的结果构建二叉树，n为元素个数，m为任意值，起到区分作用
template <class T>
void BinaryTree<T>::createBinaryTree(T* VLR, T* LVR, int n, int m)
{
    // int n = sizeof(VLR) / sizeof(T); 退化为指针
    root = createBinaryTree(VLR, LVR, n);
};