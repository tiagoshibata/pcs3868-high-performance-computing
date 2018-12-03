/**
 * Based on https://github.com/SRombauts/SimplexNoise
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <math.h>
#include <stdint.h>

#include "simplex_noise.h"

static const float simplex_noise_frequency = 1.f;
static const float simplex_noise_amplitude = 1.f;
static const float simplex_noise_lacunarity = 2.f;
static const float simplex_noise_persistence = .5f;

#ifdef SIMPLEX_NOISE_HASH_TABLE
static const uint8_t perm[256] = {
    151, 160, 137, 91, 90, 15,
    131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23,
    190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
    88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
    77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
    102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196,
    135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123,
    5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42,
    223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
    129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
    251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
    49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
    138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
};

static inline uint8_t hash(int32_t i) {
    return perm[(uint8_t)i];
}
#else
static inline uint8_t hash(int32_t i) {
    uint8_t i8 = (uint8_t)i ^ 0xde;
    return (((i >> 4) | i8 << 4) * 199 + i8) & 0xff;
}
#endif

static float grad_dot_residual_1d(int32_t hash, float x) {
    float grad = 1.f + (hash & 7);
    if (hash & 8) grad = -grad;
    return grad * x;
}

static float grad_dot_residual_2d(int32_t hash, float x, float y) {
    const int32_t h = hash & 0x3F;  // Convert low 3 bits of hash code
    const float u = h < 4 ? x : y;  // into 8 simple gradient directions,
    const float v = h < 4 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -2.f * v : 2.f * v); // and compute the dot product with (x,y).
}

float simplex_noise_1d(float x) {
    int32_t i0 = (int32_t)floor(x);
    int32_t i1 = i0 + 1;
    float x0 = x - i0;
    float x1 = x0 - 1.f;

    // Contribution from the first corner
    float t0 = 1.f - x0 * x0;
    t0 *= t0;
    float n0 = t0 * t0 * grad_dot_residual_1d(hash(i0), x0);

    // Contribution from the second corner
    float t1 = 1.f - x1 * x1;
    t1 *= t1;
    float n1 = t1 * t1 * grad_dot_residual_1d(hash(i1), x1);

    // Scale to fit within [-1,1]
    return .395f * (n0 + n1);
}

// Skewing/Unskewing factors for 2D
static const float F2 = 0.366025403f;  // F2 = (sqrt(3) - 1) / 2
static const float G2 = 0.211324865f;  // G2 = (3 - sqrt(3)) / 6

float simplex_noise_2d(float x, float y) {
    float n0, n1, n2;

    // Skew the input space to determine which simplex cell we're in
    const float s = (x + y) * F2;  // Hairy factor for 2D
    const float xs = x + s;
    const float ys = y + s;
    const int32_t i = (int32_t)floor(xs);
    const int32_t j = (int32_t)floor(ys);

    // Unskew the cell origin back to (x,y) space
    const float t = (float)(i + j) * G2;
    const float X0 = i - t;
    const float Y0 = j - t;
    const float x0 = x - X0;  // The x,y distances from the cell origin
    const float y0 = y - Y0;

    int32_t i1, j1;  // Offsets for second (middle) corner of simplex in (i,j) coords
    if (x0 > y0) {   // lower triangle, XY order: (0,0)->(1,0)->(1,1)
        i1 = 1;
        j1 = 0;
    } else {   // upper triangle, YX order: (0,0)->(0,1)->(1,1)
        i1 = 0;
        j1 = 1;
    }

    const float x1 = x0 - i1 + G2;          // Offsets for middle corner in (x,y) unskewed coords
    const float y1 = y0 - j1 + G2;
    const float x2 = x0 - 1.f + 2.f * G2;   // Offsets for last corner in (x,y) unskewed coords
    const float y2 = y0 - 1.f + 2.f * G2;

    // Gradient of the three corners
    const int gi0 = hash(i + hash(j));
    const int gi1 = hash(i + i1 + hash(j + j1));
    const int gi2 = hash(i + 1 + hash(j + 1));

    // Contribution from the first corner
    float t0 = .5f - x0*x0 - y0*y0;
    if (t0 < 0.f) {
        n0 = 0.f;
    } else {
        t0 *= t0;
        n0 = t0 * t0 * grad_dot_residual_2d(gi0, x0, y0);
    }

    // Contribution from the second corner
    float t1 = .5f - x1*x1 - y1*y1;
    if (t1 < 0.f) {
        n1 = 0.f;
    } else {
        t1 *= t1;
        n1 = t1 * t1 * grad_dot_residual_2d(gi1, x1, y1);
    }

    // Contribution from the third corner
    float t2 = .5f - x2*x2 - y2*y2;
    if (t2 < 0.f) {
        n2 = 0.f;
    } else {
        t2 *= t2;
        n2 = t2 * t2 * grad_dot_residual_2d(gi2, x2, y2);
    }

    // Scale to [-1,1]
    return 45.23065f * (n0 + n1 + n2);
}

float simplex_noise_fractal_1d(size_t octaves, float x) {
    float output    = 0.f;
    float denom     = 0.f;
    float frequency = simplex_noise_frequency;
    float amplitude = simplex_noise_amplitude;

    for (size_t i = 0; i < octaves; i++) {
        output += (amplitude * simplex_noise_1d(x * frequency));
        denom += amplitude;

        frequency *= simplex_noise_lacunarity;
        amplitude *= simplex_noise_persistence;
    }

    return (output / denom);
}

float simplex_noise_fractal_2d(size_t octaves, float x, float y) {
    float output = 0.f;
    float denom  = 0.f;
    float frequency = simplex_noise_frequency;
    float amplitude = simplex_noise_amplitude;

    for (size_t i = 0; i < octaves; i++) {
        output += (amplitude * simplex_noise_2d(x * frequency, y * frequency));
        denom += amplitude;

        frequency *= simplex_noise_lacunarity;
        amplitude *= simplex_noise_persistence;
    }

    return (output / denom);
}
