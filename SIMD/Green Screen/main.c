#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "bmp.c"

#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define BITS_PER_PIXEL_OFFSET 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define NO_COMPRESSION 0
#define MAX_NUMBER_OF_COLORS 0
#define ALL_COLORS_REQUIRED 0

typedef unsigned int int32;
typedef short int16;
typedef unsigned char byte;

// Function to check if a pixel is "green"
int is_green(byte r, byte g, byte b) {
    return (g > r && g > b);
}

int main() {
    /* Start reading the file and its information */
    byte *pixels_top, *pixels_bg;
    int32 width_top, width_bg;
    int32 height_top, height_bg;
    int32 bytesPerPixel_top, bytesPerPixel_bg;
    
    // Read the top (foreground) and background images
    ReadImage("dino.bmp", &pixels_top, &width_top, &height_top, &bytesPerPixel_top);
    ReadImage("parking.bmp", &pixels_bg, &width_bg, &height_bg, &bytesPerPixel_bg);

    /* Images should have color and be of the same size */
    assert(bytesPerPixel_top == 3);  
    assert(width_top == width_bg);
    assert(height_top == height_bg);
    assert(bytesPerPixel_top == bytesPerPixel_bg);

    int32 width = width_top, height = height_top, bytesPerPixel = bytesPerPixel_top;

    // Row size including padding
    int paddedRowSize = (int)(4 * ceil((float)(width * bytesPerPixel) / 4.0f));
    int unpaddedRowSize = width * bytesPerPixel;

    // Iterate over each pixel row by row
    for (int i = 0; i < height; i++) {
        int row_top_offset = i * paddedRowSize;
        int row_bg_offset = i * paddedRowSize;

        // Process each pixel in the row
        for (int j = 0; j < width; j++) {
            int pixel_top_offset = row_top_offset + j * bytesPerPixel;
            int pixel_bg_offset = row_bg_offset + j * bytesPerPixel;

            // Extract RGB values from the top (foreground) image
            byte b_top = pixels_top[pixel_top_offset];
            byte g_top = pixels_top[pixel_top_offset + 1];
            byte r_top = pixels_top[pixel_top_offset + 2];

            if (is_green(r_top, g_top, b_top)) {
                // Replace the top image pixel with the background pixel
                pixels_top[pixel_top_offset] = pixels_bg[pixel_bg_offset];           // B
                pixels_top[pixel_top_offset + 1] = pixels_bg[pixel_bg_offset + 1];   // G
                pixels_top[pixel_top_offset + 2] = pixels_bg[pixel_bg_offset + 2];   // R
            }
        }
    }

    /* Write the new image */
    WriteImage("replaced.bmp", pixels_top, width, height, bytesPerPixel);

    /* Free everything */
    free(pixels_top);
    free(pixels_bg);
    
    return 0;
}
