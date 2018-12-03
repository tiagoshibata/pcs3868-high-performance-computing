#ifndef __SIMPLEX_NOISE_H__
#define __SIMPLEX_NOISE_H__

#include <stddef.h>

float simplex_noise_1d(float x);
float simplex_noise_2d(float x, float y);
float simplex_noise_fractal_1d(size_t octaves, float x);
float simplex_noise_fractal_2d(size_t octaves, float x, float y);

#endif
