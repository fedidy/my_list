#ifndef HTML_H
#define HTML_H

//const int IMG_WIDTH = 200;
const int ELEMENT_HEIGHT = 50;

int HtmlInit(const char* filename, FILE** html_file);
void HtmlExit(FILE* html_file);
int HtmlDump(const lst_info *lst, FILE* html_file, const char* dump_name);
void HtmlTextDump(const lst_info *lst, FILE* html_file);
int HtmlPngDump(const lst_info *lst, FILE* html_file, const char* dump_name);

#endif
