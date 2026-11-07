#include "list_def.h"
#include "graph.h"
#include "html.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>


#define PRINT_HTML(...) fprintf(html_file, __VA_ARGS__)


int HtmlInit(const char* filename, FILE** html_file) {
    assert(filename); assert(html_file);

    //mkdir(
    system("mkdir html_dump\n");

    size_t len = strlen(filename) + sizeof(".html") + sizeof("html_dump/");
    char* fullname = (char*) calloc(len, sizeof(char));
    if (fullname == NULL) {OUTPUT_ERROR("Can't allocate fullname\n");}
    snprintf(fullname, len, "html_dump/%s.html", filename);

    *html_file = fopen(fullname, "w");
    if (*html_file == NULL) {OUTPUT_ERROR("Can't open %s\n", fullname);}

    fprintf(*html_file, "<pre>\n");

    //fclose(html_file);
    //system("cd ..\n");
    return 0;
}

void HtmlExit(FILE* html_file) {
    assert(html_file);
    fclose(html_file);
}


int HtmlDump(const lst_info *lst, FILE* html_file, const char* dump_name) {
    assert(lst); assert(html_file);
    PRINT_HTML("<h3> DUMP %s </h3>\n\n", dump_name);

    HtmlTextDump(lst, html_file);

    if (HtmlPngDump(lst, html_file, dump_name)) return -1;

    PRINT_HTML("<h3> DUMP %s END </h3>\n\n", dump_name);

    return 0;
}

void HtmlTextDump(const lst_info *lst, FILE* html_file) {
    assert(lst); assert(html_file);

    PRINT_HTML("size = %zu, capacity = %zu, clear_ind = %zu\n", lst->size, lst->capacity, lst->clear_ind);

    PRINT_HTML("list pointer: %p\n\n", lst->list);

    PRINT_HTML("List:\n");

    const char* sep = "\t";

    PRINT_HTML("INDEX:\t");
    for (size_t i = 0; i < lst->capacity; i++) {
        PRINT_HTML("%zu%s", i, sep);
    }
    PRINT_HTML("\n");

    PRINT_HTML("DATA:\t");
    for (size_t i = 0; i < lst->capacity; i++) {
        PRINT_HTML(PRINT_ELEM "%s", lst->list[i].data, sep);
    }
    PRINT_HTML("\n");

    PRINT_HTML("NEXT:\t");
    for (size_t i = 0; i < lst->capacity; i++) {
        PRINT_HTML(PRINT_ELEM "%s", lst->list[i].next, sep);
    }
    PRINT_HTML("\n");

    PRINT_HTML("PREV:\t");
    for (size_t i = 0; i < lst->capacity; i++) {
        PRINT_HTML(PRINT_ELEM "%s", lst->list[i].prev, sep);
    }
    PRINT_HTML("\n\n");
}


int HtmlPngDump(const lst_info *lst, FILE* html_file, const char* dump_name) {
    PRINT_HTML("Image:\n");

    size_t len = strlen(dump_name) + sizeof("html_dump/");
    char* full_dump_name = (char*) calloc(len, sizeof(char));
    if (full_dump_name == NULL) {OUTPUT_ERROR("Can't allocate full_dump_name\n");}
    snprintf(full_dump_name, len, "html_dump/%s", dump_name);

    GraphDump(lst, full_dump_name);

    //size_t img_height = lst->capacity * ELEMENT_HEIGHT;
    size_t img_width = lst->capacity * ELEMENT_WIDTH;
    PRINT_HTML("<img src=%s.png width=%zupx>\n\n", dump_name, img_width);

    return 0;
}


#undef PRINT_HTML
