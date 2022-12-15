#include <stdio.h>

int main(int argc, char const *argv[]) {
    if (argc <= 1) {
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        FILE* p = fopen(argv[i], "r");
        if (!p) {
            fprintf(stdout,"wcat: cannot open file\n");
            return 1;
        }
        while (1)
        {
            /* code */
            int read = fgetc(p);
            if (feof(p)) {
                break;
            }
            fputc(read, stdout);
        }
    }
    return 0;
}
