# Main compiler
CC=g++
SRCEXT=cpp

# All important subdirectories
# include contains all .h/.hpp files
IDIR=include

# object files
ODIR=obj

# libraries
LDIR=lib

# source files
SDIR=src

# binaries files
BDIR=bin

# test files
TESTDIR=tests

# Compilation flags
FLAGS=-Wall -std=c++11 -O2 -I $(IDIR) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# List of all sources and objects
SRC=$(shell find $(SDIR) -type f -name *.$(SRCEXT))
OBJ=$(patsubst $(SDIR)/%.$(SRCEXT), $(ODIR)/%.o, $(SRC))

# Main project
TARGET=$(SDIR)/main.cpp

$(ODIR)/%.o: $(SDIR)/%.$(SRCEXT)
	$(CC) -c -o $@ $^ $(FLAGS)

DTDEP=$(ODIR)/timer.o $(ODIR)/room.o $(ODIR)/object.o $(ODIR)/graphicshandler.o $(ODIR)/geometry.o $(ODIR)/dungeon-trap/character.o $(ODIR)/dungeon-trap/colliders.o $(ODIR)/dungeon-trap/enemy.o $(ODIR)/dungeon-trap/environment.o $(ODIR)/dungeon-trap/mainroom.o $(ODIR)/dungeon-trap/player.o $(ODIR)/dungeon-trap.o $(ODIR)/dungeon-trap/resources.o

dungeon-trap: $(DTDEP)
	echo "Compiling dungeon-trap"
	$(CC) -o $(BDIR)/$@ $^ $(FLAGS)

level-editor:
	echo "Compiling level-editor"
	$(CC) -o $(BDIR)/$@ $(SDIR)/level-editor.cpp

.PHONY: clean

clean:
	rm $(shell find $(ODIR) -type f -name *.o)
