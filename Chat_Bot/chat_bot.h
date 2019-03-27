#pragma once
#include<stdio.h>
#include "message.h"
char* my_scanf(char* from);
int create_people (char** names, void** people, FILE*f);
message* log(char** names, void**people, int size);
void destroy_people(char**names, void**people, message* mes,int size);