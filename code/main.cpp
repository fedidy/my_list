#include "list_def.h"


int main() {
    lst_info lst = {};

    ListCtor(&lst, 15);

    ListDump(&lst);

    ListInsert(&lst, 0, 43);

    ListDump(&lst);

    ListInsert(&lst, 0, 46);

    ListDump(&lst);

    elem_t a = 0;
    ListDelete(&lst, 1, &a);
    printf(PRINT_ELEM "\n", a);

    ListDump(&lst);

    return 0;
}
