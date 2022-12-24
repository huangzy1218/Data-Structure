const int MaxSize = 100; // ��̬����Ĵ�С
template <class T>
struct SLinkNode {
    T data; // �������
    int link; // �������ָ��
};

template <class T>
class StaticList {
    SLinkNode<T> elem[MaxSize];
    int avil; // ��ǰ�ɷ���ռ���׵�ַ
public:
    void InitList(); // ��ʼ������
    int Length() const; // ���㾲̬����ĳ���
    int Search(T x); // ���Ҿ�����
    int Locate(int i); // ���ҵ�i�����
    bool Append(T x); // �ڱ�β׷��һ�����
    bool Insert(int i, T x); // �ڵ�i����������½��
    bool Remove(int i); // �ھ�̬����ɾ����i�����
    bool IsEmpty(); // �п�
};

// ��ʼ������
template <class T>
void StaticList<T>::InitList()
{
    elem[0].link = -1; // ����ͷ���
    avil = 1; // ����׵�ַ��1��ʼ
    for (int i = 1; i < MaxSize - 1; i++) {
        elem[i].link = i + 1; // ���ɿ��������±�+1Ϊ����ָ���ַ
    }
    elem[MaxSize - 1].link = -1; // ������β
}

// ���㾲̬����ĳ���
template <class T>
int StaticList<T>::Length() const
{
    int p = elem[0].link; // ָ��ͷ���
    int count = 0;
    while (p != -1) { // ����Ϊ�ջ�Ϊ��β
        p = elem[p].link;
        count++;
    }
    return count;
}

// �п�
template <class T>
bool StaticList<T>::IsEmpty()
{
    return elem[0].link == -1;
}

// ���Ҿ�����
template <class T>
int StaticList<T>::Search(T x)
{
    int p = elem[0].link;
    while (p != -1) {
        if (elem[p].data == x) {
            break;
        } else {
            p = elem[p].link; // ָ���¸����
        }
    }
    return p;
}

// ��λ��i��Ԫ��
template <class T>
int StaticList<T>::Locate(int i)
{
    if (i < 0) {
        return -1;
    }
    if (i == 0) {
        return 0;
    }
    int j = 1, p = elem[0].link;
    while (p != -1 && j < i) {
        p = elem[p].link; // ���ڿ��ܴ��ڷǱ�β���룬���±�+1��һӦΪ�¸�Ԫ�صĵ�ַ
        j++;
    }
    return p;
}

// �ڱ�β׷��һ�����
template <class T>
bool StaticList<T>::Append(T x)
{
    if (avi == -1) {
        return false;
    }
    int q = avil; // ָ��ǰԪ�صĵ�ַ 1 = elem[1].link = 2����һ������ĵ�ַ��
    avil = elem[avil].link; // ���µ�ǰ�ռ���׵�ַ
    elem[q].data = x; // elem[1].data = x
    elem[q].link = -1; // ��ǰΪ��β
    int p = 0;
    while (elem[q].link != -1) {
        p = elem[p].link;
    }
    elem[p].link = q;
    return true;
}

// �ڵ�i����������½��
template <class T>
bool StaticList<T>::Insert(int i, T x)
{
    int p = Locate(i);
    if (p == -1) {
        return false;
    }
    int q = avil; // �ɷ�����׽��
    avil = elem[avil].link; // ��ʱ��ַ������
    elem[q].data = x;
    elem[q].link = elem[p].link; // ����
    elem[p].link = q; // i���¸����Ϊ������½��
    return true;
}

template <class T>
bool StaticList<T>::Remove(int i)
{
    int p = Locate(i - 1);
    if (p == -1) {
        return false;
    }
    int q = elem[p].link;
    elem[p].link = elem[q].link;
    elem[q].link = avil;
    avil = q;
    return true;
}