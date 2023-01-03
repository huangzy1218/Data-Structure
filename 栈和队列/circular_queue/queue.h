const int SIZE = 50;
template <class T>
class Queue {
public:
    Queue() { } // ���캯��
    ~Queue() { } // ��������
    virtual bool enQueue(const T& x) = 0; // ��Ԫ��x������
    virtual bool deQueue(T& x) = 0; // ��Ԫ�س�����
    virtual bool getFront(T& x) const = 0; // ��ȡͷ�ڵ�Ԫ��ֵ
    virtual bool isEmpty() const = 0; // �п�
    virtual bool isFull() const = 0; // ����
    virtual int size() const = 0; // ��ȡ��С
};