# Green Screen Replacement

This program replaces the green pixels in a foreground BMP image (dino.bmp) with the corresponding pixels from a background BMP image (parking.bmp). The result is saved as a new image file called replaced.bmp.
## How It Works

- The program reads two BMP images: dino.bmp (foreground) and parking.bmp (background).
- It identifies "green" pixels in the dino.bmp image by checking if the green channel (G) is greater than both the red (R) and blue (B) channels.
- For each green pixel in dino.bmp, it replaces that pixel with the corresponding pixel from parking.bmp.
- The result is saved in the file replaced.bmp.

## Requirements

The images must be 24-bit BMP format (3 bytes per pixel: RGB).
The foreground (dino.bmp) and background (parking.bmp) images must have the same dimensions.

## How to Compile

To compile the program, use the following command:

```bash
gcc -o main main.c -lm
```
This will produce an executable named main.
## How to Run

To run the program, ensure you have dino.bmp and parking.bmp in the same directory as the executable. Then, run the following command:

```bash
./main
```
After running the program, a new file called replaced.bmp will be created in the same directory, with the green pixels replaced by the corresponding pixels from parking.bmp.
