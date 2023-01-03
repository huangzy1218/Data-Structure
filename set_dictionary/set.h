template <class T>
class Set {
public:
    Set() {}; // 构造方法
    virtual void makeEmpty() = 0; // 置空集合
    virtual bool addMember(const T x) = 0; // 加入元素
    virtual bool deleteMember(const T x) = 0; // 删除元素
    virtual Set<T>& insersectWith(const Set<T>& r) = 0; // 交运算
    virtual Set<T>& unionWith(const Set<T>& r) = 0; // 并运算
    virtual Set<T>& differenceFrom(const Set<T>& r) = 0; // 差运算
    virtual bool contains(const T x) = 0; // 判断是否含有元素 x
    virtual bool subSet(const Set<T>& r) = 0; // 判断是否为子集
    virtual bool operator==(const Set<T>& r); // 判断集合是否相等
};