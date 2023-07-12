# Blending and Biniding
#### Enabling blending:
```c
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glBlendEquation(GL_FUNC_ADD);
```
Enabling blending in OpenGL allows you to combine the colors of the current pixel with the colors of the pixel already in the framebuffer. Blending is commonly used to achieve transparency effects or to blend overlapping objects smoothly.

- `glEnable(GL_BLEND)` enables blending functionality in OpenGL. Once enabled, the color blending operations will take place during rendering.

- `glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)` sets the blending factors. This particular function call specifies that the source color (the new pixel color) should be multiplied by its alpha value (transparency) and the destination color (the existing pixel color) should be multiplied by the inverse of the source alpha value. The resulting values are then added together. This is a common blending equation for achieving transparency.

- `glBlendEquation(GL_FUNC_ADD)` specifies the blending equation to be used. In this case, it adds the source and destination colors together. This equation is commonly used for blending operations.

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
Generating and binding textures in OpenGL involves creating texture objects and configuring their properties.

- `glGenTextures(1, &backgroundTexture)` generates a texture object and assigns it a unique ID, which is stored in the `backgroundTexture` variable. The number `1` specifies that we want to generate a single texture.

- `glBindTexture(GL_TEXTURE_2D, backgroundTexture)` binds the texture object with the specified ID (`backgroundTexture`) as the currently active texture. This allows subsequent texture-related function calls to operate on this texture.

- `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)` and `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)` set the texture wrapping mode. `GL_REPEAT` causes the texture to repeat if texture coordinates exceed the range [0, 1]. This allows seamless tiling of the texture [Not imp for this project] .

- `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)` and `glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)` set the texture filtering mode. `GL_LINEAR` specifies bilinear interpolation for minification and magnification. This provides smooth texture rendering.

- `glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_X, WINDOW_Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, backgroundData)` specifies the image data for the texture. It sets the texture dimensions (`WINDOW_X` and `WINDOW_Y`), pixel format (`GL_RGBA`), and data type (`GL_UNSIGNED_BYTE`). The actual image data is provided from the `backgroundData` array.

The process of generating and binding textures allows you to create texture objects, set their properties, and associate image data with them. These textures can then be used during rendering to apply textures to objects or backgrounds in the scene.
