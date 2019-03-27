#include <stdio.h>
#include "girl.h"
#include "new.h"
#include <string.h>
#define num(p) ((( struct User *)(p)) -> num)
#define name(p) ((( struct User *)(p)) -> name)
static char greeting[4] = "Hey";
static char dream[45] = "I want a dress.Will somebody buy it for me?";

static void *Girl_ctor(void *_self, va_list *app) {
	struct Girl *self = ((const struct Class *)User)->ctor(_self, app);
	return self;
}
static void Girl_dtor(void *_self) {
	((const struct Class *)User)->dtor(_self);
}
static void Girl_type(const void * _self,message* mes)
{	
	int counter = 0;
	struct Girl *self = _self;
	mes->current += num(self);
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
	num(self) = counter;
}

static const struct Class _Girl = {
	sizeof(struct Girl),
	Girl_ctor,
	Girl_dtor,
	Girl_type
};

const void *Girl = &_Girl;