#include <stdio.h>

long long fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    int n;

    if (scanf("%d", &n) != 1 || n < 0) {
        printf("n/a");
        return 0;
    }

    printf("%lld", fib(n));
    return 0;
}
