#include "list_def.h"
#include "graph.h"

void GraphDump(const lst_info *lst, const char* filename) {
    FILE* gr_file = fopen(filename, "w");

    #define PRINT_GRAPH(...) fprintf(gr_file, __VA_ARGS__)

    PRINT_GRAPH("digraph {\n");

    for (size_t i = 0; i < lst->capacity; i++) {
        PRINT_GRAPH("\tnode%zu [ shape = Mrecord; style = filled;"
                    "fillcolor = \"#ff80cc\"; color = \"#808080\";\n"
                    "\t\tlabel = \"{ data = " PRINT_ELEM " | next = %d | prev = %d }\"; ]\n",
                    i, lst->list[i].next, lst->list[i].prev, lst->list[i].data);
    }



    PRINT_GRAPH("}\n");
    fclose(gr_file);
    #undef PRINT_GRAPH
}
