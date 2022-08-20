#include "symbol_table.h"

void fix_labels(void);
void fix_symbols_table(void);
void add_missing_addresses_code(void);
void add_missing_addresses_data(void);
int get_label_type(char label[31]);