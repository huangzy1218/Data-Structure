#include <iostream>
#include <cstdlib>
using namespace std;
template <class T>
struct LinkNode {
    T data;
    LinkNode<T>* link;
    LinkNode(LinkNode<T>* ptr = NULL)  { link = ptr; }
    LinkNode(const T& item, LinkNode* ptr = NULL)
    {
        data = item;
        link = ptr;
    }
};

template <class T>
class List: public LinearList<T> {
    List() { first = new LinkNode<T>(); }                     // 构造函数
    List(const T& x) { first = new LinkNode<T>(x); }          // 构造函数
    List(List<T>& L);                                         // 复制构造函数
    ~List() { makeEmpty(); }                                  // 析构函数
    void MakeEmpty();                                         // 将链表置空
    int Length() const;                                       // 计算链表长度
    LinkNode<T>* GetHead() const  { return first; }           // 返回头结点地址
    LinkNode<T>* Search(T x);                                 // 搜索含x的元素的地址
    LinkNode<T>* Locate(int i);                               // 定位第i个元素
    bool GetData(int i, T& x) const;                          // 取出第i个元素值
    void SetData(int i, T& x);                                // 将第i个元素值设为x
    bool Insert(int i, T& x);                                 // 在第i个元素后插入x
    bool Remove(int i, T& x);                                 // 删除第i个元素，并返回其值x
    bool IsEmpty() const  { return first->link == NULL; }     // 判表空
    bool IsFull() const  { return false; }                    // 判表满
    void Sort();                                              // 排序
    void Input();                                             // 输入 
    void Output();                                            // 输出
    List<T>& operator=(List<T>& L);                           // 重载函数：赋值
protected:
    LinkNode<T>* first;
};

// 复制构造函数
template <class T>
List<T>::List(List<T>& L)
{
    T value;
    LinkNode<T>* srcptr = L.GetHead();                      // 指向源链表
    LinkNode<T>* destptr = this->GetHead();                 // 指向当前链表
    
    while (srcptr->link != NULL) {                          // 依次复制
        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(data);
        srcptr = srcptr->link;
        destptr = destptr->link;
    }   ,
    destptr->link = NULL;                                   // 标志链表尾
}
// 将链表置空
template <class T>
void List<T>::MakeEmpty()
{
    LinkNode<T>* q;                                         // 记录删除结点
    while (first->link != NULL) {
        q = first->next;
        first->link = q->link;                              // 头结点的下个结点指向删除结点的下一个，若为NULL类似
        delete q;
    }
}

// 计算链表长度
template <class T>
int List<T>::Length() const
{
    int count = 0;                                          // 计算表长
    LinkNode<T>* count = first->link;

    while (ptr != NULL) {
        ++count;
    }
    return count;
}

// 搜索含x的元素的地址
template <class T>
LinkNode<T>* Search(T x)
{
    LinkNode<T>* ptr = first->link;

    while (ptr != NULL) {
        if (ptr->data == x) {
            break;
        } else {
            ptr = ptr->link;
        }
    }
    return ptr;                                             // 单一出口原则
}

// 定位第i个元素
template <class T>
LinkNode<T>* List<T>::Locate(int i)
{
    if (i < 0) {                                            // 下标不合法
        return NULL;
    }
    int count = 0;                                          // 记录当前元素下标
    LinkNode<T>* ptr = first->link;
    while (ptr != NULL && count < i) {                      // 注意逻辑顺序
        ptr = ptr->link;
        ++count;
    }
    return ptr;
}
// 取出第i个元素值
template <class T>
bool List<T>::GetData(int i, T& x) const
{
    if (i < 0) {
        return false;
    }
    LinkNode* ptr = Locate(i);                              // 借助已有函数实现定位
    if (ptr != NULL) {
        x = ptr->data;
        return true;
    } else {
        return false;
    }
}

// 将第i个元素值设为x
template <class T>
void List<T>::SetData(int i, T& x)
{
    if (i < 0) {
        return;
    }
    LinkNode* ptr = Locate(i);                              // 借助已有函数实现定位
    if (ptr != NULL) {
        ptr->data = x;
    } else {
        return;
    }
}

// 在第i个元素后插入x
template <class T>
bool List<T>::Insert(int i, T& x)
{
    if (i < 0) {
        return false;
    }
    LinkNode<T>* ptr = Locate(i);               
    if (ptr == NULL) {                                      // 位于表尾之后，无法插入
        return false;
    } 
    LinkNode<T>* newNode = new LinkNode(x);
    if (newNode == NULL) {
        cerr << "内存分配失败" << endl;
        exit(1);
    } else {
        newNode->link = ptr->link;
        ptr->link = newNode;
    }
    return true;
}

 // 删除第i个元素，并返回其值x
 template <class T>
 bool List<T>::Remove(int i, T& x)
 {
    if (i < 0) {
        return false;
    }
    LinkNode<T>* current = Locate(i - 1);                   // 删除元素的前一个结点
    if (current == NULL || current->link == NULL) {         // 位于表尾之后，无法删除
        return false;
    } else {
        LinkNode<T>* delPtr = current->link;
        current->link = delPtr->link;
        x = delPtr->data;
        delete delPtr;
        return true;
    }     
 }

// 输出
template <class T>
void List<T>::Output()
{
    LinkNode<T>* current = first->link;

    while (current != NULL) {                               // 格式化输出
        cout << current->data << " ";
        current = current->link;
    }
    cout << endl;
}

// 输入
template <class T>
void List<T>::Input()
{
    int n;
    T x;
    cout << "开始建立单链表，请输入表中元素个数" << endl;
    cin >> n;
    LinkNode<T>* current = head;                            //  不断创建新结点保存输入数据
    while (n--) {
        cin >> x;
        current->link = new LinkNode<T>(x);
        current = current->link;
    }
    current->link = NULL;
}