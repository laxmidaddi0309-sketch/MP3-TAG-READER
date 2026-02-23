#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "types.h"
#include "view.h"

char sample_song_fname[100];
FILE *fptr_sample_song;
long get_size(FILE *fptr)
{
    long int size;
    long cur=ftell(fptr);
    fseek(fptr,0,SEEK_END);
    size=ftell(fptr);
    fseek(fptr,cur,SEEK_SET);
    return size;
}
Status read_and_validate(char* str)
{
    char *substr=strstr(str,".mp3");
    if(substr!=NULL)
    {
        if(strcmp(substr,".mp3")!=0)
        {
            printf("ERROR: Invalid Extension PLease enter the valid ectension\n");
            return e_failure;
        }
        else
        {
            strcpy(sample_song_fname,str);
            return e_success;
        }
    }
    else
    return e_failure;
}
Status open_file(char* ptr)
{
    fptr_sample_song=fopen(ptr,"rb");
    if(fptr_sample_song!=NULL)
    return e_success;
    else
    {
        printf("Invalid file cannot opened\n");
        return e_failure;
    }
}
Status do_view(char* argv)
{
    if(open_file(sample_song_fname)!=e_success)
    {
        printf("MP3 file not opened successfully\n");
        return e_failure;
    }
    printf("MP3 file opened SUccessfully\n");
    //Skip the 10 bytes of header
    fseek(fptr_sample_song,10,SEEK_SET);

    long int tag_size=get_size(fptr_sample_song);
    printf("size:%ld\n",tag_size);
    if(read_all_tags(fptr_sample_song)!=e_success)
    {
        printf("Failed MP3 tags\n");
        fclose(fptr_sample_song);
        return e_failure;
    }
    fclose(fptr_sample_song);
    return e_success;
}
Status read_all_tags(FILE *fptr)
{
    int count=0;
    char tags[5];
    int size;
    while(count<6)
    {
        if(fread(tags,1,4,fptr)!=4)
        break;
    
    tags[4]='\0';
    if(fread(&size,4,1,fptr)!=1)
    break;
        endianess(&size,4);
    fseek(fptr,2,SEEK_CUR);
    if(size==0 )
    break;
    char *data=malloc(size+1);
    if(!data)
    return e_failure;
    if(fread(data,1,size,fptr)!=size)
    {
        free(data);
        break;
    }
    data[size]='\0';
    if(print(tags,data+1)==e_success)
    count++;
    free(data);
    }
    return e_success;
}
void endianess(void *p,int size)
{
    unsigned char *ptr=(unsigned char*)p;
    for(int i=0;i<size/2;i++)
    {
        unsigned char temp=ptr[i];
        ptr[i]=ptr[size-i-1];
        ptr[size-i-1]=temp;
    }
}
Status print(char *tag,char *data)
{
    if(strcmp(tag,"TIT2")==0)
    printf("TITLE:%s\n",data);
    else if(strcmp(tag,"TPE1")==0)
    printf("ARTIST:%s\n",data);
    else if(strcmp(tag,"TALB")==0)
    printf("ALBUM:%s\n",data);
    else if(strcmp(tag,"TYER")==0)
    printf("YEAR:%s\n",data);
    else if(strcmp(tag,"TCON")==0)
    printf("GENRE:%s\n",data);
    else if(strcmp(tag,"COMM")==0)
    printf("COMMENT:%s\n",data);
    else 
    {
        printf("NOT matching the tags");
         return 0;
    }
    return e_success;
}
