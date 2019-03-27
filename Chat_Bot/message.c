#define _CRT_SECURE_NO_WARNINGS
#include "message.h"
#include <string.h>
#include <stdlib.h>

message* message_create() {
	message * mes = malloc(sizeof(message));
	mes->current = 0;
	mes->lap = 0;
	mes->size = 0;
	mes->almem = 1000;
	mes->log = malloc(sizeof(char*)*1000);
	return mes;
}
void message_clear(message* mes) {
	for (int i = 0; i < mes->size; i++) {
		free(mes->log[i]);
	}
}
void message_destroy(message* mes) {
	message_clear(mes);
	free(mes->log);
	free(mes);
}
void message_insert(message* mes, char *text) {
	if (mes->size == mes->almem) {
		realloc(mes->log, sizeof(char*)*(mes->size*2));
		mes->almem *= 2;
	}
	mes->log[mes->size] = malloc(sizeof(char)*(strlen(text)+1));
	memcpy(mes->log[mes->size],text, sizeof(char)*(strlen(text)+1));
	mes->size++;
}
