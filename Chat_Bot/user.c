// Для va_arg
#include <stdarg.h>
#include <stdlib.h>
// Для printf
#include <stdio.h>
#include<string.h>
#include "user.h"
#include "new.h"
#include "message.h"

static char greeting[4] = "Hey";

static void *User_ctor(void *_self, va_list *app){
	struct User *self = _self;
	char* name = va_arg(*app, char*);
	self->name = name;
	self->num = 0;
	//puts("here");
	return self;
}

static void User_type(const void *_self, message * mes){
	struct User *self = _self;
	int counter = 0;
	mes->current += self->num;
	if (mes->lap == 0) {
		printf("%s: ", self->name);
		puts(greeting);
		message_insert(mes, greeting);
		counter++;
	}
	self->num = counter;
}

static void User_dtor(const void *_self) {
	struct User *self = _self; 
	//puts("here");
	free(self->name);
}
static const struct Class _User = {
	sizeof(struct User),
	User_ctor,
	User_dtor,
	User_type
};

const void *User = &_User;