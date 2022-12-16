#include <stdio.h>
#include <stdlib.h>

void diwrite(int n,char c)
{
    if(n >= 1) fwrite(&n,4,1,stdout);
    fwrite(&c,1,1,stdout);
}

int main(int argc,char *argv[])
{
    char lastc = 0;
    char curc;
    int nread;
    int count = 0;
    FILE *fp = stdin;

    int i = 1;
    if(argc==1)
    {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }
    for(;i<argc;i++)
    {
        fp = fopen(argv[i],"rb");
        if(fp == NULL)
        {
            printf("wzip: cannot open file\n");
            return 1;
        }

        while((nread = fread(&curc,1,1,fp))==1)
        {
            if(curc==lastc)
            {
                count++;
                continue;
            }
            if(count!=0)
                diwrite(count,lastc);
            count = 1;
            lastc = curc;
        }
        fclose(fp);
    }
    diwrite(count,lastc);
    return 0;
}