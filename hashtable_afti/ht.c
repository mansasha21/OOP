#include "ht.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define STD_SIZE 50;
#define STD_STOP -1;
typedef
struct htable {
	size_t count;
	size_t size;
	size_t keySize;
	size_t nodeSize;
	size_t valueSize;
	HTableItem**  items;
	size_t(*hash)(const void *);
	bool(*equals)(const void *, const void *);
}htable_t;
typedef struct node {
	struct node* next;
	HTableItem * item;
}node_t;
typedef struct list {
	node_t * head;
}list_t;

void * htable_init(void * htable, size_t keySize, size_t valueSize, size_t hash(const void *), bool(*equals)(const void *, const void *)) {
	if (htable == NULL || hash == NULL || equals == NULL||keySize==0||valueSize==0)
		return NULL;
	else {
		htable_t* ht = (htable_t*)htable;
		ht->nodeSize = 10;
		ht->equals = equals;
		ht->hash = hash;
		ht->count = 0;
		ht->keySize = keySize;
		ht->valueSize = valueSize;
		ht->size = STD_SIZE;
		ht->items = malloc(sizeof(HTableItem*)*ht->size);
		for (int i = 0; i < ht->size; i++) {
			ht->items[i] = NULL;
		}
		return ht;
	}
}
void * htable_create(size_t keySize, size_t valueSize, size_t(*hash)(const void *), bool(*equals)(const void *, const void *)){
	if (hash == NULL || equals == NULL || keySize == 0 || valueSize == 0)
		return NULL;
	else {
		htable_t* ht = malloc(sizeof(htable_t));
		ht = htable_init(ht, keySize, valueSize, hash, equals);
		return ht;
	}
}
void delete_list(list_t *list_) {
	if (list_ != NULL) {
		list_t* list = (list_t*)list_;
		node_t* node = (node_t*)list->head;
		node_t* cmp = node;
		while (node != NULL) {
			free(node->item->key);
			free(node->item->value);
			cmp = node->next;
			free(node->item);
			free(node);
			node = cmp;
		}
	}
}
void htable_destroy(void * htable, void(*destroy)(void *)) {
	if (htable != NULL) {
		htable_t* ht = (htable_t*)htable;
	
		for (int i = 0; i < ht->size; i++) {
			if (ht->items[i] == NULL)
				continue;
			list_t* list= ht->items[i]->value;
			node_t* node = (node_t*)list->head;
			node_t* cmp = node;
			if (destroy != NULL) {
				while (node != NULL) {
					cmp = node->next;
					destroy(node->item);
					free(node->item->key);
					free(node->item->value);
					free(node->item);
					free(node);
					node = cmp;
				}
			}
			else {
				delete_list(ht->items[i]->value);
			}
			free(ht->items[i]->value);
		}
		for (int i = 0; i < 50; i++)
			free(ht->items[i]);
		free(ht->items);
		free(htable);
		htable = NULL;
	}
}
size_t htable_count(const void * htable){
	if (htable == NULL) return (size_t)STD_STOP;
	htable_t* ht = (htable_t*)htable;
	return ht->count;
}
void * htable_item(const void * htable, const void * key) {
	if (htable != NULL && key!=NULL) {
		htable_t* ht = (htable_t*)htable;
		size_t index = abs(ht->hash(key))%50;
		bool find = false;
		if (ht->items[index]== NULL)
			return NULL;
		else {
			HTableItem* item = ht->items[index];
			list_t*list = (list_t*)item->value;
			node_t* node = (node_t*)list->head;
			while ( node!= NULL) {
				if (ht->equals(key, node->item->key))
					return node->item->value;
				node = node->next;
			}
			return  NULL;
		}
	}
	else return NULL;
}
void * htable_insert(void * htable, const void * key, bool * createFlag){
	if (htable != NULL && key != NULL&&createFlag!=NULL) {
		htable_t* ht = (htable_t*)htable;
		size_t index = abs(ht->hash(key))%50;
		list_t* list = NULL;
		if (ht->items[index] == NULL) {
			*createFlag = true;
			ht->items[index] = malloc(sizeof(HTableItem));
			ht->items[index]->value = malloc(sizeof(list_t));
			ht->items[index]->key = NULL;
			list = (list_t*)ht->items[index]->value;
			list->head = malloc(sizeof(node_t));
			list->head->item = malloc(sizeof(HTableItem));
			list->head->item->key = malloc(ht->keySize);
			list->head->item->value = malloc(ht->valueSize);
			list->head->next = NULL;
			memcpy(list->head->item->key, key, ht->keySize);
			ht->count++;
			return list->head->item->value;
		}
		else {
			list = (list_t*)ht->items[index]->value;
			node_t* node =list->head;
			node_t* cmp = NULL;
			int i = 0;
			while (node != NULL) {
				if  (ht->equals(key, node->item->key)) {
					*createFlag = false;
					return node->item->value;
				}
				else {
					if (i == 10)
						break;
					i++;
					cmp = node;
					node = node->next;
				}
			}
			if (i == 10) {
				*createFlag = false;
				return NULL;
			}	
			node = malloc(sizeof(node_t));
			node->next = NULL;
			node->item = malloc(sizeof(HTableItem));
			node->item->key = malloc(ht->keySize);
			node->item->value = malloc(ht->valueSize);
			memcpy(node->item->key, key, ht->keySize);
			cmp->next = node;
			*createFlag = true;
			ht->count++;
			return node->item->value;
		}
	}
	else return NULL;
}
void htable_remove(void * htable, const void * key, void(*destroy)(void *)) {		 
	if (htable != NULL && key != NULL) {
		htable_t* ht = (htable_t*)htable;
		size_t index = abs(ht->hash(key)) % 50;
		if (ht->items[index] != NULL) {
			list_t * list = (list_t*)ht->items[index]->value;
			node_t* node = list->head;
			node_t* cmp = NULL;
			int i = 0;
			while (node != NULL) {
				if (destroy != NULL && ht->equals(key, node->item->key)) {
					if (i == 0)
						list->head = node->next;
					else
						cmp->next = node->next;
					destroy(node->item);
					free(node->item->key);
					free(node->item->value);
					free(node->item);
					free(node);
					node = NULL;
					if (list->head == NULL) {
						free(list);
						free(ht->items[index]);
						ht->items[index] = NULL;
					}
					ht->count--;
					break;
				}
				else {
					if (ht->equals(key, node->item->key)) {
						if (i == 0)
							list->head = node->next;
						else
							cmp->next = node->next;
						free(node->item->key);
						free(node->item->value);
						free(node->item);
						free(node);
						node = NULL;
						if (list->head == NULL) {
							free(list);
							free(ht->items[index]);
							ht->items[index] = NULL;
						}
						ht->count--;
						break;
					}
				}
				cmp = node;
				node = node->next;
				i++;
			}
		}
	}
}
void htable_clear(void * htable, void(*destroy)(void *)) {
	if (htable != NULL) {
		htable_t* ht = (htable_t*)htable;
		for (int i = 0; i < ht->size; i++) {
			if (ht->items[i] == NULL)
				continue;
			list_t* list = (list_t*)ht->items[i]->value;
			node_t* node = list->head;
			node_t* cmp = NULL;
			while (node != NULL) {
				cmp = node->next;
				if (destroy != NULL) {
					destroy(node->item);
					free(node->item->key);
					free(node->item->value);
					free(node->item);
					free(node);
					node = cmp;
					ht->count--;
				}
				else {
					ht->count--;
					free(node->item->key);
					free(node->item->value);
					free(node->item);
					free(node);
					node = cmp;
				}			
			}
			free(list);
			free(ht->items[i]);
			ht->items[i] = NULL;
		}
	}
}
size_t htable_first(const void * htable) {
	if (htable != NULL) {
		htable_t* ht = (htable_t*)htable;
		for (int i = 0; i < ht->size; i++) {
			if (ht->items[i] != NULL)
				return (size_t)i*ht->nodeSize;
		}
		return (size_t)STD_STOP;
	}
	return (size_t)STD_STOP;
}
size_t htable_last(const void * htable) {
	if (htable != NULL) {
		htable_t* ht = (htable_t*)htable;
		for (int i = ht->size - 1; i > -1; i--) {
			if (ht->items[i] == NULL)
				continue;
			list_t* list = (list_t*)ht->items[i]->value;
			node_t* node = list->head;
			int j = 0;
			if (node != NULL) {
				while (node->next != NULL) {
					node = node->next;
					j++;
				}
				return (size_t)i * ht->nodeSize + j;
			}
		}
		return (size_t)STD_STOP;
	}
	return (size_t)STD_STOP;
}
size_t htable_next(const void * htable, size_t item_id) {
	if (item_id == htable_stop(htable)) return (size_t)STD_STOP;
	if (htable != NULL && (int)item_id <= htable_last(htable) && (int)item_id >= htable_first(htable)) {
		htable_t* ht = (htable_t*)htable;
		int hash = item_id / 10;
		int num = item_id % 10;
		HTableItem* item = ht->items[hash];
		if (item != NULL) {
			list_t* list = (list_t*)item->value;
			node_t* node = list->head;
			int counter = 0;
			while (node != NULL) {
				if (counter < num && node->next == NULL) {
					return (size_t)STD_STOP;
				}
				else if (num + 1 == counter) {
					return (size_t)hash*ht->nodeSize + counter;
				}
				node = node->next;
				counter++;
			}
		}
		else
			return (size_t)STD_STOP;
		for (int i = hash + 1; i < ht->size; i++) {
			if (ht->items[i] != NULL)  return (size_t)i * ht->nodeSize;
		}
	}
	return (size_t)STD_STOP;
}
size_t htable_prev(const void * htable, size_t item_id) {
	if (item_id == htable_stop(htable)) return (size_t)STD_STOP;
	if (htable != NULL && (int)item_id<=htable_last(htable) && (int)item_id>=htable_first(htable)) {
		htable_t* ht = (htable_t*)htable;
		int hash = item_id / 10;
		int num = item_id % 10;
		list_t* list = NULL;
		node_t* node = NULL;
		HTableItem* item = ht->items[hash];
		int counter = 0;
		if (item != NULL) {
			list = (list_t*)item->value;
			node = list->head;
			while (node != NULL && counter < num) {
				if (num - 1 == counter && node->next != NULL)
					return (size_t)hash * ht->nodeSize + counter;
				else if (num - 1 >= counter && node->next == NULL)
					return (size_t)STD_STOP;
				node = node->next;
				counter++;
			}
		}
		else
			return (size_t)STD_STOP;
		for (int i = hash -1; i >-1; i--) {
			if (ht->items[i] != NULL) {
				item = ht->items[i];
				list = (list_t*)item->value;
				node = list->head;
				counter = 0;
				while(node->next!=NULL){
					node = node->next;
					counter++;
				}
				return (size_t)i * ht->nodeSize+counter;
			}
		}
	}
	return (size_t)STD_STOP;
}
size_t htable_stop(const void * htable) {
	return (size_t)STD_STOP;
}
void * htable_current(const void * htable, size_t item_id) {
	if (item_id == htable_stop(htable)) return NULL;
	if (htable != NULL && (int)item_id <= htable_last(htable) && (int)item_id >= htable_first(htable)) {
		htable_t* ht = (htable_t*)htable;
		int hash = item_id / 10;
		int num = item_id % 10;
		int counter = 0;
		HTableItem* item = ht->items[hash];
		if (item == NULL)
			return NULL;
		else {
			list_t* list = (list_t*)item->value;
			node_t* node = list->head;
			while (node != NULL) {
				if (counter == num)
					return node->item;
				counter++;
				node = node->next;
			}
		}
	}
	return NULL;
}
void htable_erase(void * htable, size_t item_id, void(*destroy)(void *)) {
	if (item_id == htable_stop(htable)) return ;
	if (htable != NULL && (int)item_id <= htable_last(htable) && (int)item_id >= htable_first(htable)) {
		htable_t* ht = (htable_t*)htable;
		int hash = item_id / 10;
		int num = item_id % 10;
		HTableItem* item = ht->items[hash];
		if (item != NULL) {
			list_t* list = (list_t*)item->value;
			node_t* node = list->head;
			node_t* cmp=NULL;
			int counter = 0;
			while (node != NULL && counter < num + 1) {
				if (destroy != NULL && counter == num) {
					if (counter == 0)
						list->head = node->next;
					else
						cmp->next = node->next;
					destroy(node->item);
					free(node->item->key);
					free(node->item->value);
					free(node->item);
					free(node);
					if (list->head == NULL) {
						free(list);
						free(item);
						ht->items[hash] = NULL;
					}
					ht->count--;
					break;
				}
				else {
					if (counter == num) {
						if (counter == 0)
							list->head = node->next;
						else
							cmp->next = node->next;
						free(node->item->key);
						free(node->item->value);
						free(node->item);
						free(node);
						if (list->head == NULL) {
							free(list);
							free(item);
							ht->items[hash] = NULL;
						}
						ht->count--;
						break;
					}
				}
				cmp = node;
				node = node->next;
				counter--;
			}
		}
	}
}