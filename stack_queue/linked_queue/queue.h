const int SIZE = 50;
template <class T>
class Queue {
public:
    Queue() { } // 构造函数
    ~Queue() { } // 析构函数
    virtual bool enQueue(const T& x) = 0; // 新元素x进对列
    virtual bool deQueue(T& x) = 0; // 新元素出队列
    virtual bool getFront(T& x) const = 0; // 读取头节点元素值
    virtual bool isEmpty() const = 0; // 判空
    virtual bool isFull() const = 0; // 判满
    virtual int size() const = 0; // 获取大小
};