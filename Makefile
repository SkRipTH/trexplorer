OBJ = main.o readdir.o render.o

all: trexplorer.exe

trexplorer.exe: $(OBJ)
	gcc $^ -lncurses -o trexplorer.exe

clean:
	rm $(OBJ)

$(OBJ): trexplorer.h
