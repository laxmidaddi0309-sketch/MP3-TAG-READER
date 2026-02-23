#ifndef EDIT_H
#define EDIT_H
#include <stdio.h>
#include "types.h"

Status do_editing(char *argv[]);
void endianess(void *,int );
Status edit_tag(FILE *fptr,char *tag,char *new_data);
#endif