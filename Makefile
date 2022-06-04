CXX = gcc
CXXFLAGS = -Wall -ansi -pedantic -std=c99
LDFLAGS =  

SRC = assemble.c file_handler.c
OBJ = $(SRC:.c=.o)
EXEC = assembler

assembler: assemble.c file_handler.c
	$(CXX) $(CXXFLAGS) -o assembler assemble.c file_handler.c -I.
