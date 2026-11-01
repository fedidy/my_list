#include "list_def.h"
#include "graph.h"

void GraphDump(const lst_info *lst, const char* filename) {
    FILE* gr_file = fopen(filename, "w");
    assert(lst); assert(filename);
    assert(lst); assert(filename);

    #define PRINT_GRAPH(...) fprintf(gr_file, __VA_ARGS__)

    PRINT_GRAPH("digraph {\n");

    GenNodes(lst, gr_file);
    //next
    GenNextArrows(lst, gr_file);
    //prev
    GenPrevArrows(lst, gr_file);
    //for clear data
    //next
    GenNextArrowsClear(lst, gr_file);
    //prev
    GenPrevArrowsClear(lst, gr_file);


    PRINT_GRAPH("}\n");
    fclose(gr_file);
}


void GenNodes(const lst_info *lst, FILE* gr_file) {
    assert(lst); assert(gr_file);
    for (size_t i = 0; i < lst->capacity; i++) {
        PRINT_GRAPH("\tnode%zu [ shape = Mrecord; style = filled;"
                    "fillcolor = \"#ff80cc\"; color = \"#808080\";\n"
                    "\t\tlabel = \"{ index = %zu | data = " PRINT_ELEM " | { <f1> next = %d | <f2> prev = %d } }\"; ]\n",
                    i, i, lst->list[i].data, lst->list[i].next, lst->list[i].prev);
    }

    PRINT_GRAPH("\tedge [ weight = 100000; color = \"#000000\"; ]\n\t"); //will be invisible
    for (size_t i = 0; i < lst->capacity; i++) {
        PRINT_GRAPH("node%zu -> ", i);
    } PRINT_GRAPH("node0\n");
}

void GenNextArrows(const lst_info *lst, FILE* gr_file) {
    PRINT_GRAPH("\tedge [ weight = 1; color = \"#00ff00\"; ]\n\t");
    assert(lst); assert(gr_file);
    PRINT_GRAPH("node0:<f1> -> ");
    int current = lst->list[0].next;
    for (size_t i = 0; i < lst->size; i++) {
        PRINT_GRAPH("node%d; node%d:<f1> -> ", current, current);
        current = lst->list[current].next;
    } PRINT_GRAPH("node%d\n", current);
}

void GenPrevArrows(const lst_info *lst, FILE* gr_file) {
    PRINT_GRAPH("\tedge [ weight = 1; color = \"#ff0000\"; ]\n\t");
    assert(lst); assert(gr_file);
    PRINT_GRAPH("node0:<f2> -> ");
    int current = lst->list[0].prev;
    for (size_t i = 0; i < lst->size; i++) {
        PRINT_GRAPH("node%d; node%d:<f2> -> ", current, current);
        current = lst->list[current].prev;
    } PRINT_GRAPH("node%d\n", current);
}

void GenNextArrowsClear(const lst_info *lst, FILE* gr_file) {
    PRINT_GRAPH("\tedge [ weight = 1; color = \"#0000ff\"; ]\n\t");
    assert(lst); assert(gr_file);
    PRINT_GRAPH("node%d:<f1> -> ", (int) lst->clear_ind);
    int current = - lst->list[lst->clear_ind].next;
    if (lst->capacity - lst->size > 1) {
        for (size_t i = 0; i < (lst->capacity - lst->size - 2); i++) {
            PRINT_GRAPH("node%d; node%d:<f1> -> ", current, current);
            current = - lst->list[current].next;
        } PRINT_GRAPH("node%d\n", current);
    }
}

void GenPrevArrowsClear(const lst_info *lst, FILE* gr_file) {
    PRINT_GRAPH("\tedge [ weight = 1; color = \"#8000ff\"; ]\n\t");
    assert(lst); assert(gr_file);
    PRINT_GRAPH("node%d:<f2> -> ", (int) lst->clear_ind);
    int current = - lst->list[lst->clear_ind].prev;
    if (lst->capacity - lst->size > 1) {
        for (size_t i = 0; i < (lst->capacity - lst->size - 2); i++) {
            PRINT_GRAPH("node%d; node%d:<f2> -> ", current, current);
            current = - lst->list[current].prev;
        } PRINT_GRAPH("node%d\n", current);
    }
}


#undef PRINT_GRAPH
