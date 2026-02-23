#ifndef VIEW_H
#define VIEW_H
Status do_view(char* );
Status read_and_validate(char* );
Status open_file(char *);
Status read_all_tags(FILE*);
void endianess(void *,int );
Status print(char*,char*);
#endif