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
	//printf("c - clear table\n");
	printf("q - exit\n");
	printf("-------------------------------------------\n");
	while (true) {
		char cmd;
		bool is_finished = false;
		scanf("%c", &cmd);
		int pos;
		//LinearlistElement *this = NULL;
		switch (cmd) {
			case 'q':
				is_finished = true;
				break;
			case 'a':
				table_push(table);
				break;
			case 'd':
				scanf("%d", &pos);
				//this = linearlist_get_prev_element_by_position(linearlist, pos, &err);
				table_note_delete(table, pos);
				break;
			case 's':
				table_sort(table);
				break;
			case 'p':
				table_print(table);
				break;
			case '\n':
				break;
			default:
				printf("Invalid command `%c`\n", cmd);
				break;
		}
		if (is_finished) break;

		//printf("First: %lld\n", (long long) linearlist_get_value(linearlist_get_first(linearlist)));
		//printf("Last: %lld\n", (long long) linearlist_get_value(linearlist_get_last(linearlist)));
	}
	printf("Goodbye!\n");

	table_destroy(&table);

	return 0;
}
