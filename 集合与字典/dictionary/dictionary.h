#include <iostream>
const int defaultSize = 26;
template <class Name, class Attribute>
class Dictionary {
public:
    Dictionary(int sz = defaultSize); // ���캯��
    bool member(Name name); // �� name �ڱ��У����� true�����򷵻� false
    Attribute* search(Name name); // ���� name
    void insert(Name name, Attribute attr); // ���
    void remove(Name name); // ���ֵ�ɾ����Ӧ�� <name, attr> ��
};