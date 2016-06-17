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
	char tmp[1024];
	int sym;
	int cnt = 0;
	int i = 0;
	Key *key = NULL;
	Data *data = NULL;
	Table *table = table_create();
	while ((sym = getchar()) != EOF) {
		if (sym == '\n') {
			tmp[i] = '\0';
			//printf("%s\n", tmp);
			if (cnt == 0) {
				key_destroy(&key);
				key = key_create();
				key_set_value(key, tmp);
				cnt++;
				cnt %= 2;
			} else {
				data_destroy(&data);
				data = data_create();
				data_set_value(data, tmp);
				table_push(table, key_clone(key), data_clone(data));
				cnt++;
				cnt %= 2;
			}
			i = 0;
			continue;
		}
		tmp[i] = sym;
		i++;
	}
	key_destroy(&key);
	data_destroy(&data);
	//printf("Point\n");
	table_print(table);
	table_sort(table);
	table_print(table);
	/*printf("To finish search input `q`");
	while (true) {
		size_t pos;
		char *inp = (char *) calloc(1023, sizeof(char));
		int l = scanf("%s", inp);
		inp[l] = '\0';

		if (inp[0] == 'q' && inp[1] == '\n')
			break;
		key = key_create();
		key_set_value(key, inp);
		Note *note = table_search(table, key, &pos);
		if (note != NULL)
			note_print(note);
		else
			printf("This note does not exists\n");
		key_destroy(&key);
		free(inp);
		inp = NULL;
	}*/
	table_destroy(&table);
	return 0; 
}