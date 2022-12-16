#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

FILE *read, *out;
void reverse() {
    char buf[1024];
    if (feof(read)) return;
    fgets(buf, 1024, read);
    reverse();
    fprintf(out,"%s", buf);
}
struct stat a, b;
int main(int argc, char const *argv[])
{
    out = stdout;
    if (argc >= 2 && argc <= 3) {
        read = fopen(argv[1], "r");
        if (read == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }
    if (argc == 3) {
        out = fopen(argv[2], "w");
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        stat(argv[1], &a);
        stat(argv[2], &b);
        if (a.st_ino == b.st_ino) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        if (read == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
    } else if (argc == 1) {
        read = stdin;
    } else {
        fprintf(stderr,"usage: reverse <input> <output>\n");
        exit(1);
    }
    reverse();
    return 0;
}
