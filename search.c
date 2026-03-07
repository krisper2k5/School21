#include <math.h>
#include <stdio.h>

int input(int *arr, int *n);
double mean(int *arr, int n);
double sigma(int *arr, int n, double m);
int find_number(int *arr, int n, double m, double s);

int main() {
  int arr[30];
  int n;

  if (!input(arr, &n)) {
    printf("n/a");
    return 0;
  }

  double m = mean(arr, n);
  double s = sigma(arr, n, m);

  int result = find_number(arr, n, m, s);
  printf("%d", result);

  return 0;
}

int input(int *arr, int *n) {
  if (scanf("%d", n) != 1 || *n <= 0 || *n > 30)
    return 0;

  for (int i = 0; i < *n; i++) {
    if (scanf("%d", &arr[i]) != 1)
      return 0;
  }
  return 1;
}

double mean(int *arr, int n) {
  double sum = 0;
  for (int i = 0; i < n; i++)
    sum += arr[i];
  return sum / n;
}

double sigma(int *arr, int n, double m) {
  double sum = 0;
  for (int i = 0; i < n; i++) {
    double diff = arr[i] - m;
    sum += diff * diff;
  }
  return sqrt(sum / n);
}

int find_number(int *arr, int n, double m, double s) {
  for (int i = 0; i < n; i++) {
    int x = arr[i];

    if (x % 2 == 0 && x != 0 && x >= m && fabs(x - m) <= 3 * s)
      return x;
  }
  return 0;
}
