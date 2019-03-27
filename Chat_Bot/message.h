#pragma once

typedef struct {
	int current;
	int lap;
	int size;
	int almem;
	char** log;
}message;

message* message_create();
void message_destroy(message* mes);
void message_insert(message* mes, char *text);