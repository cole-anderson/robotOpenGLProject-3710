INCLUDE = -I/usr/include/
LIBDIR = -L/usr/lib/

COMPILERFLAGS = -Wall
CC = g++
CFLAGS = $(COMPILERFLAGS) $(INCLUDE) $(INC)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

all: robot
# 	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $< $(LIBRARIES)

robot: main.o world.o robot.o
	g++ -c robot.cpp
	g++ -c world.cpp
	g++ -c main.cpp
	$(CC) $(CFLAGS) main.o world.o -o robot $(LIBDIR) $(LIBRARIES)

clean:
	rm -f *.o *~ robot
