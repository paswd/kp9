#ifndef _KEY_H_
#define _KEY_H_

#include <stdbool.h>
#include <string.h>

typedef struct _key Key;

int key_len(void);

Key *key_create(void);
void key_destroy(Key **key);

void key_set_value_from_input(Key *key);
void key_print(Key *key);
char key_get_sym(Key *key, int i);
int key_compare(Key *key1, Key *key2);
Key *key_clone(Key *key);

#endif
