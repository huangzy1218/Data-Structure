#include <iostream>
using namespace std;

template <class T>
struct DblNode {
    T data;
    DblNode<T> *lLink, rLink;											// 前驱（左链），后继（右链）指针
    DblNode(DblNode<T>* left = NULL, DblNode<T>* right = NULL)
            : lLink(left), rLink(r) {}                                  // 构造函数
    DblNode(T value, DblNode<T>* left = NULL, DblNode<T>* right = NULL)
            : data(T), lLink(left), rLink(r) {}                         // 构造函数
};

template <class T>
class DblList: public LinearList<T> {
public:
	DblList(T uniqueVal);                                        	// 构造函数，建立附加头结点
    ~DblList();    													// 析构函数
	int Length() const;												// 计算链表长度
	bool IsEmpty(); { return first->rlink == first; }				// 判空，头结点的下一个结点仍为头结点
	DblNode<T>* GetHead() const { return first; }					// 取附加头结点地址
	void SetHead(DblNode<T>* ptr); { first = ptr; }					// 设置头结点地址
	DblNode<T>* Search(const T& x);									// 在链表后继方向继续寻找x
	DblNode<T>* Locate(int i, int d);								// 在链表定位编号为i的结点，d=0前驱方向，否则后继方向
	bool Insert(int i, const T& x, int d);							// 在第i个值后插入新结点，d=0前驱方向，否则后继方向
	bool Remove(int i, T& x, int d);								// 删除第i个结点，d=0前驱方向，否则后继方向
private:
	DblNode<T>* first;	                                                           
};

// 构造函数，建立附加头结点
template <class T>
DblList<T>::DblList(T uniqueVal) 
{
	first = new DblNode<T>(uniqueVal);
	if (first == NULL) {
		cerr << "内存分配失败" << endl;
		exit(1);
	}
	first->rLink = first->lLink = first;							// 前驱后继均为其本身，类似于循环链表
}

// 计算链表长度
template <class T>
int DblList<T>::Length() const
{
	DblNode<T>* current = first->rLink;
	int count = 0;
	while (current != first) {
		current = current->rLink;									// 类似于循环链表，或单链表，将其rLink视为单链表中的link
		++count;
	}
	return count;
}

// 在链表定位编号为i的结点，d=0前驱方向，否则后继方向
template <class T>
DblNode<T>* DblList<T>::Locate(int i, int d)
{
	if (first->rLink == first || i == 0) {							// 若寻找头结点或链表为空
		return first;
	}
	DblNode<T>* current;
	if (d == 0) {													// 当前结点指向头结点的前驱结点
		current = first->lLink;
	} else {
		current = first->rLink;										// 当前结点指向头结点的后继结点
	}
	for (int j = 1; j < i; j++) {
		if (current == first) {										// 超出索引范围
			break;
		} else if (d == 0) {
			current = current->lLink;								// 前驱寻找
		} else {
			current = current->rLink;								// 后继寻找
		}
	}
	
	if (current != first) {
		return current;
	} else {
		return NULL;
	}
}

// 在第i个值后插入新结点，d=0前驱方向，否则后继方向
template <class T>
bool *DblList<T>::Insert(int i, const T& x, int d)
{
	DblNode<T>* current = Locate(i, d);								// 定位当前结点
	if (current == NULL) {
		return false;
	}
	DblNode<T>* newNode = DblNode<T>(x);
	if (newNode == NULL) {
		cerr << "内存分配失败" << endl;
		exit(0);
	}
	if (d == 0) {													// 前驱插入
		newNode->lLink = current->lLink;							// 新结点的前驱结点为当前结点的前驱结点
		current->lLink = newNode;									// 当前结点的前驱结点为新节点
		newNode->lLink->rLink = newNode;							// 新节点的前驱结点的后继结点为其本身
		newNode->rLink = current;									// 新节点的后继结点为当前结点
	} else {														// 后继插入
		newNode->rLink = current->rLink;							// 新结点的后继结点为当前结点的后继结点
		current->rLink = newNode;									// 新结点的后继结点为当前结点的后继结点
		newNode->rLink->lLink = newNode;							// 新结点的后继结点的前驱结点为其本身
		newNode->lLink = current;									// 新节点的前驱结点为当前结点（首尾呼应）
	}
	return true;
}

// 删除第i个结点，d=0前驱方向，否则后继方向
template <class T>
bool DblList<T>::Remove(int i, T& x, int d)
{
	DblNode<T>* current = Locate(i, d);
	if (current == NULL) {
		return false;
	}
	current->rLink->lLink = current->lLink;
	current->lLink->rLink = current->rLink;
	x = current->data;
	delete current;
	return true;
}
\