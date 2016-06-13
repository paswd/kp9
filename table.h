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

void table_push(Table *table);
void table_note_delete(Table *table, size_t pos);
void table_sort(Table *table);
void table_print(Table *table);

#endif
