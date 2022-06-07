CXX = gcc
CXXFLAGS = -g -Wall -ansi -pedantic -std=c99
LDFLAGS =  

SRC = assembler.c file_handler.c helper.c line_parser.c instruction_parser.c
OBJ = $(SRC:.c=.o)
EXEC = assembler

assembler: $(SRC)
	$(CXX) $(CXXFLAGS) -o assembler $(SRC) -I.
