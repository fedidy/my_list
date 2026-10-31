#include "list_def.h"


int main() {
    lst_info lst = {};

    ListCtor(&lst, 15);

    ListDump(&lst);

    return 0;
}
