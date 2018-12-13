#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "png_writer.h"
#include "simplex_noise.h"

int main() {
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    const int width = 1920 / 4, height = 1080 / 4;
    uint8_t *buffer = malloc(width * height * 3);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float fractal_value = simplex_noise_fractal_2d(16, 0.02 * x, 0.02 * y);
            if (fractal_value > 0) {
                buffer[3 * (y * width + x)] = 0;
                buffer[3 * (y * width + x) + 1] = 255 * fractal_value;
                buffer[3 * (y * width + x) + 2] = 0;
            } else {
                buffer[3 * (y * width + x)] = 0;
                buffer[3 * (y * width + x) + 1] = 0;
                buffer[3 * (y * width + x) + 2] = 255 + 200 * fractal_value;
            }
        }
    }
    write_png_file("noise.png", buffer, width, height);

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("time: %.5fms\n", (end_time.tv_sec * 1000 + 1e-6 * end_time.tv_nsec) - (start_time.tv_sec * 1000 + 1e-6 * start_time.tv_nsec));
    return 0;
}
