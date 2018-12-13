#ifndef __PNG_WRITER_H__
#define __PNG_WRITER_H__

#include <stdint.h>
void write_png_file(char* filename, uint8_t* data, int width, int height);

#endif
