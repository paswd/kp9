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
	table->space = (char *) calloc(key_len() + 4, sizeof(char));
	int i;
	for (i = 0; i < key_len(); i++)
		table->space[i] = ' ';
	table->space[i] = ' ';
	table->space[i + 1] = '|';
	table->space[i + 2] = ' ';
	table->space[i + 3] = '\0';
	return table;
}

void table_destroy(Table **table)
{
	for (size_t i = 0; i < (*table)->size; i++) {
		key_destroy(&((*table)->note_arr[i].key));
		data_destroy(&((*table)->note_arr[i].data));
	}
	free((*table)->note_arr);
	free((*table)->space);
	free(*table);
	*table = NULL;
}

void table_push(Table *table)
{
	Key *tmp_key = key_create();
	//printf("Push: point\n");
	printf("Input key:\n");
	key_set_value_from_input(tmp_key);
	size_t pos;
	Note *note_found = table_search(table, tmp_key, &pos);
	if (note_found != NULL) {
		key_destroy(&tmp_key);
		printf("Element with this key has already exists\n");
		return;
	}
	table->size++;
	table->note_arr = (Note *) realloc(table->note_arr, table->size * sizeof(Note));
	table->note_arr[table->size - 1].key = tmp_key;
	table->note_arr[table->size - 1].data = data_create();

	//key_set_value_from_input(table->note_arr[table->size - 1].key);
	printf("Input your ASCII-image (to finish press Ctrl+D):\n");
	data_set_value_from_input(table->note_arr[table->size - 1].data);
	//printf("Push: true\n");
	table->sorted = false;
	printf("> ");
}

void table_note_delete(Table *table, Key *key)
{
	size_t pos;
	Note *note_found = table_search(table, key, &pos);
	if (note_found == NULL) {
		printf("Element with this key does not exists\n");
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
	table->sorted = true;
}

Note *table_search(Table *table, Key *key, size_t *pos)
{
	if (table->size == 0)
		return NULL;

	if (!table_is_sorted(table)) {
		printf("Table has not been sorted. Sorting...\n");
		table_sort(table);
		printf("Table has been successfully sorted\n");
	}
	size_t start = 0;
	size_t end = table->size;
	size_t mid = (start + end) / 2;

	int lg;
	size_t mid_old = -1;

	while ((lg = key_compare(key, table->note_arr[mid].key)) != 0) {
		if (lg > 0)
			start = mid;
		else
			end = mid;
		mid_old = mid;
		mid = (start + end) / 2;
		if (mid == mid_old)
			return NULL;
	}
	*pos = mid;
	return table->note_arr + mid;
}

void table_clear(Table *table)
{
	for (size_t i = 0; i < table->size; i++) {
		key_destroy(&(table->note_arr[i].key));
		data_destroy(&(table->note_arr[i].data));
	}
	table->note_arr = realloc(table->note_arr, 0);
	table->size = 0;
	table->sorted = false;
}

void table_print(Table *table)
{
	if (table->size == 0) {
		printf("Table is empty\n");
		return;
	}
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
	printf("\n");
}

void note_print(Table *table, Note *note)
{
	if (note == NULL)
		return;
	int right_hr_len = 40;
	for (int i = 0; i < key_len() + 3 + right_hr_len; i++)
		printf("_");
	printf("\n");
	key_print(note->key);
	printf(" | ");
	data_print(note->data, table->space);
		printf("\n");
	for (int i = 0; i < key_len(); i++)
	printf("_");
	printf("_|_");
	for (int i = 0; i < right_hr_len; i++) {
		printf("_");
	}
	printf("\n");
}

bool table_is_sorted(Table *table)
{
	return table->sorted;
}
