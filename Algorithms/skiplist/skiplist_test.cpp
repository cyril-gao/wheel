#include <stdio.h>
#include "skiplist.h"
#include "check.h"

int main()
{
    {
        const size_t limit = 10000;
        Skiplist<size_t> slist;
        for (size_t i = 0; i < limit; ++i) {
            slist.insert(i);
            examine(slist.contains(i), "Sliplist::contains is failed for the argument: %zu\n", i);
        }
        for (size_t i = 0; i < limit; ++i) {
            examine(slist.erase(i), "Sliplist::erase is failed for the argument: %zu\n", i);
            examine(!slist.contains(i), "Sliplist::contains is failed for the argument: %zu\n", i);
        }
    }
    return 0;
}
