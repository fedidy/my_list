#ifndef GRAPH_H
#define GRAPH_H

#include "list_def.h"

void GraphDump(const lst_info *lst, const char* filename);

void GenNodes(const lst_info *lst, FILE* gr_file);
void GenNextArrows(const lst_info *lst, FILE* gr_file);
void GenPrevArrows(const lst_info *lst, FILE* gr_file);
void GenNextArrowsClear(const lst_info *lst, FILE* gr_file);
void GenPrevArrowsClear(const lst_info *lst, FILE* gr_file);

#endif
