#include <stdio.h>

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        FILE* fp = fopen(argv[i], "r");
        char c;
        int count;
        while (fread(&count, sizeof(int), 1, fp) > 0)
        {
            /* code */
            fread(&c, sizeof(char), 1, fp);
            for (int j = 0; j < count; j++) {
                printf("%c", c);
            }
        }
        fclose(fp);
    }
    return 0;
}
