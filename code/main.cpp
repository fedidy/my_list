#include "list_def.h"
#include "graph.h"
#include "html.h"


int main() {
    FILE* html_file = NULL;
    HtmlInit("dumpx", &html_file);

    lst_info lst = {};
    ListCtor(&lst, 15);
    HtmlDump(&lst, html_file, "dump1");

    ListInsert(&lst, 0, 43);
    HtmlDump(&lst, html_file, "dump2");

    ListInsert(&lst, 0, 46);
    ListVerity(&lst);
    HtmlDump(&lst, html_file, "dump3");

    ListPush(&lst, 67);
    ListPush(&lst, 148);
    ListVerity(&lst);
    HtmlDump(&lst, html_file, "dump4");

    elem_t a = 0;
    ListDelete(&lst, 1, &a);
    printf(PRINT_ELEM "\n", a);

    ListVerity(&lst);
    HtmlDump(&lst, html_file, "dump5");

    elem_t b = 0;
    ListPop(&lst, &b);
    printf(PRINT_ELEM "\n", b);
    HtmlDump(&lst, html_file, "dump6");

    ListPush(&lst, 432);
    ListPush(&lst, 42);
    ListInsert(&lst, 6, 12);
    ListPush(&lst, 56);
    ListPush(&lst, 54);
    ListPush(&lst, 56466);
    ListPush(&lst, 90);

    ListDelete(&lst, 8, &b);

    HtmlDump(&lst, html_file, "dump7");

    GraphDump(&lst, "graph");

    ListDtor(&lst);

    HtmlExit(html_file);

    return 0;
}
