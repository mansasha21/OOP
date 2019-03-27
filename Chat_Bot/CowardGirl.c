#include <stdio.h>
#include "CowardGirl.h"
#include "new.h"
#include <string.h>
#define num(p) ((( struct User *)(p)) -> num)
#define name(p) ((( struct User *)(p)) -> name)
static char greeting[4] = "Hey";
static char dream[45] = "I want a dress.Will somebody buy it for me?";
static char fear[31] = "AAAAaaa! No! No rats here, pls";
static void *CowardGirl_ctor(void *_self, va_list *app) {
	struct CowardGirl *self = ((const struct Class *)Girl)->ctor(_self, app);
	return self;
}
static void CowardGirl_dtor(void *_self) {
	((const struct Class *)Girl)->dtor(_self);
}

static void CowardGirl_type(const void * _self, message* mes)
{
	int counter = 0;
	struct CowardGirl *self = _self;
	mes->current += num(self);
	int size = mes->size;
	if (mes->lap == 0) {
		printf("%s: ", name(self));
		puts(greeting);
		counter++;
		printf("%s: ", name(self));
		puts(dream);
		counter++;
		message_insert(mes, greeting);
		message_insert(mes, dream);
	}
	for (int i = mes->current; i < size; i++) {
		if (strstr(mes->log[i], "rat") != NULL || strstr(mes->log[i], "rats") != NULL) {
			printf("%s: ", name(self));
			puts(fear);
			counter++;
			message_insert(mes, fear);
		}
	}
	num(self) = counter;
}

// Описание класса Circle
static const struct Class _CowardGirl = {
	sizeof(struct CowardGirl),
	CowardGirl_ctor,
	CowardGirl_dtor,
	CowardGirl_type
};

const void *CowardGirl = &_CowardGirl;