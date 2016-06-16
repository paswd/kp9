#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "key.h"
#include "data.h"
#include "table.h"

int main(void)
{
	Table *table = table_create();
	printf("-------------------------------------------\n");
	printf("Commands:\n");
	printf("a <key> <value> - push to table\n");
	printf("d <key> - delete from table\n");
	printf("s - sort table\n");
	printf("p - print table\n");
	printf("f <key> - find element by key\n");
	printf("c - clear table\n");
	printf("q - exit\n");
	printf("-------------------------------------------\n");
	size_t cnt = 0;
	char last_cmd = '\n';
	while (true) {
		if (!cnt || last_cmd == '\n')
			printf("> ");
		char cmd;
		bool is_finished = false;
		scanf("%c", &cmd);
		size_t pos;
		//LinearlistElement *this = NULL;
		Key *key = key_create();
		switch (cmd) {
			case 'q':
				is_finished = true;
				break;
			case 'a':
				table_push(table);
				break;
			case 'd':
				//scanf("%d", &pos);
				key_set_value_from_input(key);
				table_note_delete(table, key);
				break;
			case 's':
				table_sort(table);
				break;
			case 'p':
				table_print(table);
				break;
			case 'c':
				table_clear(table);
				break;
			case 'f':
				key_set_value_from_input(key);
				Note *found = table_search(table, key, &pos);
				if (found == NULL) {
					printf("There are no notes with this key in the table\n");
					break;
				}
				note_print(table, found);
				break;
			case '\n':
				break;
			default:
				printf("Invalid command `%c`\n", cmd);
				break;
		}
		last_cmd = cmd;
		key_destroy(&key);
		if (is_finished) break;

		cnt++;
		cnt %= 2;

		//printf("First: %lld\n", (long long) linearlist_get_value(linearlist_get_first(linearlist)));
		//printf("Last: %lld\n", (long long) linearlist_get_value(linearlist_get_last(linearlist)));
	}
	printf("Goodbye!\n");

	table_destroy(&table);

	return 0;
}
