#include "list_def.h"
#include "graph.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>


int GraphDump(const lst_info *lst, const char* filename) {
    assert(lst); assert(filename);
    GenGraph(lst, filename);

    size_t len = 2 * strlen(filename) + sizeof("dot -Tpng .txt -o .png");
    char* cmd = (char*) calloc(len, sizeof(char));
    if (cmd == NULL) {OUTPUT_ERROR("Can't allocate cmd\n");}
    snprintf(cmd, len, "dot -Tpng %s.txt -o %s.png\n", filename, filename);
    if (system(cmd)) {
        OUTPUT_ERROR("Can't create %s.png\n", filename);
    }
    return 0;
}


int GenGraph(const lst_info *lst, const char* filename) {
    assert(lst); assert(filename);

    size_t len = strlen(filename) + sizeof(".txt");
    char* fullname = (char*) calloc(len, sizeof(char));
    if (fullname == NULL) {OUTPUT_ERROR("Can't allocate fullname\n");}
    snprintf(fullname, len, "%s.txt", filename);

    FILE* gr_file = fopen(fullname, "w");
    if (gr_file == NULL) {OUTPUT_ERROR("Can't open file %s\n", fullname);}

    #define PRINT_GRAPH(...) fprintf(gr_file, __VA_ARGS__)

    PRINT_GRAPH("digraph {\n");

    GenNodes(lst, gr_file);
    GenClearInd(lst, gr_file);

    GenNextArrows(lst, gr_file);
    GenPrevArrows(lst, gr_file);

    //for clear data
    GenNextArrowsClear(lst, gr_file);
    GenPrevArrowsClear(lst, gr_file);


    PRINT_GRAPH("}\n");
    fclose(gr_file);
    return 0;
}

void GenNodes(const lst_info *lst, FILE* gr_file) {
    assert(lst); assert(gr_file);
    for (size_t i = 0; i < lst->capacity; i++) {
        if (lst->list[i].data != POISON) {
            PRINT_GRAPH("\tnode%zu [ shape = Mrecord; style = filled; "
                        "fillcolor = \"#ff80cc\"; color = \"#808080\";\n"
                        "\t\tlabel = \"{ index = %zu | data = " PRINT_ELEM " | { <f1> next = %d | <f2> prev = %d } }\"; ]\n",
                        i, i, lst->list[i].data, lst->list[i].next, lst->list[i].prev);
        } else {
            PRINT_GRAPH("\tnode%zu [ shape = Mrecord; style = filled; "
                        "fillcolor = \"#00ffff\"; color = \"#ff0000\";\n"
                        "\t\tlabel = \"{ index = %zu | data = " PRINT_ELEM " | { <f1> next = %d | <f2> prev = %d } }\"; ]\n",
                        i, i, lst->list[i].data, lst->list[i].next, lst->list[i].prev);
        }
    }

    PRINT_GRAPH("\tedge [ weight = 100000; color = \"#000000\"; ]\n\t"); //will be invisible
    for (size_t i = 0; i < lst->capacity - 1; i++) {
        PRINT_GRAPH("node%zu -> ", i);
    } PRINT_GRAPH("node%zu\n", lst->capacity - 1);
}

void GenClearInd(const lst_info *lst, FILE* gr_file) {
    PRINT_GRAPH("\tnode_clear_ind [ shape = Mrecord; style = filled; "
                "fillcolor = \"#ffff00\"; color = \"#0000ff\";\n"
                "\t\tlabel = \"clear_ind\"; ]\n");
    PRINT_GRAPH("\tedge [ weight = 1; color = \"#0000ff\"; ]\n\t");
    PRINT_GRAPH("\tnode_clear_ind -> node%zu\n", lst->clear_ind);
}

void GenNextArrows(const lst_info *lst, FILE* gr_file) {
    assert(lst); assert(gr_file);
    PRINT_GRAPH("\tedge [ weight = 0; color = \"#00ff00\"; ]\n\t");
    PRINT_GRAPH("node0:<f1> -> ");
    int current = lst->list[0].next;
    for (size_t i = 0; i < lst->size; i++) {
        PRINT_GRAPH("node%d; node%d:<f1> -> ", current, current);
        current = lst->list[current].next;
    } PRINT_GRAPH("node%d\n", current);
}

void GenPrevArrows(const lst_info *lst, FILE* gr_file) {
    assert(lst); assert(gr_file);
    PRINT_GRAPH("\tedge [ weight = 0; color = \"#ff0000\"; ]\n\t");
    PRINT_GRAPH("node0:<f2> -> ");
    int current = lst->list[0].prev;
    for (size_t i = 0; i < lst->size; i++) {
        PRINT_GRAPH("node%d; node%d:<f2> -> ", current, current);
        current = lst->list[current].prev;
    } PRINT_GRAPH("node%d\n", current);
}

void GenNextArrowsClear(const lst_info *lst, FILE* gr_file) {
    assert(lst); assert(gr_file);
    PRINT_GRAPH("\tedge [ weight = 0; color = \"#0000ff\"; ]\n\t");
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
    assert(lst); assert(gr_file);
    PRINT_GRAPH("\tedge [ weight = 0; color = \"#8000ff\"; ]\n\t");
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
