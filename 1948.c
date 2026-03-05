#include <stdio.h>

int analogOfDivision(int a, int b) {
    while (a >= b) {
        a = a - b;
    }
    return a;
}

int isPrimary(int n) {
    int result;
    int i;

    if (n < 2) {
        result = 0;
    } else if (n == 2) {
        result = 1;
    } else if (analogOfDivision(n, 2) == 0) {
        result = 0;
    } else {
        result = 1;
        i = 3;
        while (i * i <= n) {
            if (analogOfDivision(n, i) == 0) {
                result = 0;
                break;
            }
            i = i + 2;
        }
    }
    return result;
}

int findLargestPrimeDivisor(int n) {
    int abs_n;
    int candidate;
    int result;

    if (n == 0) {
        result = -1;
    } else {
        abs_n = (n < 0) ? -n : n;
        if (abs_n == 1) {
            result = -1;
        } else {
            result = -1;
            candidate = abs_n;
            while (candidate >= 2) {
                if (analogOfDivision(abs_n, candidate) == 0) {
                    if (isPrimary(candidate) == 1) {
                        result = candidate;
                        break;
                    }
                }
                candidate = candidate - 1;
            }
        }
    }
    return result;
}

int main() {
    int a;
    int res;

    if (scanf("%d", &a) != 1) {
        printf("n/a\n");
        return 0;
    }

    res = findLargestPrimeDivisor(a);

    if (res == -1) {
        printf("n/a\n");
    } else {
        printf("%d\n", res);
    }

    return 0;
}
