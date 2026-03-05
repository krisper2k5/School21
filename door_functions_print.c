#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#define POINTS 42
#define Y_SCALE 21

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

void printGraph(const char *name, double (*func)(double)) {
    printf("\n%s\n\n", name);

    double step = (2.0 * PI) / (POINTS - 1);

    double max_val = 0.0;
    for (int i = 0; i < POINTS; i++) {
        double x = -PI + i * step;
        double val = func(x);
        if (val > max_val) max_val = val;
    }
    if (max_val == 0.0) max_val = 1.0;

    for (int y = Y_SCALE; y >= 0; y--) {
        for (int i = 0; i < POINTS; i++) {
            double x = -PI + i * step;
            double val = func(x);
            if (val < 0) {
                printf(" ");
            } else {
                int pos = (int)(val / max_val * Y_SCALE + 0.5);
                if (pos == y)
                    printf("*");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    printGraph("Verziera Agnesi", agnesi);
    printGraph("Bernoulli Lemniscate", bernoulli);
    printGraph("Quadratic Hyperbola", hyperbola);
    return 0;
}
