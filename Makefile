CXX = gcc
CXXFLAGS = -Wall -ansi -pedantic -std=c99
LDFLAGS =  

SRC = assembler.c file_handler.c helper.c
OBJ = $(SRC:.c=.o)
EXEC = assembler

assembler: $(SRC)
	$(CXX) $(CXXFLAGS) -o assembler $(SRC) -I.
