#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "key.h"

#define KEY_LEN	5

struct _key {
	char value[KEY_LEN + 1];
};

int key_len(void)
{
	return KEY_LEN;
}

Key *key_create(void)
{
	Key *key = (Key *) calloc(1, sizeof(Key));
	return key;
}

void key_destroy(Key **key)
{
	if (*key == NULL)
		return;
	free(*key);
	*key = NULL;
}

void key_set_value_from_input(Key *key)
{
	//printf("KeyLen: %d\n", KEY_LEN);
	scanf("%c", key->value);
	for (int i = 0; i < KEY_LEN; i++) { 
		scanf("%c", key->value + i);
	}
	key->value[KEY_LEN] = '\0';
}

void key_set_value(Key *key, char *str)
{
	for (int i = 0; i <= KEY_LEN; i++) {
		key->value[i] = str[i];
	}
	if (key->value[KEY_LEN] != '\0')
		key->value[KEY_LEN] = '\0';
}

void key_print(Key *key)
{
	printf("%s", key->value);
}

char key_get_sym(Key *key, int i)
{
	if (i >= KEY_LEN || i < 0)
		return -1;
	return key->value[i];
}

int key_compare(Key *key1, Key *key2)
{
	for (int i = 0; i < KEY_LEN; i++) {
		if (key1->value[i] > key2->value[i])
			return 1;
		if (key1->value[i] < key2->value[i])
			return -1;
	}
	return 0;
}

Key *key_clone(Key *key)
{
	Key *res = key_create();
	for (int i = 0; i < KEY_LEN; i++) {
		res->value[i] = key->value[i];
	}
	return res;
}
