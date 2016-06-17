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
	if ((*data) == NULL)
		return;
	free((*data)->value);
	free(*data);
	*data = NULL;
}

void data_set_value_from_input(Data *data)
{
	Queue *queue = queue_create();

	char sym;
	int cnt = 0;
	while ((sym = getchar()) != '\n') {
		queue_push(queue, (long long) sym);
		cnt++;
	}
	char end_data = '\0';
	queue_push(queue, (long long) end_data);

	data->value = (char *) calloc(cnt, sizeof(char));
	data->length = cnt;
	for (int i = 0; i < cnt; i++)
		data->value[i] = (char) queue_pop(queue);

	queue_destroy(&queue);
}
void data_set_value(Data *data, char *str)
{
	int end = 0;
	while (str[end] != '\n' && end < 1023)
		end++;

	data->length = end + 1;
	data->value = (char *) calloc(data->length, sizeof(char));
	for (int i = 0; i < end; i++)
		data->value[i] = str[i];

	data->value[end] = '\0';
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

void data_print(Data *data)
{
	/*for (size_t i = 0; i < data->length; i++) {
		printf("%c", data->value[i]);
		if (data->value[i] == '\n')
			printf("%s", space);
	}*/
	printf("%s\n", data->value);
}
