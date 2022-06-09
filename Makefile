CXX = gcc
CXXFLAGS = -g -Wall -ansi -pedantic -std=c99

SRC = assembler.c file_handler.c helper.c line_parser.c instruction_parser.c

assembler: $(SRC)
	$(CXX) $(CXXFLAGS) -o assembler $(SRC) -I.

test: test.c helper.c
	$(CXX) $(CXXFLAGS) -o test test.c helper.c -I.