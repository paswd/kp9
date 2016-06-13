#ifndef _DATA_H_
#define _DATA_H_

#include <stdbool.h>
#include <string.h>

typedef struct _data Data;

Data *data_create(void);
void data_destroy(Data **data);
void data_set_value_from_input(Data *data);
Data *data_clone(Data *data);
void data_print(Data *data, char *space);

#endif
