#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int parse_int(char *str, unsigned long long int *res)
{
    if ('-' == str[0]) {
        return -1;
    }

    if ((*res = strtoull(str, NULL, 0)) == ULLONG_MAX) {
        if (ERANGE == errno) {
            return -2;
        } else {
            return 0;
        }

    } else {
        return 0;
    }
}

int main(int argc, char *argv[])
{
    unsigned long long num = 0, i;
    int c;

    if (2 != argc) {
        fprintf(stderr, "usage: %s NUM_BYTES < in > out\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    switch (parse_int(argv[1], &num)) {
    case 0:
        break;
    case -1:
        fprintf(stderr, "%s: invalid negative number of bytes %s\n",
                argv[0], argv[1]);
        exit(EXIT_FAILURE);
        break;
    case -2:
        fprintf(stderr, "%s: %s out of range\n", argv[0], argv[1]);
        exit(EXIT_FAILURE);
        break;
    }

    for (i = 0; i < num; i++) {
        if (getchar() == EOF) {
            exit(EXIT_SUCCESS);
        }
    }

    while ((c = getchar()) != EOF) {
        putchar(c);
    }

    return 0;
}
