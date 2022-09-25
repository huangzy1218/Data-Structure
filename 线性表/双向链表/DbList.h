#include <iostream>
using namespace std;

template <class T>
struct DblNode {
    T data;
    DblNode<T> *lLink, rLink;
    DblNode(DblNode<T>* left = NULL, DblNode<T>* right = NULL)
            : lLink(left), rLink(r)  {}
    DblNode(T value, DblNode<T>* left = NULL, DblNode<T>* right = NULL)
            : data(T), lLink(left), rLink(r)  {}
};

template <class T>
class DbList: public LinearList<T> {

};