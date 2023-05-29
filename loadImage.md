
## Loading Enemy Texture from "enemy.bmp" File

To load the enemy texture from the "enemy.bmp" file inside the "textures" folder, follow these steps:

1. Make sure you have the "enemy.bmp" file in the "textures" folder. If not, place the file in the correct location.

2. Define the width and height of the enemy texture in the "constants.h" file. Add the following lines:

   ```
   #define ENEMY_WIDTH  // Replace with the desired width value
   #define ENEMY_HEIGHT  // Replace with the desired height value
   ```

3. Declare a variable of type `GLuint` to store the texture ID. Add the following line:

   ```
   GLuint enemyTexture;
   ```

4. Update the `set_up_images` function to load the enemy texture:

   ```
   void set_up_images() {
       // Existing code...

       unsigned char* enemyData = loadImage("textures/enemy.bmp", ENEMY_WIDTH, ENEMY_HEIGHT);

       glGenTextures(1, &enemyTexture);
       glBindTexture(GL_TEXTURE_2D, enemyTexture);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ENEMY_WIDTH, ENEMY_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, enemyData);

       free(enemyData);

       // Existing code...
   }
   ```

5. create the function `draw_enemy_ship` to reflect the specific usage:

   ```
   void draw_enemy_ship(obj* enemyShip) {
       // Existing code...

       glBindTexture(GL_TEXTURE_2D, enemyTexture);

       glBegin(GL_QUADS);
           glTexCoord2f(0, 0);
           glVertex2f(enemyShip->x - ENEMY_WIDTH / 2 - 5, enemyShip->y - ENEMY_HEIGHT / 2);
           glTexCoord2f(1, 0);
           glVertex2f(enemyShip->x + ENEMY_WIDTH / 2 - 5, enemyShip->y - ENEMY_HEIGHT / 2);
           glTexCoord2f(1, 1);
           glVertex2f(enemyShip->x + ENEMY_WIDTH / 2 - 5, enemyShip->y + ENEMY_HEIGHT / 2);
           glTexCoord2f(0, 1);
           glVertex2f(enemyShip->x - ENEMY_WIDTH / 2 - 5, enemyShip->y + ENEMY_HEIGHT / 2);
       glEnd();

       // Existing code...
   }
  ```
