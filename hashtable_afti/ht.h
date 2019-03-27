#pragma once
#include <stdbool.h> // bool
#include <stddef.h>  // size_t

typedef
struct htableItem {
	const void * key;
	void * value;
}
HTableItem;
void * htable_create(size_t keySize, size_t valueSize, size_t(*hash)(const void *), bool(*equals)(const void *, const void *));
void * htable_init(void * htable, size_t keySize, size_t valueSize, size_t hash(const void *), bool(*equals)(const void *, const void *));
void htable_destroy(void * htable, void(*destroy)(void *));
size_t htable_count(const void * htable);
void * htable_item(const void * htable, const void * key);
void * htable_insert(void * htable, const void * key, bool * createFlag);
void htable_remove(void * htable, const void * key, void(*destroy)(void *));
void htable_clear(void * htable, void(*destroy)(void *));
size_t htable_first(const void * htable);
size_t htable_last(const void * htable);
size_t htable_next(const void * htable, size_t item_id);
size_t htable_prev(const void * htable, size_t item_id);
size_t htable_stop(const void * htable);
void * htable_current(const void * htable, size_t item_id);
void htable_erase(void * htable, size_t item_id, void(*destroy)(void *));

