#include<stdio.h>
#include<string.h>
#include<stdint.h>

typedef int8_t byte;

#define INVALID_INPUT_FORMAT -1
#define SOURCE_FILE_DOES_NOT_EXIST -2

/* format ./cp source destination */
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Format: ./cp <source> <destination> \n");
        return INVALID_INPUT_FORMAT;
    }

    /* Opening the source file */
    FILE *src = fopen(argv[1],"rb");
    if(src == NULL)
    {
        printf("The source file doesn't exist!\n");
        return SOURCE_FILE_DOES_NOT_EXIST;
    }

    /* Copying from the source to the destination completely rewrites it contents */

    /* Opening the destination file */
    FILE *dst = fopen(argv[2],"wb");

    byte character;
    while(fread(&character,sizeof(byte),1,src) != 0)
    {
        fwrite(&character,sizeof(byte),1,dst);
    }

    fclose(src);
    fclose(dst);
}
