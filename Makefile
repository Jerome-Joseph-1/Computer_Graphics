all: 
	gcc main.c move.c draw.c create.c collision.c -lGL -lGLU -lglut -lm -o output

clean: 
	rm *.o output