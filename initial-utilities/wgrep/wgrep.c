#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // printf("%d\n", argc);
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }
    FILE *p ;
    if (argc == 3) {
        p = fopen(argv[2], "r");
        if (p == NULL) {
            printf("wgrep: cannot open file\n");
            return 1;
        }
    } else if (argc == 2) {
        p = stdin;
        if (p == NULL) {
            printf("wgrep: searchterm [file ...]\n");
            return 1;
        }
    }
    char buf[1024];
    while (fgets(buf, 1024, p) != NULL)
    {
        /* code */
        char line[1024];
        strcpy(line, buf);
    	char *w = strtok(buf, " ");
        int has = 0;
        while (w != NULL) {
            if (strstr(w, argv[1])){
                has = 1;
                break;
            }
            w = strtok(NULL, " "); 
        }
        if (has) printf("%s", line);
    }
    
    return 0;
}
