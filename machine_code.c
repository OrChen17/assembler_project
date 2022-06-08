int IC = 0
int DC = 0
DataCell* data_section;
CodeCell* code_section;

void add_code(CodeCell *cell) {
    code_section.push(cell);
    IC++;
}

void add_data(DataCell *cell) {
    data_section.push(instruction);
    DC++;
}

// TODO: Fix, normalize data types MachineCodeCell -> CodeCell (8 bits data, 2 bits ARE)
// DataCell - 10 bits data,