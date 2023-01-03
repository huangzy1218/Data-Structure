const int maxSize = 50;
template <class T>
class Stack {
public:
    Stack() { } // 构造函数
    virtual void push(const T& x) = 0; // 入栈
    virtual bool getTop(T& x) = 0; // 获取栈顶元素
    virtual bool pop(T& x) = 0; // 出栈
    virtual bool isEmpty() const = 0; // 判空
    virtual bool isFull() const = 0; // 判满
    virtual int size() const = 0; // 获取大小
};