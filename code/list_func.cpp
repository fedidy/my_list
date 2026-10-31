#include "list_def.h"
#include <assert.h>
#include <stdlib.h>

int ListCtor(lst_info *lst, size_t capacity) {
    assert(lst);
    assert(capacity > 0);

    lst->list = (gl_elem*) calloc(capacity, sizeof(gl_elem));
    if (lst->list == NULL) {OUTPUT_ERROR("Can't create list\n");}

    lst->capacity = capacity;
    lst->size = 0;

    for (int i = 0; i < (int) capacity; i++) {
        lst->list[i].next = -i - 1;
    }
    lst->list[capacity - 1].next = 0;
    for (int i = 0; i < (int) capacity; i++) {
        lst->list[i].prev = -i + 1;
    }

    lst->list[0].next = 0;
    lst->list[0].prev = 0;
    lst->list[0].data = POISON;
    lst->clear_ind = 1;
    return 0;
}


//void ListDtor(lst_info *lst);


int ListInsert(lst_info *lst, size_t ind, elem_t elem) {
    assert(lst);
    assert(ind >= 0);
    if (lst->list[ind].next < 0) {
        OUTPUT_ERROR("Got index of non existing element: ind = %zu\n", ind);
    }

    size_t new_ind = 0;
    if (GetNewIndex(lst, &new_ind)) {OUTPUT_ERROR("Didn't get new_ind = %zu\n", new_ind);}

    lst->list[new_ind].data = elem;
    lst->list[new_ind].next = lst->list[ind].next;
    lst->list[new_ind].prev = lst->list[ind].prev;

    lst->list[lst->list[ind].next].prev = (int) new_ind;
    lst->list[ind].next = (int) new_ind;

    lst->size++;

    return 0;
}

int GetNewIndex(lst_info *lst, size_t *new_ind) {
    *new_ind = lst->clear_ind;

    if (lst->list[lst->clear_ind].next >= 0) {
        OUTPUT_ERROR("Not initialized index >= 0: %d\n", lst->list[lst->clear_ind].next);
    }
    lst->clear_ind = (size_t) -lst->list[lst->clear_ind].next;

    lst->list[lst->clear_ind].prev = 0;

    lst->list[*new_ind].data = POISON;
    lst->list[*new_ind].next = 0;
    lst->list[*new_ind].prev = 0;

    return 0;
}



void ListDump(const lst_info *lst) {
    assert(lst);

    FILE* dump_output = stdout;

    #define DUMP_OUT(...)\
    fprintf(dump_output, __VA_ARGS__)

    DUMP_OUT("------------------ lst_info DUMP ------------------\n");

    DUMP_OUT("size = %zu, capacity = %zu, clear_ind = %zu\n", lst->size, lst->capacity, lst->clear_ind);

    DUMP_OUT("list pointer: %p\n", lst->list);

    DUMP_OUT("List:\n");

    const char* sep = "\t";

    DUMP_OUT("DATA:\t");
    for (size_t i = 0; i < lst->capacity; i++) {
        DUMP_OUT(PRINT_ELEM "%s", lst->list[i].data, sep);
    }
    DUMP_OUT("\n");

    DUMP_OUT("NEXT:\t");
    for (size_t i = 0; i < lst->capacity; i++) {
        DUMP_OUT(PRINT_ELEM "%s", lst->list[i].next, sep);
    }
    DUMP_OUT("\n");

    DUMP_OUT("PREV:\t");
    for (size_t i = 0; i < lst->capacity; i++) {
        DUMP_OUT(PRINT_ELEM "%s", lst->list[i].prev, sep);
    }
    DUMP_OUT("\n");

    DUMP_OUT("------------------ lst_info END ------------------\n");

    #undef DUMP_OUT
}
