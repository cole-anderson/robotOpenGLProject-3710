#OPEN GL MAKEFILE
INCLUDE = -I/usr/include/
LIBDIR = -L/usr/lib/

COMPILERFLAGS = -Wall
CC = g++ -std=c++11
CFLAGS = $(COMPILERFLAGS) $(INCLUDE) $(INC)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

all: robot

robot: main.o objects.o
	$(CC) $(CFLAGS) main.o -o robot $(LIBDIR) $(LIBRARIES)

clean:
	rm -f *.o *~ robot
