#ifndef LIST_DEF_H
#define LIST_DEF_H

#include <stdio.h>

#define OUTPUT_ERROR(text, ...)\
fprintf(stderr, "%s:%d:" text, __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__); return -1

const int POISON = 676767;

typedef int elem_t;
#define PRINT_ELEM "%d"

typedef struct _glist_elem {
    elem_t data;
    int next;
    int prev;
} gl_elem;

typedef struct _mylist_info {
    gl_elem *list;
    size_t size;
    size_t capacity;
    size_t clear_ind;
} lst_info;

int ListCtor(lst_info *lst, size_t size);
void ListDtor(lst_info *lst);
int ListInsert(lst_info *lst, size_t ind, elem_t elem);
int ListDel(lst_info *lst, size_t ind, elem_t *elem);
int ListPush(lst_info *lst, elem_t elem);
int ListPop(lst_info *lst, elem_t *elem);
void ListDump(const lst_info *lst);


#endif
