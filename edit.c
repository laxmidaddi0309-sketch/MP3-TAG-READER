#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "types.h"
#include "edit.h"


Status do_editing(char *argv[])
{
    char *option=argv[2];       
    char *new_text=argv[3];
    char *filename=argv[4];
    char tag[5];

    if(strcmp(option,"-t")==0)
        strcpy(tag,"TIT2");
    else if(strcmp(option,"-a")==0)
        strcpy(tag,"TPE1");
    else if(strcmp(option,"-A")==0)
        strcpy(tag, "TALB");
    else if(strcmp(option,"-y")==0)
        strcpy(tag, "TYER");
    else if(strcmp(option,"-m")==0)
        strcpy(tag, "TCON");
    else if(strcmp(option,"-c")==0)
        strcpy(tag,"COMM");
    else
    {
        printf("Invalid edit option\n");
        return e_failure;
    }

    FILE *fptr=fopen(filename, "rb+");
    if(!fptr)
    {
        printf("ERROR:Unable to open file\n");
        return e_failure;
    }
    //skip the header
    fseek(fptr, 10,SEEK_SET);
    if(edit_tag(fptr,tag,new_text)==e_success)
    {
        printf("Updated %s successfully\n",tag);
        fclose(fptr);
        return e_success;
    }
    fclose(fptr);
    return e_failure;
}

Status edit_tag(FILE *fptr,char *edit_tag,char *new_data)
{
    char tag[5];
    int size;
    while(1)
    {
        if(fread(tag,1,4,fptr)!= 4)
            break;
        tag[4]='\0';

        if(fread(&size,4,1,fptr)!=1)
            break;
        endianess(&size, 4);
        //skip flags
        fseek(fptr,2,SEEK_CUR);   
        long pos=ftell(fptr);

        if(strcmp(tag,edit_tag)==0)
        {
            int new_size=strlen(new_data)+1;
            if(new_size>size)
            {
                printf("ERROR:New data too large\n");
                return e_failure;
            }

            char *buffer=malloc(size);
            if (buffer==NULL)
            {
                printf("ERROR:Memory allocation failed\n");
                return e_failure;
            }
            buffer[0]=0; 
            strcpy(buffer+1,new_data);

            fseek(fptr,pos,SEEK_SET);
            fwrite(buffer,1,size,fptr);

            free(buffer);
            return e_success;
        }

        fseek(fptr,size,SEEK_CUR);
    }

    printf("ERROR:Tag not found\n");
    return e_failure;
}