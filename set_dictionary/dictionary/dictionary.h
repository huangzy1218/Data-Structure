#include <iostream>
const int defaultSize = 26;
template <class Name, class Attribute>
class Dictionary {
public:
    Dictionary(int sz = defaultSize); // 构造函数
    bool member(Name name); // 若 name 在表中，返回 true，否则返回 false
    Attribute* search(Name name); // 搜索 name
    void insert(Name name, Attribute attr); // 添加
    void remove(Name name); // 在字典删除相应的 <name, attr> 对
};