#ifndef _TABLE_H_
#define _TABLE_H_

#include <stdbool.h>
#include <string.h>
#include "key.h"
#include "data.h"

typedef struct _note Note;
typedef struct _table Table;

Table *table_create(void);
void table_destroy(Table **table);

bool table_push(Table *table, Key *key, Data *data);
void table_note_delete(Table *table, Key *key);
void table_sort(Table *table);
Note *table_search(Table *table, Key *key, size_t *pos);
void table_clear(Table *table);
void table_print(Table *table);
void note_print(Note *note);
bool table_is_sorted(Table *table);

#endif
