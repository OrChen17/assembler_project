CXX = gcc
CXXFLAGS = -g -Wall -ansi -pedantic -std=c99

SRC = file_handler.c helper.c line_parser.c instruction_parser.c machine_code.c

assembler: assembler.c $(SRC)
	$(CXX) $(CXXFLAGS) -o assembler assembler.c $(SRC) -I.

test: test.c $(SRC)
	$(CXX) $(CXXFLAGS) -o test test.c $(SRC) -I.

