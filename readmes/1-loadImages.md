# Loading Textures
#### Opening the BMP file:
```c
FILE* file = fopen(filename, "rb");
if (!file) {
    printf("Error: Unable to open the BMP file.\n");
    exit(1);
}
```
This code snippet opens the BMP file specified by the `filename` parameter in binary mode (`"rb"`). It uses the `fopen` function to open the file and assigns the file pointer to the `file` variable. If the file opening operation fails (i.e., the file pointer is `NULL`), it prints an error message and exits the program.


#### Reading the BMP header:
```c
unsigned char header[54];
if (fread(header, 1, 54, file) != 54) {
    printf("Error: Invalid BMP file.\n");
    fclose(file);
    exit(1);
}
```
This code snippet reads the first 54 bytes of the opened BMP file into the `header` array using the `fread` function. It checks if the number of bytes read is equal to 54. If the read operation doesn't return 54 bytes, it indicates an invalid BMP file. In that case, it prints an error message, closes the file using `fclose`, and exits the program.


#### Checking if the file is a valid BMP file:
```c
if (header[0] != 'B' || header[1] != 'M') {
    printf("Error: Invalid BMP file.\n");
    fclose(file);
    exit(1);
}
```
This code snippet checks if the file is a valid BMP file by verifying the magic number in the BMP header. It compares the first two bytes of the `header` array (`header[0]` and `header[1]`) with the ASCII characters `'B'` and `'M'`. If they don't match, it indicates an invalid BMP file. In that case, it prints an error message, closes the file using `fclose`, and exits the program.


#### Extracting the image data:
```c
unsigned int dataPos = *(int*) &(header[0x0A]);
unsigned int imageSize = *(int*) &(header[0x22]);
unsigned int width = *(int*) &(header[0x12]);
unsigned int height = *(int*) &(header[0x16]);
```
This code snippet extracts relevant information from the BMP header. It uses pointer casting to retrieve specific values from the header array. For example, `*(int*) &(header[0x0A])` casts the memory address of the `0x0A` offset in the header array to an `int` pointer and dereferences it to retrieve the value at that location. The extracted information includes the data position, image size, width, height, and pixel format.


#### Memory allocation for the image data:
```c
unsigned char* imageData = (unsigned char*)malloc(imageSize);
if (!imageData) {
    printf("Error: Unable to allocate memory for the image data.\n");
    fclose(file);
    exit(1);
}
```
This code snippet allocates memory for the image data using the `malloc` function. It allocates `imageSize` bytes of memory and assigns the memory address to the `imageData` pointer. If the memory allocation fails (i.e., `imageData` is `NULL`), it prints an error message, closes the file using `fclose`, and exits the program.


#### Reading the image data from the file:
```c
if (fread(imageData, 1, imageSize, file) != imageSize) {
    printf("Error: Unable to read the image data.\n");
    free(imageData);
    fclose(file);
    exit(1);
}
```
This code snippet reads the image data from the file into the allocated `imageData` array using the `fread` function. It reads `imageSize` bytes of data and verifies if the number of bytes read is equal to `imageSize`. If the read operation doesn't return the expected number of bytes, it indicates an error. In that case, it prints an error message, frees the allocated memory using `free`, closes the file using `fclose`, and exits the program.


#### Resizing the image:
```c
unsigned char* resizedData = (unsigned char*)malloc(targetWidth * targetHeight * 4);
if (!resizedData) {
    printf("Error: Unable to allocate memory for the resized image data.\n");
    free(imageData);
    exit(1);
}

gluScaleImage(GL_RGBA, width, height, GL_UNSIGNED_BYTE, imageData, targetWidth, targetHeight, GL_UNSIGNED_BYTE, resizedData);
```
This code snippet resizes the image to the desired dimensions (`targetWidth` and `targetHeight`).

In this example, the `gluScaleImage` function is called to resize an image from the `imageData` array to the dimensions specified by `targetWidth` and `targetHeight`.

- `GL_RGBA`: Specifies the format of the input image data. In this case, it indicates that the image has red, green, blue, and alpha color channels.
- `width`: Specifies the width of the input image in pixels. It is the original width of the image.
- `height`: Specifies the height of the input image in pixels. It is the original height of the image.
- `GL_UNSIGNED_BYTE`: Specifies the data type of the input image. In this case, it indicates that each color channel is represented by an unsigned byte value (0-255).
- `imageData`: Points to the memory location where the input image data is stored. It is the original image data that needs to be resized.
- `targetWidth`: Specifies the desired width of the output image in pixels. It is the new width to which the image will be resized.
- `targetHeight`: Specifies the desired height of the output image in pixels. It is the new height to which the image will be resized.
- `GL_UNSIGNED_BYTE`: Specifies the data type of the output image. In this case, it indicates that each color channel in the resized image will be represented by an unsigned byte value.
- `resizedData`: Points to the memory location where the resized image data will be stored. It is the array that will hold the resized image data.

The `gluScaleImage` function takes the input image data (`imageData`) with its original dimensions (`width` and `height`) and scales it to the desired dimensions (`targetWidth` and `targetHeight`). It performs the necessary interpolation and resampling to adjust the image size while maintaining the visual content.

After the `gluScaleImage` function call, the resized image data is stored in the `resizedData` array, which should be pre-allocated with sufficient memory to hold the resized image.
