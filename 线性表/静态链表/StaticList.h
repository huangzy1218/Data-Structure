const int MaxSize = 100;            // 静态链表的大小
template <class T>
struct SLinkNode {
    T data;                         // 结点数据
    int link;                       // 结点链接指针
};

template <class T>
class StaticList {
    SLinkNode<T> elem[MaxSize];     
    int avil;                       // 当前可分配空间的首地址
public:
    void InitList();                // 初始化链表
    int Length() const;             // 计算静态链表的长度
    int Search(T x);                // 查找具体结点
    int Locate(int i);              // 查找第i个结点
    bool Append(T x);               // 在表尾追加一个结点
    bool Insert(int i, T x);        // 在第i个结点后插入新结点
    bool Remove(int i);             // 在静态链表删除第i个结点
    bool IsEmpty();                 // 判空
};

// 初始化链表
template <class T>
void StaticList<T>::InitList()
{
    elem[0].link = -1;              // 设置头结点
    avil = 1;                       // 结点首地址从1开始
    for (int i = 1; i < MaxSize - 1; i++) {
        elem[i].link = i + 1;       // 构成空闲链表，下标+1为链接指针地址
    }
    elem[MaxSize-1].link = -1;      // 链表收尾 
}

// 计算静态链表的长度
template <class T>
int StaticList<T>::Length() const
{
    int p = elem[0].link;           // 指向头结点
    int count = 0;
    while (p != -1) {               // 链表不为空或不为表尾
        p = elem[p].link;
        count++;
    }
    return count;           
}

// 判空
template <class T>
bool StaticList<T>::IsEmpty()
{
    return elem[0].link == -1;  
} 

// 查找具体结点
template <class T>
int StaticList<T>::Search(T x)
{
    int p = elem[0].link;
    while (p != -1) {
        if (elem[p].data == x) {
            break;
        } else {
            p = elem[p].link;       // 指向下个结点
        }
    }
    return p;
}

// 定位第i个元素
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
        p = elem[p].link;           // 由于可能存在非表尾插入，故下标+1不一应为下个元素的地址
        j++;
    }
    return p;
}

// 在表尾追加一个结点
template <class T>
bool StaticList<T>::Append(T x)
{
    if (avi == -1) {
        return false;
    }
    int q = avil;                   // 指向当前元素的地址 1 = elem[1].link = 2（下一个分配的地址）
    avil = elem[avil].link;         // 更新当前空间的首地址
    elem[q].data = x;               // elem[1].data = x
    elem[q].link = -1;              // 当前为表尾
    int p = 0;
    while (elem[q].link != -1) {
        p = elem[p].link;
    }
    elem[p].link = q;         
    return true;
}

// 在第i个结点后插入新结点
template <class T>
bool StaticList<T>::Insert(int i, T x)
{
    int p = Locate(i);
    if (p == -1) {
        return false;
    }
    int q = avil;                   // 可分配的首结点
    avil = elem[avil].link;         // 此时地址不连续
    elem[q].data = x;               
    elem[q].link = elem[p].link;    // 链入
    elem[p].link = q;               // i的下个结点为插入的新结点
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