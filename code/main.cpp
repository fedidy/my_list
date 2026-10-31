#include "list_def.h"


int main() {
    lst_info lst = {};

    ListCtor(&lst, 15);

    ListDump(&lst);

    ListInsert(&lst, 0, 43);

    ListDump(&lst);

    ListInsert(&lst, 0, 46);

    ListDump(&lst);

    return 0;
}
