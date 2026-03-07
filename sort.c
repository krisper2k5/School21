#include <stdio.h>

#define N 10

int input(int *arr);
void sort(int *arr);
void output(int *arr);

int main() {
  int arr[N];

  if (!input(arr)) {
    printf("n/a");
    return 0;
  }

  sort(arr);
  output(arr);

  return 0;
}

int input(int *arr) {
  for (int i = 0; i < N; i++) {
    if (scanf("%d", arr + i) != 1)
      return 0;
  }
  return 1;
}

void sort(int *arr) {
  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < N - i - 1; j++) {
      if (*(arr + j) > *(arr + j + 1)) {
        int tmp = *(arr + j);
        *(arr + j) = *(arr + j + 1);
        *(arr + j + 1) = tmp;
      }
    }
  }
}

void output(int *arr) {
  for (int i = 0; i < N; i++) {
    printf("%d", *(arr + i));
    if (i < N - 1)
      printf(" ");
  }
}
