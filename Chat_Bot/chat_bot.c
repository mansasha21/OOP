#include <stdio.h>
#include<stdlib.h>
#include "user.h"
#include "boy.h"
#include "girl.h"
#include "RichBoy.h"
#include"CowardGirl.h"
#include "new.h"
#include<string.h>

char* my_scanf(char* from) {
	int i = 0;
	int j = 0;
	char* to = malloc(20 * sizeof(char));
	for (; j == 0 || from[j - 1] == ' '&&from[j] == ' ' || from[j] != ' '&&j < 19; j++) {
		if (j == 0 && from[j] == ' ' || from[j - 1] == ' '&&from[j] == ' ')
			continue;
		to[i] = from[j];
		i++;
	}
	to[i] = '\0';
	return to;
}
int create_people (char** names, void** people, FILE*f) {
	char buffer[100];
	fgets(buffer, 100, f);
	int num = 0;
	while (buffer[0] != '\n') {

		if (strstr(buffer, " User")|| strstr(buffer, " user")) {
			names[num] = my_scanf(buffer);
			people[num] = new(User, names[num]);
			num++;
		}
		else if (strstr(buffer, " Boy")|| strstr(buffer, " boy")) {
			names[num] = my_scanf(buffer);
			people[num] = new(Boy, names[num]);
			num++;
		}
		else if (strstr(buffer, " Girl")|| strstr(buffer, " girl")) {
			names[num] = my_scanf(buffer);
			people[num] = new(Girl, names[num]);
			num++;
		}
		else if (strstr(buffer, " CowardGirl")|| strstr(buffer, " cowardGirl")) {
			names[num] = my_scanf(buffer);
			people[num] = new(CowardGirl, names[num]);
			num++;
		}
		else if (strstr(buffer, " RichBoy")|| strstr(buffer, " richBoy")) {
			names[num] = my_scanf(buffer);
			people[num] = new(RichBoy, names[num]);
			num++;
		}
		fgets(buffer, 100, f);
	}
	return num;
}

message* log(char** names, void**people,int size) {
	char c;
	message * mes = message_create();
	int lap = 0;
	while (1) {
		mes->lap = lap;
		for (int k = 0; k < size; k++) {
			type(people[k], mes);
		}
		lap++;
		c = getch();
		if (c == 'q' || c == 'Q' || c == 'é' || c == 'É')
			break;
	}
	return mes;
}
void destroy_people(char**names, void**people, message* mes,int size) {
	message_destroy(mes);
	for (int k = 0; k < size; k++) {
		delete(people[k]);
	}
	free(people);
	free(names);
}