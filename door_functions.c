#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#define POINTS 42

double agnesi(double x) { return 1.0 / (1.0 + x * x); }

double bernoulli(double x) {
    double inside = sqrt(1.0 + x * x) - x * x;
    if (inside < 0.0) return -1.0;
    return sqrt(inside);
}

double hyperbola(double x) {
    if (x == 0.0) return -1.0;
    return 1.0 / (x * x);
}

int main() {
    double step = (2.0 * PI) / (POINTS - 1);

    for (int i = 0; i < POINTS; i++) {
        double x = -PI + i * step;

        double a = agnesi(x);
        double b = bernoulli(x);
        double h = hyperbola(x);

        printf("%.7lf | %.7lf | ", x, a);

        if (b < 0)
            printf("- | ");
        else
            printf("%.7lf | ", b);

        if (h < 0)
            printf("-\n");
        else
            printf("%.7lf\n", h);
    }

    return 0;
}

// Перенаправление вывода в файл:   ./door_functions > data/door_data.txt
