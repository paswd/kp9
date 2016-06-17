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
};

Table *table_create(void)
{
	Table *table = (Table *) calloc(1, sizeof(Table));
	table->note_arr = NULL;
	table->size = 0;
	table->sorted = false;
	return table;
}

void table_destroy(Table **table)
{
	for (size_t i = 0; i < (*table)->size; i++) {
		key_destroy(&((*table)->note_arr[i].key));
		data_destroy(&((*table)->note_arr[i].data));
	}
	free((*table)->note_arr);
	free(*table);
	*table = NULL;
}


bool table_push(Table *table, Key *key, Data *data)
{
	table->size++;
	table->note_arr = (Note *) realloc(table->note_arr, table->size * sizeof(Note));
	table->note_arr[table->size - 1].key = key;
	table->note_arr[table->size - 1].data = data;
	table->sorted = false;
	return true;
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

	/*if (!table_is_sorted(table)) {
		printf("Table has not been sorted. Sorting...\n");
		table_sort(table);
		printf("Table has been successfully sorted\n");
	}*/
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
	for (size_t i = 0; i < table->size; i++) {
		data_print(table->note_arr[i].data);
	}
}
void note_print(Note *note)
{
	data_print(note->data);
}

bool table_is_sorted(Table *table)
{
	return table->sorted;
}
