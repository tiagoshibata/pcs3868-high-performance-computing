#include "png_writer.h"

#include <stdio.h>
#include <stdlib.h>

#include <png.h>

void write_png_file(char* file_name, uint8_t* data, int width, int height) {
    FILE *fp = fopen(file_name, "wb");
    if (!fp) {
        perror("fopen");
        exit(-1);
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fprintf(stderr, "png_create_write_struct failed");
        exit(-1);
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        fprintf(stderr, "png_create_info_struct failed");
        exit(-1);
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "libpng failed");
        exit(-1);
    }
    png_init_io(png_ptr, fp);

    const png_byte color_type = PNG_COLOR_TYPE_RGB;
    const png_byte bit_depth = 8;
    png_bytep *row_pointers = malloc(height * sizeof(data));
    for (int y = 0; y < height; y++) {
        row_pointers[y] = data + 3 * y * width;
    }
    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, NULL);

    free(row_pointers);
    fclose(fp);
}
