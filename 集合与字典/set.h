template <class T>
class Set {
public:
    Set() {}; // ���췽��
    virtual void makeEmpty() = 0; // �ÿռ���
    virtual bool addMember(const T x) = 0; // ����Ԫ��
    virtual bool deleteMember(const T x) = 0; // ɾ��Ԫ��
    virtual Set<T>& insersectWith(const Set<T>& r) = 0; // ������
    virtual Set<T>& unionWith(const Set<T>& r) = 0; // ������
    virtual Set<T>& differenceFrom(const Set<T>& r) = 0; // ������
    virtual bool contains(const T x) = 0; // �ж��Ƿ���Ԫ�� x
    virtual bool subSet(const Set<T>& r) = 0; // �ж��Ƿ�Ϊ�Ӽ�
    virtual bool operator==(const Set<T>& r); // �жϼ����Ƿ����
};