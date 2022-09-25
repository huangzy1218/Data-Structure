const int MaxSize = 50;
enum bool { false, true };
template <class T>
class Stack {                               // 栈的类定义 
public:
    Stack();                                // 构造函数
    virtual void Push(const T& x) = 0;      // 新元素x进栈
    virtual void GetTop(T& x) = 0;          // 栈顶元素出栈，由x返回
    virtual bool IsEmpty() const = 0;       // 判断栈为空
    virtual bool IsFull() const = 0;        // 判断栈满
    virtual int GetSize() const = 0;        // 计算栈中元素个数
};