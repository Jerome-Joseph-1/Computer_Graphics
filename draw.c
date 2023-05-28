#include "header/includeHeaders.h"
#include "header/constants.h"
#include "header/customTypes.h"

// Texture ID for the background image
GLuint backgroundTexture;

// Texture ID for the ship image
GLuint shipTexture;

// Texture ID for the enemy image
GLuint enemyTexture;

// Texture ID for the comet image
GLuint cometTexture;

unsigned char* loadImage(char* filename, unsigned int targetWidth, unsigned int targetHeight) {
    FILE* file;
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    unsigned int width, height;
    unsigned int pixelFormat;

    // Open the BMP file
    file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Unable to open the BMP file.\n");
        exit(1);
    }

    // Read the BMP header
    if (fread(header, 1, 54, file) != 54) {
        printf("Error: Invalid BMP file.\n");
        fclose(file);
        exit(1);
    }

    // Check if the file is a valid BMP file
    if (header[0] != 'B' || header[1] != 'M') {
        printf("Error: Invalid BMP file.\n");
        fclose(file);
        exit(1);
    }

    // Extract the image data
    dataPos = *(int*) &(header[0x0A]);
    imageSize = *(int*) &(header[0x22]);
    width = *(int*) &(header[0x12]);
    height = *(int*) &(header[0x16]);
    pixelFormat = *(unsigned int*) &(header[0x1C]);

    // Adjust the image width and height if necessary
    if (imageSize == 0)
        imageSize = width * height * 4;
    if (dataPos == 0)
        dataPos = 54;

    // Allocate memory for the image data
    unsigned char* imageData = (unsigned char*)malloc(imageSize);
    if (!imageData) {
        printf("Error: Unable to allocate memory for the image data.\n");
        fclose(file);
        exit(1);
    }

    // Read the image data from the file
    if (fread(imageData, 1, imageSize, file) != imageSize) {
        printf("Error: Unable to read the image data.\n");
        free(imageData);
        fclose(file);
        exit(1);
    }

    // Close the file
    fclose(file);

    // Resize the image to the desired dimensions
    unsigned char* resizedData = (unsigned char*)malloc(targetWidth * targetHeight * 4);
    if (!resizedData) {
        printf("Error: Unable to allocate memory for the resized image data.\n");
        free(imageData);
        exit(1);
    }

    gluScaleImage(GL_RGBA, width, height, GL_UNSIGNED_BYTE, imageData, targetWidth, targetHeight, GL_UNSIGNED_BYTE, resizedData);

    // Free the original image data
    free(imageData);

    // Set the resized image data as the new image data
    return resizedData;
}

void setUpImages(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    unsigned char* backgroundData = loadImage("textures/background.bmp", WINDOW_X, WINDOW_Y);
    unsigned char* shipData = loadImage("textures/ship.bmp", SPACE_SHIP_WIDTH, SPACE_SHIP_HEIGHT);

    glGenTextures(1, &backgroundTexture);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_X, WINDOW_Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, backgroundData);

	glGenTextures(1, &shipTexture);
    glBindTexture(GL_TEXTURE_2D, shipTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SPACE_SHIP_WIDTH, SPACE_SHIP_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, shipData);

    free(shipData);
    free(backgroundData);
}

void drawBackground(){
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    // Enable texture mapping
    glEnable(GL_TEXTURE_2D);

    // Draw a rectangle with the background texture
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0, 0, -1);  // Set z-coordinate to -100
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(WINDOW_X, 0, -1);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(WINDOW_X, WINDOW_Y, -1);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0, WINDOW_Y, -1);
    glEnd();


    glDisable(GL_TEXTURE_2D);
}

void draw_ship(obj* ship){

    glEnable(GL_TEXTURE_2D);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, shipTexture);

    // Enable texture mapping
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(ship->x - SPACE_SHIP_WIDTH / 2 - 5, ship->y - SPACE_SHIP_HEIGHT / 2);
        glTexCoord2f(1, 0);
        glVertex2f(ship->x + SPACE_SHIP_WIDTH / 2 - 5, ship->y - SPACE_SHIP_HEIGHT / 2);
        glTexCoord2f(1, 1);
        glVertex2f(ship->x + SPACE_SHIP_WIDTH / 2 - 5, ship->y + SPACE_SHIP_HEIGHT / 2);
        glTexCoord2f(0, 1);
        glVertex2f(ship->x - SPACE_SHIP_WIDTH / 2 - 5, ship->y + SPACE_SHIP_HEIGHT / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);

}