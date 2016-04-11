# Project: GLprimer
# Makefile created by Stefan Gustavson 2015-04-10

# Makefile for Windows mingw32, Linux and MacOSX (gcc environments)

CC   = gpp
OBJ  = main.o
INC  = -I.
OPT = -Wall -O3 -ffast-math -g3
APPNAME = ballin

Usage:
	@echo "Usage: make Win32 | Linux | MacOSX | clean | distclean"

GLprimer.o: main.cpp
	$(CC) $(OPT) $(INC) -c main.cpp -o main.o

Win32: $(OBJ)
	$(CC) $(OBJ) -o $(APPNAME).exe -L./GLFW -mwindows -lglfw3 -lopengl32 -mconsole -g3

Linux: $(OBJ)
	$(CC) $(OBJ) -o $(APPNAME) -L./GLFW -lglfw3_linux -lGL -lm -lX11 -lXxf86vm -lXrandr -lXi

MacOSX: $(OBJ)
	$(CC) $(OBJ) -o $(APPNAME) -L./GLFW -lglfw3_macosx -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

clean:
	rm -f $(OBJ)

distclean:
	rm -rf $(OBJ) $(APPNAME) $(APPNAME).exe
