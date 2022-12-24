const int maxSize = 50;
template <class T>
class Stack {
public:
    Stack() { } // ���캯��
    virtual void push(const T& x) = 0; // ��ջ
    virtual bool getTop(T& x) = 0; // ��ȡջ��Ԫ��
    virtual bool pop(T& x) = 0; // ��ջ
    virtual bool isEmpty() const = 0; // �п�
    virtual bool isFull() const = 0; // ����
    virtual int size() const = 0; // ��ȡ��С
};