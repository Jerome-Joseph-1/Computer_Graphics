# Computer_Graphics Project ( Space Invaders )

## Installation

1. Fork the repository to create your own copy.
2. Clone the forked repository to your local machine.
3. Make sure you have GLUT installed on your system. If not, you can install it by following the instructions provided by the GLUT documentation.
4. A Linux environment is preferred for running this project.

## Running the Program

To compile and run the program, follow these steps:

1. In a terminal or command prompt, navigate to the working directory where the project files are located.
2. Type the following command to compile the program:
```
make all
```
This will generate an executable file named "output".

3. To run the program, use the following command:
```
./output
```
## Files Description

The project contains the following files:

### C Files:

- `create.c`: Contains functions to create objects.
- `draw.c`: Contains functions to draw objects.
- `move.c`: Contains functions to move objects.
- `collision.c`: Contains functions to detect object collisions (e.g., bullets and objects).

### Header Files:

- `header/includeHeaders.h`: Contains essential header files needed for compiling and running the program (e.g., GL/glut.h).
- `header/constants.h`: Contains constants (e.g., window size and object speed).
- `header/customTypes.h`: Contains custom data types such as structures for points and structures for objects. The structures for objects hold data like the position of the object, size of the object, health points of the object etc....
- `header/create.h`: Contains function prototypes for functions declared in create.c.
- `header/draw.h`: Contains function prototypes for functions declared in draw.c.
- `header/move.h`: Contains function prototypes for functions declared in move.c.
- `header/collision.h`: Contains function prototypes for functions declared in collision.c.

## Adding Functions

If you need to add a new function inside one of the C files (create.c, draw.c, move.c, collision.c), you must also add the function prototype to the respective header file. This is used to provide necessary information about the functions defined in the corresponding source files.

Make sure to update the header files (`header/create.h`, `header/draw.h`, `header/move.h`, `header/collision.h`) with the function prototypes whenever you add or define a new function in the corresponding C file.
