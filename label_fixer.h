#include "symbol_table.h"

void fix_labels(void);
void fix_symbols_table(void);
/*Moving data rows to the bottom*/
void add_missing_addresses_code(void);
/*Adding addresses to code cells where missing*/
int get_label_type(char label[31]);
int check_all_entries_are_labels();
/*Verify that all of the EntryExtern cells contents are indeed labels*/