#include <stdio.h>

#include "simplex_noise.h"

int main() {
    // for (float x = 0; x < 10; x += 0.05) {
    //     printf("%f\n", simplex_noise_1d(x));
    // }
    for (float x = 0; x < 20; x += 0.05) {
        printf("%f\n", simplex_noise_fractal_1d(12, x));
    }
    return 0;
}
