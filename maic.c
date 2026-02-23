#include<stdio.h>
#include<string.h>
#include "types.h"
#include "view.h"
#include "edit.h"
OperationType check_operation(char* );
int main(int argc,char* argv[])
{
    if(argc>=3)
    {
        if(check_operation(argv[1])==e_view)
        {
           if(read_and_validate(argv[2])==e_success)
           {
                if(do_view(argv[2])==e_success)
                printf("###Viewing Completed###\n");
                else
                return 0;
           }
           else
           {
            printf("Invalid Please enter the valid Extension\n");
            return 0;
           }
        }
       else if(check_operation(argv[1]) == e_edit)
    {
        if(argc< 5)
        {
            printf("Invalid arguments for edit\n");
            return 0;
        }
        else if(read_and_validate(argv[4])==e_success)
        {
            if(do_editing(argv)==e_success)
            printf("### Editing Completed ###\n");
        }
        else
        {
            printf("Invalid file extension\n");
            return 0;
        }
    }
        else if(check_operation(argv[1])==e_help)
        {
            printf("-----------------------HELP MENU-------------------\n");
            printf("1. -v -> view mp3 file contents\n");
            printf("2. -e -> edit mp3 file contents\n");
            printf("\t2.1 -t ->to edit song title\n");
            printf("\t2.2 -a ->to edit artist name\n");
            printf("\t2.3 -A ->to edit album name\n");
            printf("\t2.4 -y ->to edit year\n");
            printf("\t2.1 -m ->to edit content\n");
            printf("\t2.1 -c ->to edit comment\n");
            printf("---------------------------------------------------\n");
        }
        else
        {
             printf("Invalid Command line arguments");
             return 0;
        }
    }
    else
    {
        printf("-------------------------------------------------------------------------------\n");
        printf("ERROR: ./a.out:INVALID ARGUMENTS\nUSAGE:\n");
        printf("To view please pass like: ./a.out -v mp2filename\n");
        printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
        printf("To get help pass like: ./a.out --help\n");
        printf("-------------------------------------------------------------------------------\n");
    }
    
}
   OperationType check_operation(char* symbol)
   {
    if(strcmp(symbol,"-v")==0)
    return e_view;
    else if(strcmp(symbol,"-e")==0)
    return e_edit;
    else if(strcmp(symbol,"--h")==0)
    return e_help;
    return e_unsupported;
   }
