#include "GenList.h"

int main()
{
    GenList<char> genList;
    SeqList<char> listName;
    SeqList<GenListNode<char> *> node;
    genList.createList(cin, genList.first, listName, node);

    return 0;
}