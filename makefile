#build directories.  BIN_DIR is relative to OBJ_DIR
OBJ_DIR = build/obj/
BIN_DIR = ../../build/bin/

CC = g++
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -std=c++11 -Wall -c

#sources to be compiled
SOURCES = main.cpp
#replace .cpp with .o in sources to get objects
OBJECTS = $(SOURCES:.cpp=.o)
EXE = rpg

all: $(EXE)
	
$(EXE): $(OBJECTS)
	cd $(OBJ_DIR); $(CC) $^ $(LDFLAGS) -o $(BIN_DIR)$@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $(OBJ_DIR)$@



.PHONY: clean
clean:
	rm build/bin/$(EXE)
	rm build/obj/*.o
