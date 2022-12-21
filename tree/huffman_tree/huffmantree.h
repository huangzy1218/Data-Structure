#include <iostream>
#include "../heap/MinHeap.h"
struct HuffmanNode
{
    float data;                                                        // 结点数据
    HuffmanNode *leftChild, *rightChild, *parent;                      // 左右子女和父结点指针
    HuffmanNode() : leftChild(NULL), rightChild(NULL), parent(NULL) {} // 构造函数
    HuffmanNode(float elem, HuffmanNode *left = NULL,
                HuffmanNode *right = NULL, HuffmanNode *pr = NULL) // 构造函数
        : data(elem), leftChild(left), rightChild(right), parent(pr)
    {
    }
    bool operator<=(HuffmanNode &r) { return data <= r.data; }
    bool operator>(HuffmanNode &r) { return data > r.data; }
};

class HuffmanTree
{
public:
    HuffmanTree(float w[], int n);       // 构造函数
    ~HuffmanTree() { deleteTree(root); } // 析构函数
protected:
    HuffmanNode *root;
    void deleteTree(HuffmanNode *t); // 删除以t为根的子树
    void mergeTree(HuffmanNode &ht1, // 合并二叉树
                   HuffmanNode &ht2, HuffmanNode *&parent);
};

// 构造函数
HuffmanTree::HuffmanTree(float w[], int n)
{
    MinHeap<HuffmanNode> hp;
    HuffmanNode *parent, first, second, work;
    // 初始化，构建n颗空树
    for (int i = 0; i < n; i++)
    {
        work.data = w[i];
        work.leftChild = NULL;
        work.rightChild = NULL;
        work.parent = NULL;
        hp.insert(work); // 插入最小堆中
    }
    for (int i = 0; i < n - 1; i++) // 形成Huffman树
    {
        hp.removeMin(first);              // 选出权值最小的树
        hp.removeMin(second);             // 选择权值次小的树
        mergeTree(first, second, parent); // 合并
        hp.insert(*parent);               // 重新插入到最小堆中
    }
    root = parent; // 建立根结点
};

// 合并二叉树
void HuffmanTree::mergeTree(HuffmanNode &ht1,
                            HuffmanNode &ht2, HuffmanNode *&parent)
{
    parent = new HuffmanNode();
    // 利用较小的树构建二叉树
    parent->leftChild = &ht1;
    parent->rightChild = &ht2;
    parent->data = ht1.data + ht2.data; // 其父结点的值为左右孩子权值之和
    ht1.parent = ht2.parent = parent;
};