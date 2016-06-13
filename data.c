#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "data.h"
#include "queue.h"

struct _data {
	char *value;
	size_t length;
};

Data *data_create(void)
{
	Data *data = (Data *) calloc(1, sizeof(Data));
	return data;
}
void data_destroy(Data **data)
{
	free((*data)->value);
	free(*data);
	*data = NULL;
}

void data_set_value_from_input(Data *data)
{
	Queue *queue = queue_create();

	char sym;
	int cnt = 0;
	while ((sym = getchar()) != EOF) {
		queue_push(queue, (long long) sym);
		cnt++;
	}

	data->value = (char *) calloc(cnt, sizeof(char));
	data->length = cnt;
	for (int i = 0; i < cnt; i++)
		data->value[i] = (char) queue_pop(queue);

	queue_destroy(&queue);
}

Data *data_clone(Data *data)
{
	Data *res = data_create();
	res->length = data->length;
	res->value = (char *) calloc(res->length, sizeof(char));
	for (size_t i = 0; i < res->length; i++) {
		res->value[i] = data->value[i];
	}
	return res;
}

void data_print(Data *data, char *space)
{
	for (size_t i = 0; i < data->length; i++) {
		printf("%c", data->value[i]);
		if (data->value[i] == '\n')
			printf("%s", space);
	}
}
