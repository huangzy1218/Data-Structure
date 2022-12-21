#include <iostream>
#include "../heap/MinHeap.h"
struct HuffmanNode
{
    float data;                                                        // �������
    HuffmanNode *leftChild, *rightChild, *parent;                      // ������Ů�͸����ָ��
    HuffmanNode() : leftChild(NULL), rightChild(NULL), parent(NULL) {} // ���캯��
    HuffmanNode(float elem, HuffmanNode *left = NULL,
                HuffmanNode *right = NULL, HuffmanNode *pr = NULL) // ���캯��
        : data(elem), leftChild(left), rightChild(right), parent(pr)
    {
    }
    bool operator<=(HuffmanNode &r) { return data <= r.data; }
    bool operator>(HuffmanNode &r) { return data > r.data; }
};

class HuffmanTree
{
public:
    HuffmanTree(float w[], int n);       // ���캯��
    ~HuffmanTree() { deleteTree(root); } // ��������
protected:
    HuffmanNode *root;
    void deleteTree(HuffmanNode *t); // ɾ����tΪ��������
    void mergeTree(HuffmanNode &ht1, // �ϲ�������
                   HuffmanNode &ht2, HuffmanNode *&parent);
};

// ���캯��
HuffmanTree::HuffmanTree(float w[], int n)
{
    MinHeap<HuffmanNode> hp;
    HuffmanNode *parent, first, second, work;
    // ��ʼ��������n�ſ���
    for (int i = 0; i < n; i++)
    {
        work.data = w[i];
        work.leftChild = NULL;
        work.rightChild = NULL;
        work.parent = NULL;
        hp.insert(work); // ������С����
    }
    for (int i = 0; i < n - 1; i++) // �γ�Huffman��
    {
        hp.removeMin(first);              // ѡ��Ȩֵ��С����
        hp.removeMin(second);             // ѡ��Ȩֵ��С����
        mergeTree(first, second, parent); // �ϲ�
        hp.insert(*parent);               // ���²��뵽��С����
    }
    root = parent; // ���������
};

// �ϲ�������
void HuffmanTree::mergeTree(HuffmanNode &ht1,
                            HuffmanNode &ht2, HuffmanNode *&parent)
{
    parent = new HuffmanNode();
    // ���ý�С��������������
    parent->leftChild = &ht1;
    parent->rightChild = &ht2;
    parent->data = ht1.data + ht2.data; // �丸����ֵΪ���Һ���Ȩֵ֮��
    ht1.parent = ht2.parent = parent;
};