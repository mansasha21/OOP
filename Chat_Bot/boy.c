#include <stdio.h>
#include "boy.h"
#include "new.h"
#include <string.h>
static char greeting[4] = "Hey";
static char flirt[37] = "U r such a girl!R u afraid of rats?";
#define num(p) ((( struct User *)(p)) -> num)
#define name(p) ((( struct User *)(p)) -> name)

static void *Boy_ctor(void *_self, va_list *app) {

	struct Boy *self = ((const struct Class *)User)->ctor(_self, app);

	return self;
}

static void Boy_dtor(void *_self) {
	((const struct Class *)User)->dtor(_self);
}



static void Boy_type(const void * _self,message*mes)
{

	int counter = 0;
	struct Boy *self = _self;
	int size = mes->size;
	mes->current += num(self);
	if (mes->lap == 0) {
		printf("%s: ", name(self));
		puts(greeting);
		counter++;
		message_insert(mes, greeting);
	}
	for (int i = mes->current; i < size; i++) {
		if (strstr(mes->log[i], "I want a dress") != NULL) {
			printf("%s: ", name(self));
			puts(flirt);
			counter++;
			message_insert(mes, flirt);
		}
	}
	num(self) = counter;
}

static const struct Class _Boy = {
	sizeof(struct Boy),
	Boy_ctor,
	Boy_dtor,
	Boy_type
};


const void *Boy = &_Boy;