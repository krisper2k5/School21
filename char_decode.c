#include <stdio.h>
#include <string.h>

int hexToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

void encode() {
    int c1, c2;
    int first = 1;

    while (1) {
        c1 = getchar();
        if (c1 == '\n' || c1 == EOF) break;

        if (c1 == ' ') {
            printf("n/a");
            return;
        }

        c2 = getchar();
        if (c2 == '\n' || c2 == EOF) break;

        if (c2 != ' ') {
            printf("n/a");
            return;
        }

        if (!first) printf(" ");

        printf("%02X", (unsigned char)c1);
        first = 0;
    }

    printf("\n");
}

void decode() {
    int c1, c2, c3;
    int first = 1;

    while (1) {
        c1 = getchar();
        if (c1 == '\n' || c1 == EOF) break;

        if (c1 == ' ') {
            printf("n/a");
            return;
        }

        c2 = getchar();
        if (c2 == '\n' || c2 == EOF) {
            printf("n/a");
            return;
        }

        int high = hexToInt(c1);
        int low = hexToInt(c2);

        if (high == -1 || low == -1) {
            printf("n/a");
            return;
        }

        c3 = getchar();
        if (c3 != ' ' && c3 != '\n' && c3 != EOF) {
            printf("n/a");
            return;
        }

        if (!first) printf(" ");

        printf("%c", (char)((high << 4) | low));
        first = 0;

        if (c3 == '\n' || c3 == EOF) break;
    }

    printf("\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("n/a");
        return 0;
    }

    if (strcmp(*(argv + 1), "0") == 0)
        encode();
    else if (strcmp(*(argv + 1), "1") == 0)
        decode();
    else
        printf("n/a");

    return 0;
}
