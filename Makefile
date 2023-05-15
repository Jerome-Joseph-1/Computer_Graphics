all: 
	gcc main.c move.c draw.c create.c -lGL -lGLU -lglut -lm -o output

clean: 
	rm *.o output