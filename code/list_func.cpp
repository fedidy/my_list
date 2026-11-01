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

    for (size_t i = 0; i < capacity; i++) {
        lst->list[i].data = POISON;
    }

    for (int i = 0; i < (int) capacity; i++) {
        lst->list[i].next = -i - 1;
    }
    lst->list[capacity - 1].next = -1;

    for (int i = 0; i < (int) capacity; i++) {
        lst->list[i].prev = -i + 1;
    }
    lst->list[1].prev = - (int) capacity + 1;

    lst->list[0].next = 0;
    lst->list[0].prev = 0;
    lst->list[0].data = POISON;
    lst->clear_ind = 1;
    return 0;
}


void ListDtor(lst_info *lst) {
    assert(lst);

    free(lst->list);
    lst->capacity = 0;
    lst->size = 0;
    lst->clear_ind = 0;
}


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
    lst->list[new_ind].prev = (int) ind;

    lst->list[lst->list[ind].next].prev = (int) new_ind;
    lst->list[ind].next = (int) new_ind;

    lst->size++;

    return 0;
}

int GetNewIndex(lst_info *lst, size_t *new_ind) {
    assert(lst);
    assert(new_ind);

    *new_ind = lst->clear_ind;

    if (lst->list[lst->clear_ind].next >= 0) {
        OUTPUT_ERROR("Not initialized index >= 0: %d\n", lst->list[lst->clear_ind].next);
    }
    lst->clear_ind = (size_t) -lst->list[lst->clear_ind].next;

    lst->list[-lst->list[*new_ind].prev].next = - (int) (lst->clear_ind);
    lst->list[lst->clear_ind].prev = lst->list[*new_ind].prev;

    lst->list[*new_ind].data = POISON;
    lst->list[*new_ind].next = 0;
    lst->list[*new_ind].prev = 0;

    return 0;
}


void ListDelete(lst_info *lst, size_t ind, elem_t *elem) {
    assert(lst);
    assert(elem);

    // delete from list
    lst->list[lst->list[ind].prev].next = lst->list[ind].next;
    lst->list[lst->list[ind].next].prev = lst->list[ind].prev;
    *elem = lst->list[ind].data;

    // add to clear list
    lst->list[ind].next = - (int) lst->clear_ind;
    lst->list[ind].prev = lst->list[lst->clear_ind].prev;
    lst->list[ind].data = POISON;

    lst->list[lst->clear_ind].prev = - (int) ind;
    lst->list[- lst->list[ind].prev].next = - (int) ind;

    lst->size--;
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



int ListVerity(const lst_info *lst) {
    assert(lst);

    FILE* verity_output = stdout;

    #define VERITY_OUT(...)\
    fprintf(verity_output, __VA_ARGS__)

    if (lst->size > (size_t) - 100000) {
        OUTPUT_ERROR("Bad size: %zu\n", lst->size);
    }
    if (lst->capacity > (size_t) -100000) {
        OUTPUT_ERROR("Bad capacity: %zu\n", lst->capacity);
    }
    if (lst->clear_ind > (size_t) -100000) {
        OUTPUT_ERROR("Bad clear_ind: %zu\n", lst->clear_ind);
    }

    int ind = lst->list[0].next;
    size_t cnt = 0;
    VERITY_OUT("Data in the right order\n");
    while (ind != 0) {
        VERITY_OUT(PRINT_ELEM " ", lst->list[ind].data);
        ind = lst->list[ind].next;
        cnt++;
        if (cnt > lst->size) {
            OUTPUT_ERROR("Got stuck in list on ind = %d\n", ind);
        }
    }
    VERITY_OUT("\n");

    #undef VERITY_OUT
    return 0;
}

