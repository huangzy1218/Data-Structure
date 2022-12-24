#include <iostream>
const int maxSize = 256;
struct HuffmanNode {
    int weight; // Ȩֵ
    char ch; // �洢�ַ�
    string code; // ��Ӧ����
    int leftChild, rightChild, parent;
};

class HuffmanCode {
public:
    HuffmanCode(string str); // ���캯��
    ~HuffmanCode() { delete[] huffmanTree; } // ��������
    void getMin(int& first, int& second, int parent); // ѡ��������СԪ��
    void merge(int first, int second, int parent); // �ϲ�
    void encode(); // ����
    void decode(string str); // ����
private:
    HuffmanNode* huffmanTree;
    int leafSize; // ��ͬ�ַ��ĸ���
};

// ���캯��
HuffmanCode::HuffmanCode(string str)
{
    int len = str.size();
    int charCounter[maxSize]; // �洢ÿ���ַ����ֵĸ���
    huffmanTree = new HuffmanNode[maxSize];

    for (i = 0; i < (2 * len - 1); i++) {
        huffmanTree[i].leftChild = huffmanTree[i].rightChild = huffmanTree[i].parent = -1;
        HuffmanTree[i].code = "";
    }

    memset(charCounter, 0, sizeof(charCounter));
    for (int i = 0; i < len; i++) {
        charCounter[str[i]]++;
    }
    leafSize = 0;
    for (int i = 0; i < maxSize; i++) {
        if (charCounter[i] != 0) {
            huffmanTree[leafSize].ch = (char)i;
            huffmanTree[leafSize].weight = charCounter[i];
            leafSize++;
        }
    }
    int first, int second;
    for (i = leafSize; i < (2 * leafSize - 1); i++) {
        getMin(first, second, i); // ѡȡ��С������Ԫ��
        merge(first, second, i); // �ϲ�
    }
}

// ѡȡ������С��Ԫ��
void HuffmanCode::getMin(int& first, int& second, int parent)
{
    int weight = 0;
    for (int i = 0; i < parent; i++) {
        if (huffmanTree[i].parent != -1)
            continue;
        if (weight == 0) {
            weight = huffmanTree[i].weight;
            first = i;
        } else if (huffmanTree[i].weight < weight) {
            weight = huffmanTree[i].weight;
            first = i;
        }
    }
    weight = 0;
    for (int i = 0; i < parent; i++) {
        if (huffmanTree[i].parent != -1 || i == first)
            continue;
        if (weight == 0) {
            weight = huffmanTree[i].weight;
            second = i;
        } else if (huffmanTree[i].weight < weight) {
            weight = huffmanTree[i].weight;
            second = i;
        }
    }
}

// �ϲ�
void HuffmanCode::merge(int first, int second, int parent)
{
    huffmanTree[first].parent = huffmanTree[second].parent = parent;
    huffmanTree[parent].leftChild = first;
    huffmanTree[parent].rightChild = second;
    huffmanTree[parent].weight = huffmanTree[first].weight + huffmanTree[second].weight;
}

// ����
void HuffmanCode::encode()
{
    string code;
    for (int i = 0; i < leafSize; i++) {
        int j = i;
        code = "";
        while (huffmanTree[j].parent != -1) {
            if (j == huffmanTree[parent].leftChild)
                code += "0";
            else
                code += "1";
        }
        for (int k = code.size() - 1; k >= 0; k--) {
            huffmanTree[i].code += code[k];
        }
        cout << "�ַ���" << huffmanTree[i].ch << "�ı���Ϊ��" << huffmanTree[i].code
             << endl;
    }
}

void HuffmanCode::decode(string str)
{
    string decode, temp;
    int len = str.size();
    decode = temp = "";
    for (int i = 0; i < str.size(); i++) {
        temp += str[i];
        for (int j = 0; j < leafSize; j++) {
            if (huffmanTree[j].code == temp) {
                decode += huffmanTree[j].ch;
                temp = "";
                break;
            }
        }
        if (i == str.size() - 1 && j == leafSize) {
            cout << "�������" << endl;
            return;
        }
    }
    cout << decode << endl;
}