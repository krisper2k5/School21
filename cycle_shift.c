#include <stdio.h>

#define MAX 10

int input(int *arr, int *n, int *c);
void shift(int *arr, int n, int c);
void output(int *arr, int n);

int main() {
  int arr[MAX];
  int n, c;

  if (!input(arr, &n, &c)) {
    printf("n/a");
    return 0;
  }

  shift(arr, n, c);
  output(arr, n);

  return 0;
}

int input(int *arr, int *n, int *c) {
  if (scanf("%d", n) != 1 || *n <= 0 || *n > MAX)
    return 0;

  for (int i = 0; i < *n; i++) {
    if (scanf("%d", arr + i) != 1)
      return 0;
  }

  if (scanf("%d", c) != 1)
    return 0;

  return 1;
}

void shift(int *arr, int n, int c) {
  int temp[MAX];

  c = ((c % n) + n) % n;

  for (int i = 0; i < n; i++)
    temp[i] = *(arr + (i + c) % n);

  for (int i = 0; i < n; i++)
    *(arr + i) = temp[i];
}

void output(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d", *(arr + i));
    if (i < n - 1)
      printf(" ");
  }
}
