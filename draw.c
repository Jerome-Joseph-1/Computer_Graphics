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

// Texture ID for the bullet image
GLuint bulletTexture, enemyBulletTexture;



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

void fixColorChannels(unsigned char* imageData, unsigned int numPixels) {
    for (unsigned int i = 0; i < numPixels; i++) {
        // Get the color channels
        unsigned char red = imageData[i * 4];    // Red channel
        unsigned char green = imageData[i * 4 + 1];  // Green channel
        unsigned char blue = imageData[i * 4 + 2];       // Blue channel

        // Update the color channels in the image data
        imageData[i * 4 + 2] = red;
        imageData[i * 4 + 1] = green;
        imageData[i * 4] = blue;
    }
}



void set_up_images(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    unsigned char* enemyData= loadImage("textures/enemy_ship_r.bmp",ENEMY_SHIP_WIDTH,ENEMY_SHIP_HEIGHT);
    unsigned char* backgroundData = loadImage("textures/background.bmp", WINDOW_X, WINDOW_Y);
    unsigned char* shipData = loadImage("textures/ship.bmp", SPACE_SHIP_WIDTH, SPACE_SHIP_HEIGHT);
    unsigned char* bulletData = loadImage("textures/bullets/bullet_16_up.bmp", BULLET_WIDTH, BULLET_HEIGHT);
    unsigned char* cometData = loadImage("textures/bullets/bullet_19_down.bmp",COMET_WIDTH,COMET_HEIGHT);
    unsigned char* enemyBulletData = loadImage("textures/bullets/bullet_14_down.bmp", BULLET_WIDTH, BULLET_HEIGHT);

    fixColorChannels(enemyData, ENEMY_SHIP_WIDTH * ENEMY_SHIP_HEIGHT);
    fixColorChannels(backgroundData, WINDOW_X * WINDOW_Y);
    fixColorChannels(shipData, SPACE_SHIP_WIDTH * SPACE_SHIP_HEIGHT);
    fixColorChannels(bulletData, BULLET_WIDTH * BULLET_HEIGHT);
    fixColorChannels(cometData, COMET_WIDTH * COMET_HEIGHT);
    fixColorChannels(enemyBulletData, BULLET_WIDTH * BULLET_HEIGHT);

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

    glGenTextures(1, &enemyTexture);
    glBindTexture(GL_TEXTURE_2D, enemyTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ENEMY_SHIP_WIDTH, ENEMY_SHIP_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, enemyData);

    glGenTextures(1, &bulletTexture);
    glBindTexture(GL_TEXTURE_2D, bulletTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BULLET_WIDTH, BULLET_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, bulletData);

    glGenTextures(1,&cometTexture);
    glBindTexture(GL_TEXTURE_2D, cometTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, COMET_WIDTH, COMET_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, cometData);

    glGenTextures(1,&enemyBulletTexture);
    glBindTexture(GL_TEXTURE_2D, enemyBulletTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BULLET_WIDTH, BULLET_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, enemyBulletData);

    free(enemyBulletData);
    free(bulletData);
    free(enemyData);
    free(shipData);
    free(backgroundData);
    free(cometData);
}

void draw_background(){
    glColor3f(1,1,1);

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

    // Enable texture mapping
    glEnable(GL_TEXTURE_2D);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, shipTexture);


    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(ship->x - SPACE_SHIP_WIDTH / 2 - 2, ship->y - SPACE_SHIP_HEIGHT / 2);
        glTexCoord2f(1, 0);
        glVertex2f(ship->x + SPACE_SHIP_WIDTH / 2 - 2, ship->y - SPACE_SHIP_HEIGHT / 2);
        glTexCoord2f(1, 1);
        glVertex2f(ship->x + SPACE_SHIP_WIDTH / 2 - 2, ship->y + SPACE_SHIP_HEIGHT / 2);
        glTexCoord2f(0, 1);
        glVertex2f(ship->x - SPACE_SHIP_WIDTH / 2 - 2, ship->y + SPACE_SHIP_HEIGHT / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);

}

void draw_enemy_ship(obj* enemy_ship) {
    // Enable texture mapping
    glEnable(GL_TEXTURE_2D);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, enemyTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(enemy_ship->x - ENEMY_SHIP_WIDTH / 2 , enemy_ship->y - ENEMY_SHIP_HEIGHT / 2);
        glTexCoord2f(1, 0);
        glVertex2f(enemy_ship->x + ENEMY_SHIP_WIDTH / 2 , enemy_ship->y - ENEMY_SHIP_HEIGHT / 2);
        glTexCoord2f(1, 1);
        glVertex2f(enemy_ship->x + ENEMY_SHIP_WIDTH / 2 , enemy_ship->y + ENEMY_SHIP_HEIGHT / 2);
        glTexCoord2f(0, 1);
        glVertex2f(enemy_ship->x - ENEMY_SHIP_WIDTH / 2 , enemy_ship->y + ENEMY_SHIP_HEIGHT / 2);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void draw_bullets(bullet* bullets[MAX_BULLETS]){

    glEnable(GL_TEXTURE_2D);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, bulletTexture);
    
    
	for(int i = 0; i < MAX_BULLETS; i++) {
        if(bullets[i]) {

            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex2f(bullets[i]->x - BULLET_WIDTH / 2 , bullets[i]->y - BULLET_HEIGHT / 2);
                glTexCoord2f(1, 0);
                glVertex2f(bullets[i]->x + BULLET_WIDTH / 2 , bullets[i]->y - BULLET_HEIGHT / 2);
                glTexCoord2f(1, 1);
                glVertex2f(bullets[i]->x + BULLET_WIDTH / 2 , bullets[i]->y + BULLET_HEIGHT / 2);
                glTexCoord2f(0, 1);
                glVertex2f(bullets[i]->x - BULLET_WIDTH / 2 , bullets[i]->y + BULLET_HEIGHT / 2);
            glEnd();
        }
    }

    glDisable(GL_TEXTURE_2D);
}

void draw_enemy_bullets(bullet* bullets[MAX_ENEMY_BULLETS]){
    glEnable(GL_TEXTURE_2D);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, enemyBulletTexture);
    
    
	for(int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        if(bullets[i]) {

            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex2f(bullets[i]->x - BULLET_WIDTH / 2 , bullets[i]->y - BULLET_HEIGHT / 2);
                glTexCoord2f(1, 0);
                glVertex2f(bullets[i]->x + BULLET_WIDTH / 2 , bullets[i]->y - BULLET_HEIGHT / 2);
                glTexCoord2f(1, 1);
                glVertex2f(bullets[i]->x + BULLET_WIDTH / 2 , bullets[i]->y + BULLET_HEIGHT / 2);
                glTexCoord2f(0, 1);
                glVertex2f(bullets[i]->x - BULLET_WIDTH / 2 , bullets[i]->y + BULLET_HEIGHT / 2);
            glEnd();
        }
    }

    glDisable(GL_TEXTURE_2D);
}

void draw_menu(){
	glColor3f(1, 1, 1);

        // Define the titles and their positions
        const char* titles[] = {"SPACE INVADERS", "START", "EXIT"};
        const int numTitles = sizeof(titles) / sizeof(titles[0]);
        const float yOffset[] = {WINDOW_X / 4 + WINDOW_Y / 2, WINDOW_Y / 2 - WINDOW_Y / 30, WINDOW_Y / 2 - WINDOW_Y / 10};

        void* font = GLUT_BITMAP_HELVETICA_18;

        for (int i = 0; i < numTitles; i++) {
            const char* title = titles[i];
            int titleWidth = 0;
            if(i != 0) 
                glColor3f(0, 1, 0);
            for (int j = 0; title[j] != '\0'; j++) {
                titleWidth += glutBitmapWidth(font, title[j]);
            }

            glRasterPos2i(WINDOW_X / 2 - titleWidth / 2, yOffset[i]);

            for (int j = 0; title[j] != '\0'; j++) {
                glutBitmapCharacter(font, title[j]);
            }
        }

        // Reset the text color
        glColor3f(1, 1, 1);
}

void draw_game_over() {
    const char* titles[] = {"GAME OVER", "PRESS 'P' TO RETURN TO MAIN MENU"};
    const int numTitles = sizeof(titles) / sizeof(titles[0]);
        const float yOffset[] = {WINDOW_Y / 2, WINDOW_Y / 2 - WINDOW_Y / 30, WINDOW_Y / 2 - WINDOW_Y / 10};

        void* font = GLUT_BITMAP_HELVETICA_18;

        for (int i = 0; i < numTitles; i++) {
            const char* title = titles[i];
            int titleWidth = 0;
            if(i != 0) 
                glColor3f(0, 1, 0);
            for (int j = 0; title[j] != '\0'; j++) {
                titleWidth += glutBitmapWidth(font, title[j]);
            }

            glRasterPos2i(WINDOW_X / 2 - titleWidth / 2, yOffset[i]);

            for (int j = 0; title[j] != '\0'; j++) {
                glutBitmapCharacter(font, title[j]);
            }
        }

        // Reset the text color
        glColor3f(1, 1, 1);
}



//Draw comet
void draw_comet(comet* c) {
    // Enable texture mapping
    glEnable(GL_TEXTURE_2D);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, cometTexture);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(c->x - COMET_WIDTH / 2, c->y - COMET_HEIGHT / 2);
        glTexCoord2f(1, 0);
        glVertex2f(c->x + COMET_WIDTH / 2, c->y - COMET_HEIGHT / 2);
        glTexCoord2f(1, 1);
        glVertex2f(c->x + COMET_WIDTH / 2, c->y + COMET_HEIGHT / 2);
        glTexCoord2f(0, 1);
        glVertex2f(c->x - COMET_WIDTH / 2, c->y + COMET_HEIGHT / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


