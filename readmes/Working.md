# Game Documentation - Space Invaders

## Description
The game "Space Invaders" is a classic arcade-style game that involves a player's ship, enemy ships, and comets. The player can control their ship using the W, A, S, and D keys and shoot bullets using the left mouse button. The enemy ships move in an elliptic orbit and fire bullets towards the player's ship, while comets move from the top to the bottom of the screen. The objective is to dodge enemy bullets and destroy all enemy ships while avoiding damage to the player's ship.

## Implementation
The game implements several key components:
- The game objects, such as the player ship, enemy ships, and comets, are represented using a struct object called `obj`. It stores information like health points (hp) and coordinates (x, y) for each object.
- Textures are loaded into a box that is drawn around the center coordinates of each object.

## Game States
The game consists of different states represented by a `GAME_STATE` enum:
- `MAIN_MENU`: The main menu screen.
- `GAME_START`: The gameplay screen.
- `GAME_OVER`: The game over screen.
The `GAME_STATE` variable is updated to switch between these states and determine which screen is displayed.

## Moving Player Ship
- The player can control the ship using the W, A, S, and D keys. When a key is pressed, the corresponding value in the `keyStates` array is set to 1 (ASCII value of the key).
```
For example, `keyStates['w'] = 1;` is equivalent to `keyStates[119] = 1;`
```
- The ship's movement is handled by a function called `refresh`, which is called every 16ms. Within this function, the `move_ship` function checks if the W, A, S, or D key is pressed (by checking the value in `keyStates`). If pressed, the ship's coordinates (x or y) are incremented or decremented by a fixed value (`SPACE_SHIP_SPEED`).

## Moving Enemy Ship
- The movement of enemy ships is controlled by the `move_enemy_ships` function, which is called within the `refresh` function. This function updates the x and y coordinates of each enemy ship based on an elliptical path determined by the value of `theta`.
- The parametric equations of an ellipse are used to calculate the coordinates:
  - x = a * cos(theta) (a is the major axis)
  - y = b * sin(theta) (b is the minor axis)
- The angle `theta` is measured in radians.

## Creating and Moving Bullets (Player's Bullets)
- Bullet creation:
  - The variable `bulletBufferFilled` is a boolean that checks if the bullet buffer (an array holding all bullets) is full (true) or not (false).
  - When the left mouse button is pressed and `bulletBufferFilled` is false, a bullet is created at the position of the player's ship and added to the `bullets` array.
- Bullet movement:
  - The `move_bullet` function is responsible for moving the bullets. It iterates through each bullet in the array and increases its y-coordinate by a fixed value (`SPACE_SHIP_BULLET_SPEED`).
  - If the bullet's y-coordinate goes beyond the screen's y-axis, the bullet is set to NULL.

## Creating and Moving Comets
- Comet creation:
  - The `create_comet` function dynamically allocates memory for a comet object, sets its x-coordinate to a random value within the window's range, sets its y-coordinate to a position just above the top of the window, and assigns a random speed between 1 and 4. The function then returns a pointer to the newly created comet object. This comet is stored in an array called `comets`.
- Comet movement:
  - The `move_comets` function is responsible for moving the comets. It updates the y-coordinate of each comet in the array by subtracting its assigned speed (moving downward). If a comet's y-coordinate becomes less than 0, indicating it has moved beyond the bottom of the window, its x-coordinate is set to a random value within the window's range, and its y-coordinate is reset to the top of the window.

## Collision Detection
- There are two collision detection functions:
  1. `check_ship_bullet_collision`: This function checks for collisions between bullets fired from the player's ship and enemy ships as well as comets. It iterates through the bullet and enemy ship arrays, checking if a bullet hits an enemy ship by comparing the bullet's position (x, y) with the box drawn around the enemy ship. If a hit occurs, the enemy ship's health is decreased, and the bullet is marked as not present. Similarly, it checks for collisions between bullets and comets, freeing the memory of the collided comet.
  2. `check_enemy_bullet_collision`: This function checks collisions between bullets fired by enemy ships and the player's ship, as well as collisions between comets and the player's ship. It iterates through the enemy bullet array, checking if a bullet hits the player's ship. If a hit occurs, the ship's health is decreased. It also iterates through the comet array, checking for collisions with the ship using the same collision detection method as before. If a collision is detected, the memory of the collided comet is freed, and the ship's health is decreased.
