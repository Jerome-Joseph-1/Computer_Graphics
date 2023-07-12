# Set Up Images
#### Enabling blending:
```c
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glBlendEquation(GL_FUNC_ADD);
```
These lines of code enable blending in OpenGL. Blending is a process that combines the colors of the current pixel with the colors of the pixel already in the framebuffer. The first line enables blending functionality, and the following two lines set up the blending factors and equations.

#### Loading image data:
```c
unsigned char* enemyData = loadImage("textures/enemy_ship_r.bmp", ENEMY_SHIP_WIDTH, ENEMY_SHIP_HEIGHT);
unsigned char* backgroundData = loadImage("textures/background.bmp", WINDOW_X, WINDOW_Y);
unsigned char* shipData = loadImage("textures/ship.bmp", SPACE_SHIP_WIDTH, SPACE_SHIP_HEIGHT);
unsigned char* bulletData = loadImage("textures/bullets/bullet_16_up.bmp", BULLET_WIDTH, BULLET_HEIGHT);
unsigned char* cometData = loadImage("textures/bullets/bullet_19_down.bmp", COMET_WIDTH, COMET_HEIGHT);
unsigned char* enemyBulletData = loadImage("textures/bullets/bullet_14_down.bmp", BULLET_WIDTH, BULLET_HEIGHT);
```
These lines of code load image data from BMP files using the `loadImage` function. Each image is loaded into a separate unsigned char pointer, such as `enemyData`, `backgroundData`, etc. The function takes the filename of the BMP file and the desired width and height of the image.

#### Fixing color channels:
```c
fixColorChannels(enemyData, ENEMY_SHIP_WIDTH * ENEMY_SHIP_HEIGHT);
fixColorChannels(backgroundData, WINDOW_X * WINDOW_Y);
fixColorChannels(shipData, SPACE_SHIP_WIDTH * SPACE_SHIP_HEIGHT);
fixColorChannels(bulletData, BULLET_WIDTH * BULLET_HEIGHT);
fixColorChannels(cometData, COMET_WIDTH * COMET_HEIGHT);
fixColorChannels(enemyBulletData, BULLET_WIDTH * BULLET_HEIGHT);
```
These lines of code fix the color channels of the loaded image data using the `fixColorChannels` function. It ensures that the color channels are in the correct order for OpenGL texture usage. The function rearranges the red, green, and blue channels.

#### Generating and binding textures:
```c
glGenTextures(1, &backgroundTexture);
glBindTexture(GL_TEXTURE_2D, backgroundTexture);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_X, WINDOW_Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, backgroundData);
```
These lines of code generate and bind textures in OpenGL. It uses the generated texture IDs (e.g., `backgroundTexture`, `shipTexture`, etc.) to define the properties and image data for each texture. The `glTexParameteri` functions set the texture wrapping and filtering parameters, and the `glTexImage2D` function specifies the image data for the texture.

#### Freeing allocated memory:
```c
free(enemyBulletData);
free(bulletData);
free(enemyData);
free(shipData);
free(backgroundData);
free(cometData);
```
These lines of code free the dynamically allocated memory that was used to hold the loaded image data. It ensures that the memory is released properly to avoid memory leaks.

The `set_up_images` function performs the necessary setup steps for loading image data, fixing color channels, generating and binding textures, and freeing memory. It prepares the textures for rendering in the OpenGL application.
