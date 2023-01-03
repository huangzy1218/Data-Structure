/**
 * @file main.cpp
 * @author Huang Z.Y.
 * @brief a test of skip list
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "skiplist.h"
int main(void)
{
    SkipList<int> list(5, 100);
    // ≤Â»Î
    for (int i = 0; i < 10; i++) {
        list.insert(i, 100 * i);
    }
    list.output();
    // ≤È’“
    list.find(2);
    // …æ≥˝
    list.remove(2);
    list.output();

    return 0;
}
