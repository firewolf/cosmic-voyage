CC=g++
CFLAGS=-Wall
LDFLAGS=main.cpp ./math/Orbit.cpp ./lib/drawing.cpp ./lib/Colors.cpp ./math/Math.cpp ./planets/Planet.cpp /usr/lib/libjpeg.a /usr/lib/libpng.a /usr/lib/libpng.so -lGLU -lglut

all: solar

solar:
	$(CC) $(CFLAGS) $(LDFLAGS) -o cosmic-voyage 
	
clean:
	rm -f solar-system