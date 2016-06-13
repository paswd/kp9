#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "table.h"
#include "key.h"
#include "data.h"

struct _note {
	Key *key;
	Data *data;
};

struct _table {
	Note *note_arr;
	size_t size;
	bool sorted;
	char *space;
};

Table *table_create(void)
{
	Table *table = (Table *) calloc(1, sizeof(Table));
	table->note_arr = NULL;
	table->size = 0;
	table->sorted = false;
	table->space = (char *) calloc(key_len() + 3, sizeof(char));
	int i;
	for (i = 0; i < key_len(); i++)
		table->space[i] = ' ';
	table->space[i] = ' ';
	table->space[i + 1] = '|';
	table->space[i + 2] = ' ';
	return table;
}

void table_destroy(Table **table)
{
	for (size_t i = 0; i < (*table)->size; i++) {
		(*table)->note_arr[i].key = (*table)->note_arr[i + 1].key;
		(*table)->note_arr[i].data = (*table)->note_arr[i + 1].data;
	}
	free((*table)->space);
	free(*table);
	*table = NULL;
}

void table_push(Table *table)
{
	table->size++;
	table->note_arr = (Note *) realloc(table->note_arr, table->size * sizeof(Note));
	table->note_arr[table->size - 1].key = key_create();
	table->note_arr[table->size - 1].data = data_create();

	printf("Input key:\n");
	key_set_value_from_input(table->note_arr[table->size - 1].key);
	printf("Input your ASCII-image (to finish press Ctrl+D):\n");
	data_set_value_from_input(table->note_arr[table->size - 1].data);

	table->sorted = false;
}

void table_note_delete(Table *table, size_t pos)
{
	if (pos >= table->size) {
		printf("Selected note is out of range\n");
		return;
	}
	key_destroy(&(table->note_arr[pos].key));
	data_destroy(&(table->note_arr[pos].data));
	for (size_t i = pos; i < table->size - 1; i++) {
		table->note_arr[i].key = table->note_arr[i + 1].key;
		table->note_arr[i].data = table->note_arr[i + 1].data;
	}
	table->size--;
	table->note_arr = (Note *) realloc(table->note_arr, table->size * sizeof(Note));
}


void table_sort(Table *table)
{
	bool is_changed;
	size_t end = table->size;
	do {
		is_changed = false;

		for (size_t i = 1; i < end; i++) {
			if (key_compare(table->note_arr[i - 1].key, table->note_arr[i].key) == 1) {
				Key *tmp_key = table->note_arr[i - 1].key;
				table->note_arr[i - 1].key = table->note_arr[i].key;
				table->note_arr[i].key = tmp_key;

				Data *tmp_data = table->note_arr[i - 1].data;
				table->note_arr[i - 1].data = table->note_arr[i].data;
				table->note_arr[i].data = tmp_data;

				is_changed = true;

			}
		}

		end--;
	} while (is_changed && end > 0);
}

void table_print(Table *table)
{
	int right_hr_len = 40;
	for (int i = 0; i < key_len() + 3 + right_hr_len; i++)
		printf("_");
	printf("\n");
	for (size_t i = 0; i < table->size; i++) {
		key_print(table->note_arr[i].key);
		printf(" | ");
		data_print(table->note_arr[i].data, table->space);
			printf("\n");
		for (int i = 0; i < key_len(); i++)
		printf("_");
		printf("_|_");
		for (int i = 0; i < right_hr_len; i++) {
			printf("_");
		}
		printf("\n");
	}
}
