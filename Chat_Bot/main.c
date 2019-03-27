#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>
#include "user.h"
#include "boy.h"
#include "girl.h"
#include "RichBoy.h"
#include"CowardGirl.h"
#include "new.h"
#include<string.h>
#include "chat_bot.h"



int main(int argc, char **argv) {
	void** people = malloc(sizeof(void*) * 100);
	char** names = malloc(sizeof(char*) * 100);
	if (argc == 1)
		return -1;
	FILE * f = fopen(argv[1], "r");
	if (f == NULL) {
		return -1;
	}
	int num= create_people(names, people, f);
	message *mes=log(names, people, num);
	destroy_people(names, people, mes,num);
	fclose(f);
	return 0;
}