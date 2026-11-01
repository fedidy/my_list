#include "list_def.h"
#include "graph.h"


int main() {
    lst_info lst = {};

    ListCtor(&lst, 15);
    ListDump(&lst);

    ListInsert(&lst, 0, 43);
    ListDump(&lst);

    ListInsert(&lst, 0, 46);
    ListVerity(&lst);
    ListDump(&lst);

    ListPush(&lst, 67);
    ListPush(&lst, 148);
    ListVerity(&lst);
    ListDump(&lst);

    elem_t a = 0;
    ListDelete(&lst, 1, &a);
    printf(PRINT_ELEM "\n", a);

    ListVerity(&lst);
    ListDump(&lst);

    elem_t b = 0;
    ListPop(&lst, &b);
    printf(PRINT_ELEM "\n", b);
    ListDump(&lst);

    ListPush(&lst, 432);
    ListPush(&lst, 42);
    ListInsert(&lst, 6, 12);
    ListPush(&lst, 56);
    ListPush(&lst, 54);
    ListPush(&lst, 56466);
    ListPush(&lst, 90);

    ListDelete(&lst, 8, &b);

    ListDump(&lst);

    GraphDump(&lst, "graph.txt");

    ListDtor(&lst);

    return 0;
}
