#include "list_def.h"
#include "graph.h"

void GraphDump(const lst_info *lst, const char* filename) {
    FILE* gr_file = fopen(filename, "w");

    #define PRINT_GRAPH(...) fprintf(gr_file, __VA_ARGS__)

    PRINT_GRAPH("digraph {\n");

    for (size_t i = 0; i < lst->capacity; i++) {
        PRINT_GRAPH("\tnode%zu [ shape = Mrecord; style = filled;"
                    "fillcolor = \"#ff80cc\"; color = \"#808080\";\n"
                    "\t\tlabel = \"{ index = %zu | data = " PRINT_ELEM " | { next = %d | prev = %d } }\"; ]\n",
                    i, i, lst->list[i].data, lst->list[i].next, lst->list[i].prev);
    }

    PRINT_GRAPH("\tedge [ weight = 100000; color = \"#000000\"; ]\n\t");
    for (size_t i = 0; i < lst->capacity; i++) {
        PRINT_GRAPH("node%zu->", i);
    } PRINT_GRAPH("node0\n");

    //next
    PRINT_GRAPH("\tedge [ weight = 1; color = \"#00ff00\"; ]\n\t");
    int current = 0;
    for (size_t i = 0; i < lst->size + 1; i++) {
        PRINT_GRAPH("node%d->", current);
        current = lst->list[current].next;
    } PRINT_GRAPH("node%d\n", current);


    //prev
    PRINT_GRAPH("\tedge [ weight = 1; color = \"#ff0000\"; ]\n\t");
    current = 0;
    for (size_t i = 0; i < lst->size + 1; i++) {
        PRINT_GRAPH("node%d->", current);
        current = lst->list[current].prev;
    } PRINT_GRAPH("node%d\n", current);


    PRINT_GRAPH("}\n");
    fclose(gr_file);
    #undef PRINT_GRAPH
}
